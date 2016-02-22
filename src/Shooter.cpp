#include "WPILib.h"
#include "Shooter.h"
#include <iostream>
using namespace std;

void Shooter::ShooterInit() {

	prefs = Preferences::GetInstance();
	pcmCANID = prefs->GetInt("pcmCANID", 7);
	shooterSolenoidExtend = prefs->GetInt("shooterSolenoidExtend", 2);
	shooterSolenoidRetract = prefs->GetInt("shooterSolenoidRetract", 2);
	shooterTopMotorCANTalonID = prefs->GetInt("shooterTopMotorCANTalonID", 8);
	shooterBottomMotorCANTalonID = prefs->GetInt("shooterBottomMotorCANTalonID",9);
	shooterBallDetectSwitch = prefs->GetInt("shooterBallDetectSwitch", 3);
	driveJoystickNumber = prefs->GetInt("driveJoystickNumber", 0);
	shooterTrigger = prefs->GetInt("shooterTrigger", 3);

	firePhase = 0;
	shooterJoystick = new Joystick(driveJoystickNumber);
	shooterButtonvalue = false;
	exsole = new DoubleSolenoid(pcmCANID, shooterSolenoidExtend, shooterSolenoidRetract);
	rightTimer = new Timer();
	shooterLimitSwitch = new DigitalInput(shooterBallDetectSwitch);
	topWheel = new CANTalon(shooterTopMotorCANTalonID);
	lowerWheel = new CANTalon(shooterBottomMotorCANTalonID);
	timer = 0;

}

void Shooter::ShooterDisable() {

	lowerWheel->Set(0);
	topWheel->Set(0);
	exsole->Set(false);
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

		if (shooterLimitSwitch->Get()) {

			firePhase++;

		}

		break;
	case 1: //check if launch button pressed

		shooterButtonvalue = shooterJoystick->GetRawButton(shooterTrigger);
		if (shooterButtonvalue) {
			firePhase++;
			ceeout = 0;
			shooterButtonvalue = false;
		}

		break;
	case 2: //spin up flywheels

		topWheel->Set(.2);
		lowerWheel->Set(.2);
		if (1 == 1) {
			SmartDashboard::PutBoolean("DB/Button 3", true);
			firePhase++;
		}

		break;
	case 3: //check if launch button pressed

		//note == replace "true" in the next line with code that determines if the shooter motors are up to speed.
		if (true) {
			firePhase++;
			ceeout = 0;
		}

		break;
	case 4: //fire piston

		exsole->Set(DoubleSolenoid::Value::kForward);

		if (!shooterLimitSwitch->Get()) {

			topWheel->Set(0);
			lowerWheel->Set(0);
			firePhase++;
		}

		break;

	case 5:

		timer = timer + 1;

		if (timer == 150) {

			firePhase++;
		}
		break;

	case 6: //reset piston , deactivate flywheels

		exsole->Set(DoubleSolenoid::Value::kReverse);
		firePhase = 0;
		break;
	}
}
