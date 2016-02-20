#include "WPILib.h"
#include "Auto.h"
#include <cmath>
#include <iostream>

using namespace std;

void Auto::AutoInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 2);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 3);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 5);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 6);
	wheelCircumfrence = prefs->GetDouble("wheelCircumfrence", 23);
	driveRatio = 8.45;

	// assign motors and drive joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);

	// setup motors
	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);

	//Set back motors to follow front
	rightBackMotor->SetControlMode(CANSpeedController::kFollower);
	rightBackMotor->Set(2);

	leftBackMotor->SetControlMode(CANSpeedController::kFollower);
	leftBackMotor->Set(5);

	//Setup encoders
	rightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightFrontMotor->ConfigEncoderCodesPerRev(20);

	leftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	leftFrontMotor->ConfigEncoderCodesPerRev(20);
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

	cout << "Left: " << leftFrontMotor->GetPosition() << endl;
	cout << "Right: " << rightFrontMotor->GetPosition() << endl;

	cout << "Left Speed: " << leftFrontMotor->GetSpeed() << endl;
	cout << "Right Speed: " << rightFrontMotor->GetSpeed() << endl;

	double inches = 12;


	if (leftFrontMotor->GetPosition() < (inches/wheelCircumfrence)*driveRatio) {
		leftFrontMotor->Set(.2);
	} else {
		leftFrontMotor->Set(0);
	}

	if (rightFrontMotor->GetPosition() < (inches/wheelCircumfrence)*driveRatio) {
		rightFrontMotor->Set(.2);
	} else {
		rightFrontMotor->Set(0);
	}

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
