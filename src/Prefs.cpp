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
	prefs->PutInt("shooterSolenoidExtend", 0);
	prefs->PutInt("shooterSolenoidRetract", 1);
	prefs->PutInt("armSolenoidExtendPCMPort", 2);
	prefs->PutInt("armSolenoidRetractPCMPort", 3);
	prefs->PutInt("armSolenoidExtendPCMPort2", 4);
	prefs->PutInt("armSolenoidRetractPCMPort2", 5);
	prefs->PutInt("armSolenoidExtendPCMPort3", 6);
	prefs->PutInt("armSolenoidRetractPCMPort3", 7);

	//ENCODEr stuffS
	prefs->PutFloat("shooterTargetSpeed", 1.0f);
	prefs->PutFloat("collectTargetSpeed", 0.5f);

	// ramp rate
	prefs->PutDouble("rampRate", 12.0);
	// CANTalon IDs
	prefs->PutInt("frontRightMotorCANTalonID", 3);
	prefs->PutInt("frontLeftMotorCANTalonID", 9);
	prefs->PutInt("backRightMotorCANTalonID", 2);
	prefs->PutInt("backLeftMotorCANTalonID", 8);
	prefs->PutInt("collectConveyorMotorCANTalonID", 4);
	prefs->PutInt("liftMotorCANTalonID", 1);
	prefs->PutInt("shooterTopMotorCANTalonID", 7);
	prefs->PutInt("shooterBottomMotorCANTalonID", 6);


	// driveJoyStick IDs
	prefs->PutInt("driveJoystickNumber", 0); //drive joystick
	prefs->PutInt("leftAxis", 1);
	prefs->PutInt("rightAxis", 3);
	prefs->PutInt("halfSpeedButton", 6);

	// auxJoyStick IDs
	prefs->PutInt("auxJoystickNumber", 1);//operator joystick
	prefs->PutInt("collectConveyerInButton", 1);
	prefs->PutInt("collectConveyerOutButton", 3);
	prefs->PutInt("shooterTrigger", 8);
	prefs->PutInt("liftUpButton", 4);
	prefs->PutInt("liftDownButton", 2);
	prefs->PutInt("armTrigger2", 9); //may need to change depending on pcm ports
	prefs->PutInt("altIntakeIn", 5);
	prefs->PutInt("altIntakeOut", 7);
	prefs->PutInt("flashlight", 6);
	prefs->PutInt("piston", 10);

}
