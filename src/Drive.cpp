#include "WPILib.h"
#include <cmath>
#include "Drive.h"
#include <iostream>

using namespace std;

void Drive::DriveInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 1);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 3);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 5);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 4);
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
	rightBackMotor->SetControlMode(CANSpeedController::kFollower);
	rightBackMotor->Set(1);

	leftBackMotor->SetControlMode(CANSpeedController::kFollower);
	leftBackMotor->Set(5);

	//Setup encoders
	rightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightFrontMotor->ConfigEncoderCodesPerRev(20);

	leftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	leftFrontMotor->ConfigEncoderCodesPerRev(20);

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
	leftFrontMotor->SetPosition(0);
	rightFrontMotor->SetPosition(0);

}

void Drive::DriveTeleopPeriodic() {
	double leftVal;
	double rightVal;

	leftVal = joy->GetRawAxis(leftAxis);
	rightVal = joy->GetRawAxis(rightAxis);

	leftVal = fabs(leftVal) > 0.1 ? leftVal : 0;
	rightVal = fabs(rightVal) > 0.1 ? rightVal : 0;

	leftVal = leftVal * .8;
	rightVal = rightVal * .8;

	leftSpeedSet(leftVal);
	rightSpeedSet(rightVal);

//	cout << "Drive Left: " << leftFrontMotor->GetPosition() << endl;
//	cout << "Drive Right: " << rightFrontMotor->GetPosition() << endl;

//	cout << "Drive Left Speed: " << leftFrontMotor->GetSpeed() << endl;
//	cout << "Drive Right Speed: " << rightFrontMotor->GetSpeed() << endl;

	/*	halfButtonvalue = joy->GetRawButton(6);

	 if (halfButtonvalue) {
	 leftVal = leftVal / 2;
	 rightVal = rightVal / 2;
	 }
	 */

}

void Drive::allSpeedSet(double s) {
	leftFrontMotor->Set(s);
	rightFrontMotor->Set(s);

}

void Drive::leftSpeedSet(double s) {
	leftFrontMotor->Set(s);
}

void Drive::rightSpeedSet(double s) {
	rightFrontMotor->Set(s);

}
