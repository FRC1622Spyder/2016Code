#include "WPILib.h"
#include "Auto.h"
#include <cmath>
#include <iostream>

using namespace std;

void Auto::AutoInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 1);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 3);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 5);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 4);
	wheelCircumfrence = prefs->GetDouble("wheelCircumfrence", 23);
	driveRatio = 8.45;

	// assign motors and drive joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);

	// setup motors
	rightBackMotor->SetInverted(true);
	rightFrontMotor->SetInverted(true);

	//Set back motors to follow front
	leftFrontMotor->SetControlMode(CANSpeedController::kFollower);
	leftFrontMotor->Set(1);

	rightFrontMotor->SetControlMode(CANSpeedController::kFollower);
	rightFrontMotor->Set(5);

	//Setup encoders
	rightBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightBackMotor->ConfigEncoderCodesPerRev(20);

	leftBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	leftBackMotor->ConfigEncoderCodesPerRev(20);

	//set closed loop gains
	leftBackMotor->SetPID(2.0f, 0, 200.0f, 0);
	rightBackMotor->SetPID(2.0f, 0, 200.0f, 0);
	leftBackMotor->SetCloseLoopRampRate(24);
	rightBackMotor->SetCloseLoopRampRate(24);
}

void Auto::AutoDisable() {

	//leftBackMotor->Set(0);
	//leftFrontMotor->Set(0);
	//rightBackMotor->Set(0);
	//rightFrontMotor->Set(0);

}

void Auto::AutoAutoInit() {

	//Prepping auto state
	autoLoopCounter = 0;
	leftBackMotor->SetPosition(0);
	rightBackMotor->SetPosition(0);


	//0 the sensor and position
	leftBackMotor->SetPosition(0);
	rightBackMotor->SetPosition(0);
	targetPosition = 0.0;

	leftBackMotor->SetControlMode(CANTalon::ControlMode::kPosition);
	rightBackMotor->SetControlMode(CANTalon::ControlMode::kPosition);

}

void Auto::AutoAutoPeriodic() {

	// Autonomous code goes here

	cout << "Left: " << leftBackMotor->GetPosition() << endl;
	cout << "Right: " << rightBackMotor->GetPosition() << endl;

	cout << "Left Speed: " << leftBackMotor->GetSpeed() << endl;
	cout << "Right Speed: " << rightBackMotor->GetSpeed() << endl;

	double inches = 36;
	double leftWheelPosition;
	double rightWheelPosition;

	targetPosition = (inches / wheelCircumfrence) * driveRatio;
	leftBackMotor->Set(targetPosition);
    rightBackMotor->Set(targetPosition*-1);
    leftWheelPosition=leftBackMotor->GetPosition();
    rightWheelPosition=-1*rightBackMotor->GetPosition();


	cout << "Left Position: " << leftWheelPosition << endl;
	cout << "Right Position: " << rightWheelPosition << endl;
}

void Auto::AutoTeleopInit() {

}

void Auto::AutoTeleopPeriodic() {

}

void Auto::allSpeedSet(double s) {

	leftBackMotor->Set(s);

	rightBackMotor->Set(s);

}

void Auto::leftSpeedSet(double s) {
	//leftBackMotor->Set(s);
	leftBackMotor->Set(s);
}

void Auto::rightSpeedSet(double s) {
	//rightBackMotor->Set(s);
	rightBackMotor->Set(s);

}
