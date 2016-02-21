#include "WPILib.h"
#include <cmath>
#include "Drive.h"
#include <iostream>

<<<<<<< HEAD
=======
using namespace std;

>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
void Drive::DriveInit() {

	// get preferences
	prefs = Preferences::GetInstance();
<<<<<<< HEAD
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 2);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 3);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 5);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 6);
	driveJoystickNumber = prefs->GetInt("joystickNumber", 0);
	leftAxis = prefs->GetInt("leftAxis", 1);
	rightAxis = prefs->GetInt("rightAxis", 3);
=======
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 1);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 3);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 5);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 4);
	driveJoystickNumber = prefs->GetInt("joystickNumber", 0);
	leftAxis = prefs->GetInt("leftAxis", 1);
	rightAxis = prefs->GetInt("rightAxis", 3);
	wheelCircumfrence = prefs->GetDouble("wheelCircumfrence", 23);
	driveRatio = 8.45;
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc

	// assign motors and joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);
	joy = new Joystick(driveJoystickNumber);

	// setup motors
	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);
<<<<<<< HEAD
}
void Drive::DriveDisable() {

	leftBackMotor->Set(0);
	leftFrontMotor->Set(0);
	rightBackMotor->Set(0);
	rightFrontMotor->Set(0);

}

/**
 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
 * below the Gyro
 *
 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
 * If using the SendableChooser make sure to add them to the chooser code above as well.
 */
=======

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

>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
void Drive::DriveAutoInit() {

}

void Drive::DriveAutoPeriodic() {

}

void Drive::DriveTeleopInit() {
<<<<<<< HEAD

	// TODO -- need to re-read the preferences and re-assign the motors and joysticks here.
	// if we want the ability to change them at the start of teleop
	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 2);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 3);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 5);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 6);
	driveJoystickNumber = prefs->GetInt("joystickNumber", 0);
	leftAxis = prefs->GetInt("leftAxis", 1);
	rightAxis = prefs->GetInt("rightAxis", 3);

	// assign motors and joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);
	joy = new Joystick(driveJoystickNumber);


=======
	leftFrontMotor->SetPosition(0);
	rightFrontMotor->SetPosition(0);
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc

}

void Drive::DriveTeleopPeriodic() {
	double leftVal;
	double rightVal;

	leftVal = joy->GetRawAxis(leftAxis);
	rightVal = joy->GetRawAxis(rightAxis);

<<<<<<< HEAD
	leftVal = fabs(leftVal) > 0.5 ? leftVal : 0;
	rightVal = fabs(rightVal) > 0.5 ? rightVal : 0;

	leftVal = leftVal / 5;
	rightVal = rightVal / 5;
=======
	leftVal = fabs(leftVal) > 0.1 ? leftVal : 0;
	rightVal = fabs(rightVal) > 0.1 ? rightVal : 0;

	leftVal = leftVal * .8;
	rightVal = rightVal * .8;
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc

	leftSpeedSet(leftVal);
	rightSpeedSet(rightVal);

<<<<<<< HEAD
=======
//	cout << "Drive Left: " << leftFrontMotor->GetPosition() << endl;
//	cout << "Drive Right: " << rightFrontMotor->GetPosition() << endl;

//	cout << "Drive Left Speed: " << leftFrontMotor->GetSpeed() << endl;
//	cout << "Drive Right Speed: " << rightFrontMotor->GetSpeed() << endl;

>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
	/*	halfButtonvalue = joy->GetRawButton(6);

	 if (halfButtonvalue) {
	 leftVal = leftVal / 2;
	 rightVal = rightVal / 2;
	 }
	 */

}

void Drive::allSpeedSet(double s) {
<<<<<<< HEAD
	leftBackMotor->Set(s);
	leftFrontMotor->Set(s);
	rightBackMotor->Set(s);
=======
	leftFrontMotor->Set(s);
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
	rightFrontMotor->Set(s);

}

void Drive::leftSpeedSet(double s) {
<<<<<<< HEAD
	leftBackMotor->Set(s);
=======
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
	leftFrontMotor->Set(s);
}

void Drive::rightSpeedSet(double s) {
<<<<<<< HEAD
	rightBackMotor->Set(s);
=======
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
	rightFrontMotor->Set(s);

}
