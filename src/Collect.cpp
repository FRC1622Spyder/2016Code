#include "WPILib.h"
#include "Config.h"
#include "Collect.h"
#include <iostream>
#include <cmath>

void Collect::CollectInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	collectConveyorMotorCANTalonID = prefs->GetInt(
			"collectConveyorMotorCANTalonID");
	shooterBottomMotorCANTalonID = prefs->GetInt(
			"shooterBottomMotorCANTalonID");
	auxJoystickNumber = prefs->GetInt("auxJoystickNumber");
	collectConveyerInButton = prefs->GetInt("collectConveyerInButton");
	collectConveyerOutButton = prefs->GetInt("collectConveyerOutButton");

	// assign motors and joystick
	collectConveyorMotor = new CANTalon(collectConveyorMotorCANTalonID);
	lowerWheel = new CANTalon(shooterBottomMotorCANTalonID);
	joy = new Joystick(auxJoystickNumber);

	// setup motors
//	collectArmMotor->SetInverted(true);  // TODO need to figure out if this motor needs to be inverted
	collectConveyorMotor->SetControlMode(CANSpeedController::kPercentVbus);
	collectVBusValue = 0.5; // TODO need to figure out what the right speed is for this. (Percent VBus)


	lowerWheel->SetControlMode(CANSpeedController::kSpeed);
	lowerWheel->Set(0);

	lowerWheel->SetFeedbackDevice(CANTalon::QuadEncoder);
	lowerWheel->ConfigEncoderCodesPerRev(250);

	lowerWheel->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	lowerWheel->ConfigPeakOutputVoltage(+12.0f, -12.0f);

	//set closed loop gains
	//TODO == play with these to get the speed consistent
	lowerWheel->SelectProfileSlot(0);
	lowerWheel->SetPID(0.0f, 0.0f, 0.0f, 200.0f);

}
void Collect::CollectDisable() {

	collectConveyorMotor->Set(0.0f);
	lowerWheel->Set(0);

}

void Collect::CollectAutoInit() {

}

void Collect::CollectAutoPeriodic() {

}

void Collect::CollectTeleopInit() {

}

void Collect::CollectTeleopPeriodic() {

	// If in button is pressed, go in
	if (joy->GetRawButton(collectConveyerInButton)) {
		collectConveyorMotor->Set(collectVBusValue);
		collectTargetSpeed = prefs->GetFloat("collectTargetSpeed"); // get this speed from prefs file
		lowerWheel->Set(collectTargetSpeed);
	}

	// If out button is pressed, go out
	else if (joy->GetRawButton(collectConveyerOutButton)) {
		collectConveyorMotor->Set(-1 * collectVBusValue);
		collectTargetSpeed = prefs->GetFloat("collectTargetSpeed"); // get this speed from prefs file
		lowerWheel->Set(-1 * collectTargetSpeed);
	}

	else {
		collectConveyorMotor->Set(0);
//		lowerWheel->Set(0);
	}

}
