#include "WPILib.h"
#include "Collect.h"
#include <iostream>
#include <cmath>

void Collect::CollectInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	collectConveyorMotorCANTalonID = prefs->GetInt("collectConveyorMotorCANTalonID");
	collectArmMotorCANTalonID =	prefs->GetInt("collectArmMotorCANTalonID");
	shooterBottomMotorCANTalonID = prefs->GetInt("shooterBottomMotorCANTalonID");
	collectBallDetectSwitch1 = prefs->GetInt("collectBallDetectSwitch1");
	collectBallDetectSwitch2 = prefs->GetInt("collectBallDetectSwitch2");
	collectConveyerUpSwitch = prefs->GetInt("collectConveyerUpSwitch");
	collectConveyerDownSwitch = prefs->GetInt("collectConveyerDownSwitch");
	auxJoystickNumber = prefs->GetInt("auxJoystickNumber");
	collectConveyerInButton = prefs->GetInt("collectConveyerInButton");
	collectConveyerOutButton = prefs->GetInt("collectConveyerOutButton");
	collectConveyerUpButton = prefs->GetInt("collectConveyerUpButton");
	collectConveyerDownButton = prefs->GetInt("collectConveyerDownButton");
	collectFinalLoadButton = prefs->GetInt("collectFinalLoadButton");


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
