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
	prefs->PutInt("armSolenoidExtendPCMPort", 2);
	prefs->PutInt("armSolenoidRetractPCMPort", 3);
	prefs->PutInt("shooterSolenoidExtend", 0);
	prefs->PutInt("shooterSolenoidRetract", 1);

	//ENCODEr stuffS
	prefs->PutDouble("wheelCircumfrence", 23);
	prefs->PutFloat("shooterTargetSpeed", 10.0f);
	prefs->PutFloat("collectTargetSpeed", 1.0f);

	// CANTalon IDs
	prefs->PutInt("frontRightMotorCANTalonID", 3);
	prefs->PutInt("frontLeftMotorCANTalonID", 9);
	prefs->PutInt("backRightMotorCANTalonID", 2);
	prefs->PutInt("backLeftMotorCANTalonID", 8);
	prefs->PutInt("collectConveyorMotorCANTalonID", 4); //need to check this one
	prefs->PutInt("liftMotorCANTalonID", 1);
	prefs->PutInt("shooterTopMotorCANTalonID", 7);
	prefs->PutInt("shooterBottomMotorCANTalonID", 6);

	// Limit Switch IDs
	prefs->PutInt("liftLimitSwitchLow", 1); //not implemented on robot yet
	prefs->PutInt("liftLimitSwitchHigh", 0);

	// driveJoyStick IDs
	prefs->PutInt("driveJoystickNumber", 0);
	prefs->PutInt("leftAxis", 1);
	prefs->PutInt("rightAxis", 3);
	prefs->PutInt("armTrigger", 5);
	prefs->PutInt("halfSpeedButton", 6);

	// auxJoyStick IDs
	prefs->PutInt("auxJoystickNumber", 1);
	prefs->PutInt("collectConveyerInButton", 1);
	prefs->PutInt("collectConveyerOutButton", 3);
	prefs->PutInt("shooterTrigger", 8);
	prefs->PutInt("liftUpButton", 4);
	prefs->PutInt("liftDownButton", 2);

	// Camera Prefs
	prefs->PutInt("Brightness", 40); // not on robot yet

}
