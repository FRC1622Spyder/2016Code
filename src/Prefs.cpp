/*
 * Prefs.cpp
 *
 *  Created on: Feb 13, 2016
 *      Author: Admin
 */

#include "WPILib.h"
#include "Prefs.h"

// List of all configurable preferences and default values.
// Default values will be overwritten by values loaded from driver station dashboard

void Prefs::PrefsInit() {
	prefs = Preferences::GetInstance();

	// Pneumatic Control Module (PCM) IDs
	prefs->PutInt("pcmCANID", 7);
	prefs->PutInt("armSolenoidExtendPCMPort", 0);
	prefs->PutInt("armSolenoidRetractPCMPort", 1);
	prefs->PutInt("shooterSolenoidExtend", 2);

	//ENCODEr stuffS
	prefs->PutDouble("wheelCircumfrence", 23);

	// CANTalon IDs
	prefs->PutInt("frontRightMotorCANTalonID", 4);
	prefs->PutInt("frontLeftMotorCANTalonID", 3);
	prefs->PutInt("backRightMotorCANTalonID", 5);
	prefs->PutInt("backLeftMotorCANTalonID", 1);
	prefs->PutInt("collectConveyorMotorCANTalonID", 2); //not implemented on robot yet
	prefs->PutInt("collectArmMotorCANTalonID", 2); //not implemented on robot yet
	prefs->PutInt("liftMotorCANTalonID", 2);  //not implemented on robot yet
	prefs->PutInt("shooterTopMotorCANTalonID", 2);  //not implemented on robot yet
	prefs->PutInt("shooterBottomMotorCANTalonID", 2);  //not implemented on robot yet

	// Limit Switch IDs
	prefs->PutInt("liftLimitSwitchLow", 0);
	prefs->PutInt("liftLimitSwitchMed", 1);
	prefs->PutInt("liftLimitSwitchHigh", 2);
	prefs->PutInt("shooterBallDetectSwitch", 3);
	prefs->PutInt("collectBallDetectSwitch1", 4);
	prefs->PutInt("collectBallDetectSwitch2", 5);
	prefs->PutInt("collectConveyerUpSwitch", 6);
	prefs->PutInt("collectConveyerDownSwitch", 7);

	// driveJoyStick IDs
	prefs->PutInt("driveJoystickNumber", 0);
	prefs->PutInt("leftAxis", 1);
	prefs->PutInt("rightAxis", 3);
	prefs->PutInt("armTrigger", 5);
	prefs->PutInt("liftUpButton", 4);
	prefs->PutInt("liftDownButton", 2);
	prefs->PutInt("shooterTrigger", 8);
	prefs->PutInt("halfSpeedButton", 6);

	// auxJoyStick IDs
	prefs->PutInt("auxJoystickNumber", 1);
	prefs->PutInt("collectConveyerInButton", 1);
	prefs->PutInt("collectConveyerOutButton", 3);
	prefs->PutInt("collectConveyerUpButton", 4);
	prefs->PutInt("collectConveyerDownButton", 2);
	prefs->PutInt("collectFinalLoadButton", 8);
	prefs->PutInt("cameraSendButton", 5);

	// Camera Prefs
	prefs->PutInt("Brightness", 40);

}
