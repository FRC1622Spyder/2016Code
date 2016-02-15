#include "WPILib.h"
#include "Auto.h"
#include <cmath>
#include <iostream>

void Auto::AutoInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 7);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 7);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 7);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 7);

	// assign motors and drive joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);

	// setup motors
	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);
}

void Auto::AutoDisable() {

	leftBackMotor->Set(0);
	leftFrontMotor->Set(0);
	rightBackMotor->Set(0);
	rightFrontMotor->Set(0);

}

void Auto::AutoAutoInit() {
	autoLoopCounter = 0;
}

void Auto::AutoAutoPeriodic() {

	// Autonomous code goes here

	if(autoLoopCounter < 250) {
		allSpeedSet(.2);
	}
	else {
		allSpeedSet(0);
	}
	autoLoopCounter++;

}

void Auto::AutoTeleopInit() {

}

void Auto::AutoTeleopPeriodic() {

}

void Auto::allSpeedSet(double s) {
	leftBackMotor->Set(s);
	leftFrontMotor->Set(s);
	rightBackMotor->Set(s);
	rightFrontMotor->Set(s);

}

void Auto::leftSpeedSet(double s) {
	leftBackMotor->Set(s);
	leftFrontMotor->Set(s);
}

void Auto::rightSpeedSet(double s) {
	rightBackMotor->Set(s);
	rightFrontMotor->Set(s);

}
