#include "WPILib.h"
#include "Lift.h"
#include <iostream>

using namespace std;

void Lift::LiftInit() {
	prefs = Preferences::GetInstance();
	liftMotorCANTalonID = prefs->GetInt("liftMotorCANTalonID", 7);
	liftLimitSwitchLow = prefs->GetInt("liftLimitSwitchLow", 0);
	liftLimitSwitchMed = prefs->GetInt("liftLimitSwitchMed", 1);
	liftLimitSwitchHigh = prefs->GetInt("liftLimitSwitchHigh", 2);
	liftUpButton = prefs->GetInt("liftUpButton", 4);
	liftDownButton = prefs->GetInt("liftDownButton", 2);
	driveJoystickNumber = prefs->GetInt("joystickNumber", 0);

	stick = new Joystick(driveJoystickNumber);
	liftLimitSwitch1 = new DigitalInput(liftLimitSwitchLow);
	liftLimitSwitch2 = new DigitalInput(liftLimitSwitchMed);
	liftLimitSwitch3 = new DigitalInput(liftLimitSwitchHigh);
	liftMotor = new CANTalon(liftMotorCANTalonID);
	state = 0;
	logOnce = true;

}

void Lift::LiftDisable() {

	liftMotor->Set(0);

}

void Lift::LiftAutoInit() {

}

void Lift::LiftAutoPeriodic() {

}

void Lift::LiftTeleopInit() {

}

void Lift::LiftTeleopPeriodic() {

	// If up button is pressed and up limit not reached, go up
	if (stick->GetRawButton(liftUpButton) && !(stick->GetRawButton(liftLimitSwitchHigh))) {
		liftMotor->Set(.5);
	}

	// If down button is pressed and down limit not reached, go down
	else if (stick->GetRawButton(liftDownButton) && !(stick->GetRawButton(liftLimitSwitchLow))) {
		liftMotor->Set(-.5);
	}

	else {
		liftMotor->Set(0);
	}


	/*
	switch (state) {
	case 0:
		// Wait for Up button
		if (logOnce) {
			cout << "Lift: State: " << state << endl;
			cout << "Lift: Waiting For Up Button!\n";
			logOnce = false;
		}
		if (stick->GetRawButton(liftUpButton)) {
			state = 1;
			logOnce = true;
			break;
		}
		break;
	case 1:
		// Go Up Until Switch 2, Stop
		if (logOnce) {
			cout << "Lift: State: " << state << endl;
			cout << "Lift: Going Up!\n"; // (Replace)
			logOnce = false;
		}
		liftMotor->Set(.6);
		cout << "Lift: " << liftLimitSwitch2->Get() << endl;
		if (liftLimitSwitch2->Get()) {
			cout << "Lift: Motor Stopping!\n"; // (Replace)
			liftMotor->Set(0);
			state = 2;
			logOnce = true;
			break;
		}
		break;
	case 2:
		// Wait for up button
		if (logOnce) {
			cout << "Lift: State: " << state << endl;
			cout << "Lift: Waiting For Up Button!\n";
			logOnce = false;
		}
		if (stick->GetRawButton(liftUpButton)) {
			state = 3;
			logOnce = true;
			break;
		}
		break;
	case 3:
		// Go up until switch 3, Stop
		if (logOnce) {
			cout << "Lift: State: " << state << endl;
			cout << "Lift: Going Up!\n";
			logOnce = false;
		}
		liftMotor->Set(.6);
		if (liftLimitSwitch3->Get()) {
			cout << "Lift: Motor Stopping!\n";
			liftMotor->Set(0);
			state = 4;
			logOnce = true;
			break;
		}
		break;
	case 4:
		// Wait for down Button
		if (logOnce) {

			cout << "Lift: State: " << state << endl;
			cout << "Lift: Waiting For Down Button!\n";
			logOnce = false;
		}
		if (stick->GetRawButton(liftDownButton)) {
			state = 5;
			logOnce = true;
			break;
		}
		break;
	case 5:
		// go down until switch 2, stop
		if (logOnce) {
			cout << "Lift: State: " << state << endl;
			cout << "Lift: Going Down!\n";
			logOnce = false;
		}
		liftMotor->Set(-.6);
		if (liftLimitSwitch2->Get()) {
			cout << "Lift: Motor Stopping!\n";
			liftMotor->Set(0);
			state = 6;
			logOnce = true;
			break;
		}
		break;
	case 6:
		// go down until switch 2, stop
		if (logOnce) {
			cout << "Lift: State: " << state << endl;
			cout << "Lift: Done!\n";
			logOnce = false;
		}
		liftMotor->Set(0);
		break;
	}
*/

}
