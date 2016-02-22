#include "WPILib.h"
#include "Shooter.h"
#include <iostream>
using namespace std;

void Shooter::ShooterInit() {

	prefs = Preferences::GetInstance();
	pcmCANID = prefs->GetInt("pcmCANID", 7);
	shooterSolenoidExtend = prefs->GetInt("shooterSolenoidExtend", 2);
	shooterSolenoidRetract = prefs->GetInt("shooterSolenoidRetract", 2);
	shooterTopMotorCANTalonID = prefs->GetInt("shooterTopMotorCANTalonID", 2);
	shooterBottomMotorCANTalonID = prefs->GetInt("shooterBottomMotorCANTalonID",6);
	shooterBallDetectSwitch = prefs->GetInt("shooterBallDetectSwitch", 3);
	driveJoystickNumber = prefs->GetInt("driveJoystickNumber", 0);
	shooterTrigger = prefs->GetInt("shooterTrigger", 8);
	firePhase = 0;
	shooterJoystick = new Joystick(driveJoystickNumber);
	shooterButtonvalue = false;
	exsole = new DoubleSolenoid(pcmCANID, shooterSolenoidExtend, shooterSolenoidRetract);
	rightTimer = new Timer();
	shooterLimitSwitch = new DigitalInput(shooterBallDetectSwitch);
	timer = 0;
	targetSpeed = prefs->GetFloat ("shooterTargetSpeed", 10.0f);
	actualTopSpeed = 0.0f;
	actualLowerSpeed = 0.0f;

	//Set up wheels
	topWheel = new CANTalon(shooterTopMotorCANTalonID);
	lowerWheel = new CANTalon(shooterBottomMotorCANTalonID);
	topWheel->SetFeedbackDevice(CANTalon::QuadEncoder);
	topWheel->ConfigEncoderCodesPerRev(250);//change to 250 before using
	lowerWheel->SetFeedbackDevice(CANTalon::QuadEncoder);
	lowerWheel->ConfigEncoderCodesPerRev(250);//change to 250 before using
	topWheel->SetControlMode(CANSpeedController::kSpeed);
	lowerWheel->SetControlMode(CANSpeedController::kSpeed);
	topWheel->Set(0);
	lowerWheel->Set(0);

	//set closed loop gains
	topWheel->SelectProfileSlot(0);
	lowerWheel->SelectProfileSlot(0);
	topWheel->SetPID(0.0f, 0, 0.0f, 0);
	lowerWheel->SetPID(0.0f, 0, 0.0f, 0);
	topWheel->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	lowerWheel->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	topWheel->ConfigPeakOutputVoltage(+12.0f, -12.0f);
	lowerWheel->ConfigPeakOutputVoltage(+12.0f, -12.0f);

}

void Shooter::ShooterDisable() {

	lowerWheel->Set(0);
	topWheel->Set(0);
	exsole->Set(DoubleSolenoid::Value::kReverse);
}

void Shooter::ShooterAutoInit() {

}

void Shooter::ShooterAutoPeriodic() {
	/*  Old code used to test switches
	 cout << "Limit Switches: ";
	 cout << shooterLimitSwitch->Get() << " ";
	 cout << shooterLimitSwitch1->Get() << " ";
	 cout << shooterLimitSwitch2->Get() << endl;
	 */
}

void Shooter::ShooterTeleopInit() {



}

void Shooter::ShooterTeleopPeriodic() {
	switch (firePhase) //meant to fire then reset
	{
	case 0: //check if a ball is loaded
cout << "0" << endl;
		if (shooterLimitSwitch->Get()) {

			firePhase++;

		}

		break;
	case 1: //check if launch button pressed
		cout << "1" << endl;
		shooterButtonvalue = shooterJoystick->GetRawButton(shooterTrigger);
		if (shooterButtonvalue) {
			firePhase++;
			ceeout = 0;
			shooterButtonvalue = false;
		}

		break;
	case 2: //spin up flywheels
		cout << "2" << endl;
		topWheel->Set(targetSpeed);
		lowerWheel->Set(targetSpeed);
		//note == replace "true" in the next line with code that determines if the shooter motors are up to speed.
		actualTopSpeed = topWheel->GetSpeed();
		actualLowerSpeed = lowerWheel->GetSpeed();
		 cout << "Top Speed: " << actualTopSpeed << endl;
		 cout << "Lower Speed: " << actualLowerSpeed << endl;
		if (within5percent(targetSpeed,actualTopSpeed) and within5percent(targetSpeed,actualLowerSpeed)) {
			SmartDashboard::PutBoolean("DB/Button 3", true);
			firePhase++;
		}

		break;

	case 3: //fire piston

		exsole->Set(DoubleSolenoid::Value::kForward);

		if (!shooterLimitSwitch->Get()) {

			firePhase++;
		}

		break;

	case 4:

		timer = timer + 1;

		if (timer == 150) {

			firePhase++;
		}
		break;

	case 5: //reset piston , deactivate flywheels

		topWheel->Set(0);
		lowerWheel->Set(0);
		exsole->Set(DoubleSolenoid::Value::kReverse);
		firePhase = 0;
		break;
	}
}

bool Shooter::within5percent (float target,float actual)
{
	float difference = 1.0 - (actual/target);
	if (difference < .05 and difference > -.05)
	{
		return true;
	}else{
		return false;
	}
}
