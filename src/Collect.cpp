#include "WPILib.h"
#include "Collect.h"
#include <iostream>
#include <cmath>

void Collect::CollectInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	collectConveyorMotorCANTalonID = prefs->GetInt("collectConveyorMotorCANTalonID", 5);
	collectArmMotorCANTalonID =	prefs->GetInt("collectArmMotorCANTalonID", 6);
	shooterBottomMotorCANTalonID = prefs->GetInt("shooterBottomMotorCANTalonID", 9);
	collectBallDetectSwitch1 = prefs->GetInt("collectBallDetectSwitch1", 4);
	collectBallDetectSwitch2 = prefs->GetInt("collectBallDetectSwitch2", 5);
	collectConveyerUpSwitch = prefs->GetInt("collectConveyerUpSwitch", 6);
	collectConveyerDownSwitch = prefs->GetInt("collectConveyerDownSwitch", 7);
	auxJoystickNumber = prefs->GetInt("auxJoystickNumber", 1);
	collectConveyerInButton = prefs->GetInt("collectConveyerInButton", 1);
	collectConveyerOutButton = prefs->GetInt("collectConveyerOutButton", 3);
	collectConveyerUpButton = prefs->GetInt("collectConveyerUpButton", 4);
	collectConveyerDownButton = prefs->GetInt("collectConveyerDownButton", 2);
	collectFinalLoadButton = prefs->GetInt("collectFinalLoadButton", 8);


	// assign motors and joystick
	collectConveyorMotor = new CANTalon(collectConveyorMotorCANTalonID);
	collectArmMotor = new CANTalon(collectArmMotorCANTalonID);
	shooterBottomMotor = new CANTalon(shooterBottomMotorCANTalonID);
	joy = new Joystick(auxJoystickNumber);


	// setup motors
//	collectArmMotor->SetInverted(true);
}
void Collect::CollectDisable() {

	collectConveyorMotor->Set(0);
	collectArmMotor->Set(0);
	shooterBottomMotor->Set(0);
}


/**
 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
 * below the Gyro
 *
 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
 * If using the SendableChooser make sure to add them to the chooser code above as well.
 */
void Collect::CollectAutoInit() {

}

void Collect::CollectAutoPeriodic() {

}

void Collect::CollectTeleopInit() {

}

void Collect::CollectTeleopPeriodic() {

	// If up button is pressed and up limit not reached, go up
	if (joy->GetRawButton(collectConveyerUpButton) && !(joy->GetRawButton(collectConveyerUpSwitch))) {
		collectConveyorMotor->Set(.5);
	}

	// If down button is pressed and down limit not reached, go down
	if (joy->GetRawButton(collectConveyerDownButton) && !(joy->GetRawButton(collectConveyerDownSwitch))) {
		collectConveyorMotor->Set(-.5);
	}

	// If in button is pressed, go in
	if (joy->GetRawButton(collectConveyerInButton)) {
		collectConveyorMotor->Set(.5);
	}

	// If out button is pressed, go out
	if (joy->GetRawButton(collectConveyerOutButton)) {
		collectConveyorMotor->Set(-.5);
	}

	// If final load button is pressed, load final
	if (joy->GetRawButton(collectConveyerOutButton)) {
		shooterBottomMotor->Set(-.5);
	}


}
