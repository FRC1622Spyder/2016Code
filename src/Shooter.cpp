#include "WPILib.h"
#include "Shooter.h"
#include <iostream>
#include <cmath>
using namespace std;

void Shooter::ShooterInit() {

	prefs = Preferences::GetInstance();
	pcmCANID = prefs->GetInt("pcmCANID");
	shooterSolenoidExtend = prefs->GetInt("shooterSolenoidExtend");
	shooterSolenoidRetract = prefs->GetInt("shooterSolenoidRetract");
	shooterTopMotorCANTalonID = prefs->GetInt("shooterTopMotorCANTalonID");
	shooterBottomMotorCANTalonID = prefs->GetInt(
			"shooterBottomMotorCANTalonID");
	collectConveyorMotorCANTalonID = prefs->GetInt(
			"collectConveyorMotorCANTalonID");
	auxJoystickNumber = prefs->GetInt("auxJoystickNumber");
	shooterTrigger = prefs->GetInt("shooterTrigger");
	firePhase = 0;
	shooterJoystick = new Joystick(auxJoystickNumber);
	shooterButtonvalue = false;
	exsole = new DoubleSolenoid(pcmCANID, shooterSolenoidExtend,
			shooterSolenoidRetract);
	collectConveyerInButton = prefs->GetInt("collectConveyerInButton");
	collectConveyerOutButton = prefs->GetInt("collectConveyerOutButton");

	timer = 0;
	targetSpeed = prefs->GetFloat("shooterTargetSpeed", 10.0f);
	actualTopSpeed = 0.0f;
	actualLowerSpeed = 0.0f;

	//Set up wheels
	topWheel = new CANTalon(shooterTopMotorCANTalonID);
	lowerWheel = new CANTalon(shooterBottomMotorCANTalonID);
	collectConveyorMotor = new CANTalon(collectConveyorMotorCANTalonID);

	// set up encoders
	topWheel->SetFeedbackDevice(CANTalon::QuadEncoder);
	topWheel->ConfigEncoderCodesPerRev(250);
	lowerWheel->SetFeedbackDevice(CANTalon::QuadEncoder);
	lowerWheel->ConfigEncoderCodesPerRev(250);
	lowerWheel->SetSensorDirection(true);

	// set control mode to closed-loop velocity
	topWheel->SetControlMode(CANSpeedController::kSpeed);
	lowerWheel->SetControlMode(CANSpeedController::kSpeed);
	collectConveyorMotor->SetControlMode(CANSpeedController::kPercentVbus);
	collectVBusValue = 0.5; // TODO need to figure out what the right speed is for this. (Percent VBus)

	//set speeds to 0
	topWheel->Set(0);
	lowerWheel->Set(0);

	//set voltages
	topWheel->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	lowerWheel->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	topWheel->ConfigPeakOutputVoltage(+12.0f, -12.0f);
	lowerWheel->ConfigPeakOutputVoltage(+12.0f, -12.0f);

	//set closed loop gains
	//TODO == play with these to get the speed consistent
	topWheel->SelectProfileSlot(0);
	lowerWheel->SelectProfileSlot(0);
	topWheel->SetPID(0.0f, 0.0f, 0.0f, 200.0f);
	lowerWheel->SetPID(0.0f, 0.0f, 0.0f, 200.0f);

}

void Shooter::ShooterDisable() {

	lowerWheel->Set(0);
	topWheel->Set(0);
	exsole->Set(DoubleSolenoid::Value::kReverse);
	collectConveyorMotor->Set(0.0f);
}

void Shooter::ShooterAutoInit() {

}

void Shooter::ShooterAutoPeriodic() {

}

void Shooter::ShooterTeleopInit() {

}

void Shooter::ShooterTeleopPeriodic() {
	switch (firePhase) //meant to fire then reset
	{
	case 0: //check if a ball is loaded
//		cout << "0" << endl;
		timer = 0;
		if (true) {
			firePhase++;
		}

		break;

	case 1: //check if launch button pressed
//		cout << "1" << endl;
		// If in button is pressed, go in
		if (shooterJoystick->GetRawButton(collectConveyerInButton)) {
			collectConveyorMotor->Set(collectVBusValue);
			collectTargetSpeed = prefs->GetFloat("collectTargetSpeed"); // get this speed from prefs file
			lowerWheel->Set(collectTargetSpeed);
		}

		// If out button is pressed, go out
		else if (shooterJoystick->GetRawButton(collectConveyerOutButton)) {
			collectConveyorMotor->Set(-1 * collectVBusValue);
			collectTargetSpeed = prefs->GetFloat("collectTargetSpeed"); // get this speed from prefs file
			lowerWheel->Set(-1 * collectTargetSpeed);
		}

		else {
			collectConveyorMotor->Set(0);
			lowerWheel->Set(0);
		}

		shooterButtonvalue = shooterJoystick->GetRawButton(shooterTrigger);
		if (shooterButtonvalue) {
			firePhase++;
			ceeout = 0;
			shooterButtonvalue = false;
		}

		break;
	case 2: //spin up flywheels
		cout << "2" << endl;
		targetSpeed = prefs->GetFloat("shooterTargetSpeed"); // get new target speed from prefs file in case changed through dashboard
		topWheel->Set(targetSpeed);
		lowerWheel->Set(targetSpeed);
		actualTopSpeed = topWheel->GetSpeed();
		actualLowerSpeed = lowerWheel->GetSpeed();
		cout << "Top Speed: " << actualTopSpeed << endl;
		cout << "Lower Speed: " << actualLowerSpeed << endl;
		timer = timer + 1;
		if (timer >= 150) {
			timer = 0;
			firePhase++;
		} else if (WithinPercent(targetSpeed, actualTopSpeed)
				and WithinPercent(targetSpeed, actualLowerSpeed)) {
			timer = 0;
			firePhase++;
		}
		break;

	case 3: //fire piston

		exsole->Set(DoubleSolenoid::Value::kForward);

		if (true) {
			firePhase++;
		}

		break;

	case 4: // wait three seconds to make sure ball is gone

		timer = timer + 1;
		if (timer >= 150) {
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

// checks whether actual speed is within a certain percentage of target speed
bool Shooter::WithinPercent(float target, float actual) {
	float difference = 1.0 - (actual / target);
	// put percentage in next line
	if (difference < .05 and difference > -.05) {
		return true;
	} else {
		return false;
	}
}
