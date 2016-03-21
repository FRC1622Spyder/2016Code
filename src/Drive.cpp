#include "WPILib.h"
#include <cmath>
#include "Drive.h"
#include <iostream>
#include <math.h>

using namespace std;

void Drive::DriveInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID");
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID");
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID");
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID");
	driveJoystickNumber = prefs->GetInt("joystickNumber");
	leftAxis = prefs->GetInt("leftAxis");
	rightAxis = prefs->GetInt("rightAxis");
	rampRate = prefs->GetDouble("rampRate");
//	wheelCircumfrence = prefs->GetDouble("wheelCircumfrence");
//	driveRatio = 8.45;

	// assign motors and joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);
	joy = new Joystick(driveJoystickNumber);

	//set the ramp rate
	leftBackMotor->SetVoltageRampRate(rampRate);
	rightBackMotor->SetVoltageRampRate(rampRate);
	leftFrontMotor->SetVoltageRampRate(rampRate);
	rightFrontMotor->SetVoltageRampRate(rampRate);

	// invert left motors
	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);

	//Set drive motors to vBus
	leftBackMotor->SetControlMode(CANSpeedController::kPercentVbus);
	rightBackMotor->SetControlMode(CANSpeedController::kPercentVbus);
	leftFrontMotor->SetControlMode(CANSpeedController::kPercentVbus);
	rightFrontMotor->SetControlMode(CANSpeedController::kPercentVbus);

	//Set front motors to follow back
//	leftFrontMotor->SetControlMode(CANSpeedController::kFollower);
//	leftFrontMotor->Set(backLeftMotorCANTalonID);

//	rightFrontMotor->SetControlMode(CANSpeedController::kFollower);
//	rightFrontMotor->Set(backRightMotorCANTalonID);

	//Setup encoders
//	leftBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
//	leftBackMotor->ConfigEncoderCodesPerRev(20);

//	rightBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
//	rightBackMotor->ConfigEncoderCodesPerRev(20);

}

void Drive::DriveDisable() {

	leftBackMotor->Set(0);
	leftFrontMotor->Set(0);
	rightBackMotor->Set(0);
	rightFrontMotor->Set(0);

}

void Drive::DriveAutoInit() {

}

void Drive::DriveAutoPeriodic() {

}

void Drive::DriveTeleopInit() {
//	leftBackMotor->SetPosition(0);
//	rightBackMotor->SetPosition(0);

}

void Drive::DriveTeleopPeriodic() {
	double leftVal;
	double rightVal;


	halfButtonValue = joy->GetRawButton(prefs->GetInt("halfSpeedButton"));
	leftVal = joy->GetRawAxis(leftAxis);
	rightVal = joy->GetRawAxis(rightAxis);

//	cout << "Drive Left: " << leftVal << endl;
//	cout << "Drive Right: " << rightVal << endl;

	// cut speed in half if button is pressed
	if (halfButtonValue) {
		leftBackMotor->SetVoltageRampRate(0);
		rightBackMotor->SetVoltageRampRate(0);
	}



	// create dead zone at 10%
	leftVal = fabs(leftVal) > 0.1 ? leftVal : 0;
	rightVal = fabs(rightVal) > 0.1 ? rightVal : 0;

	// limmit speed to 80%
	//leftVal = leftVal * .87;
	//rightVal = rightVal * .87;

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
	leftFrontMotor->Set(s);
	rightFrontMotor->Set(s);
}

void Drive::leftSpeedSet(double s) {

	leftBackMotor->Set(s);
	leftFrontMotor->Set(s);

}

void Drive::rightSpeedSet(double s) {

	rightBackMotor->Set(s);
	rightFrontMotor->Set(s);


}




