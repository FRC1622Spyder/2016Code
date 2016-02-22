#include "WPILib.h"
#include <cmath>
#include "Drive.h"
#include <iostream>

using namespace std;

void Drive::DriveInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 4);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 5);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 3);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 1);
	driveJoystickNumber = prefs->GetInt("joystickNumber", 0);
	leftAxis = prefs->GetInt("leftAxis", 1);
	rightAxis = prefs->GetInt("rightAxis", 3);
	wheelCircumfrence = prefs->GetDouble("wheelCircumfrence", 23);
	driveRatio = 8.45;

	// assign motors and joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);
	joy = new Joystick(driveJoystickNumber);

	// setup motors
	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);

	//Set back motors to follow front
	leftFrontMotor->SetControlMode(CANSpeedController::kFollower);
	leftFrontMotor->Set(1);

	rightFrontMotor->SetControlMode(CANSpeedController::kFollower);
	rightFrontMotor->Set(5);

	//Setup encoders
	leftBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	leftBackMotor->ConfigEncoderCodesPerRev(20);

	rightBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightBackMotor->ConfigEncoderCodesPerRev(20);

}

void Drive::DriveDisable() {

	//leftBackMotor->Set(0);
	//leftFrontMotor->Set(0);
	//rightBackMotor->Set(0);
	//rightFrontMotor->Set(0);

}

void Drive::DriveAutoInit() {

}

void Drive::DriveAutoPeriodic() {

}

void Drive::DriveTeleopInit() {
	leftBackMotor->SetPosition(0);
	rightBackMotor->SetPosition(0);

}

void Drive::DriveTeleopPeriodic() {
	double leftVal;
	double rightVal;
	bool halfButtonValue = joy->GetRawButton(prefs->GetInt("halfSpeedButton"));

	leftVal = joy->GetRawAxis(leftAxis);
	rightVal = joy->GetRawAxis(rightAxis);

	cout << "Drive Left: " << leftVal << endl;
	cout << "Drive Right: " << rightVal << endl;

	if (halfButtonValue) {
		leftVal = leftVal / 2;
		rightVal = rightVal / 2;
	}

	leftVal = fabs(leftVal) > 0.1 ? leftVal : 0;
	rightVal = fabs(rightVal) > 0.1 ? rightVal : 0;

	leftVal = leftVal * .8;
	rightVal = rightVal * .8;

	leftSpeedSet(leftVal);
	rightSpeedSet(rightVal);

//	cout << "Drive Left: " << leftBackMotor->GetPosition() << endl;
//	cout << "Drive Right: " << rightBackMotor->GetPosition() << endl;

//	cout << "Drive Left Speed: " << leftBackMotor->GetSpeed() << endl;
//	cout << "Drive Right Speed: " << rightBackMotor->GetSpeed() << endl;

}

void Drive::allSpeedSet(double s) {
	leftBackMotor->Set(s);
	rightBackMotor->Set(s);

}

void Drive::leftSpeedSet(double s) {
	leftBackMotor->Set(s);
}

void Drive::rightSpeedSet(double s) {
	rightBackMotor->Set(s);

}
