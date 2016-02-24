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
	prefs->PutInt("shooterSolenoidRetract", 3);

	//ENCODEr stuffS
	prefs->PutDouble("wheelCircumfrence", 23);
	prefs->PutFloat("shooterTargetSpeed", 10);

	// CANTalon IDs
	prefs->PutInt("frontRightMotorCANTalonID", 3);
	prefs->PutInt("frontLeftMotorCANTalonID", 9);
	prefs->PutInt("backRightMotorCANTalonID", 2);
	prefs->PutInt("backLeftMotorCANTalonID", 8);
	prefs->PutInt("collectConveyorMotorCANTalonID", 4); //not implemented on robot yet
	prefs->PutInt("collectArmMotorCANTalonID", 5); //not implemented on robot yet
	prefs->PutInt("liftMotorCANTalonID", 1);  //not implemented on robot yet
	prefs->PutInt("shooterTopMotorCANTalonID", 7);  //not implemented on robot yet
	prefs->PutInt("shooterBottomMotorCANTalonID", 6);  //not implemented on robot yet

	// Limit Switch IDs
	prefs->PutInt("liftLimitSwitchLow", 0); //yet to be mapped
	prefs->PutInt("liftLimitSwitchMed", 1); //yet to be mapped
	prefs->PutInt("liftLimitSwitchHigh", 2); //yet to be mapped
	prefs->PutInt("shooterBallDetectSwitch", 3);//yet to be mapped
	prefs->PutInt("collectBallDetectSwitch1", 4);//yet to be mapped
	prefs->PutInt("collectBallDetectSwitch2", 5);//yet to be mapped
	prefs->PutInt("collectConveyerUpSwitch", 6);//yet to be mapped
	prefs->PutInt("collectConveyerDownSwitch", 7);//yet to be mapped

	// driveJoyStick IDs
	prefs->PutInt("driveJoystickNumber", 0);//yet to be mapped
	prefs->PutInt("leftAxis", 1);//yet to be mapped
	prefs->PutInt("rightAxis", 3);//yet to be mapped
	prefs->PutInt("armTrigger", 5);//yet to be mapped
	prefs->PutInt("liftUpButton", 4);//yet to be mapped
	prefs->PutInt("liftDownButton", 2);//yet to be mapped
	prefs->PutInt("shooterTrigger", 8);//yet to be mapped
	prefs->PutInt("halfSpeedButton", 6);//yet to be mapped

	// auxJoyStick IDs
	prefs->PutInt("auxJoystickNumber", 1);//yet to be mapped
	prefs->PutInt("collectConveyerInButton", 1);//yet to be mapped
	prefs->PutInt("collectConveyerOutButton", 3);//yet to be mapped
	prefs->PutInt("collectConveyerUpButton", 4);//yet to be mapped
	prefs->PutInt("collectConveyerDownButton", 2);//yet to be mapped
	prefs->PutInt("collectFinalLoadButton", 8);//yet to be mapped
	prefs->PutInt("cameraSendButton", 5);//yet to be mapped

	// Camera Prefs
	prefs->PutInt("Brightness", 40);//yet to be mapped


}
