#include "WPILib.h"
#include "Auto.h"
#include <cmath>
#include <iostream>

<<<<<<< HEAD
=======
using namespace std;

>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
void Auto::AutoInit() {

	// get preferences
	prefs = Preferences::GetInstance();
<<<<<<< HEAD
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 2);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 3);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 5);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 6);
=======
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 1);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 3);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 5);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 4);
	wheelCircumfrence = prefs->GetDouble("wheelCircumfrence", 23);
	driveRatio = 8.45;
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc

	// assign motors and drive joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);

	// setup motors
<<<<<<< HEAD
	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);
=======
	rightBackMotor->SetInverted(true);
	rightFrontMotor->SetInverted(true);

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

	//set closed loop gains
	leftFrontMotor->SetPID(2.0f, 0, 200.0f, 0);
	rightFrontMotor->SetPID(2.0f, 0, 200.0f, 0);
	leftFrontMotor->SetCloseLoopRampRate(24);
	rightFrontMotor->SetCloseLoopRampRate(24);
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
}

void Auto::AutoDisable() {

<<<<<<< HEAD
	leftBackMotor->Set(0);
	leftFrontMotor->Set(0);
	rightBackMotor->Set(0);
	rightFrontMotor->Set(0);
=======
	//leftBackMotor->Set(0);
	//leftFrontMotor->Set(0);
	//rightBackMotor->Set(0);
	//rightFrontMotor->Set(0);
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc

}

void Auto::AutoAutoInit() {
<<<<<<< HEAD
	autoLoopCounter = 0;
=======

	//Prepping auto state
	autoLoopCounter = 0;
	leftFrontMotor->SetPosition(0);
	rightFrontMotor->SetPosition(0);


	//0 the sensor and position
	leftFrontMotor->SetPosition(0);
	rightFrontMotor->SetPosition(0);
	targetPosition = 0.0;

	leftFrontMotor->SetControlMode(CANTalon::ControlMode::kPosition);
	rightFrontMotor->SetControlMode(CANTalon::ControlMode::kPosition);

>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
}

void Auto::AutoAutoPeriodic() {

	// Autonomous code goes here

<<<<<<< HEAD
	if(autoLoopCounter < 250) {
		allSpeedSet(.2);
	}
	else {
		allSpeedSet(0);
	}
	autoLoopCounter++;

=======
	cout << "Left: " << leftFrontMotor->GetPosition() << endl;
	cout << "Right: " << rightFrontMotor->GetPosition() << endl;

	cout << "Left Speed: " << leftFrontMotor->GetSpeed() << endl;
	cout << "Right Speed: " << rightFrontMotor->GetSpeed() << endl;

	double inches = 36;
	double leftWheelPosition;
	double rightWheelPosition;

	targetPosition = (inches / wheelCircumfrence) * driveRatio;
	leftFrontMotor->Set(targetPosition);
    rightFrontMotor->Set(targetPosition*-1);
    leftWheelPosition=leftFrontMotor->GetPosition();
    rightWheelPosition=-1*rightFrontMotor->GetPosition();


	cout << "Left Position: " << leftWheelPosition << endl;
	cout << "Right Position: " << rightWheelPosition << endl;
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
}

void Auto::AutoTeleopInit() {

}

void Auto::AutoTeleopPeriodic() {

}

void Auto::allSpeedSet(double s) {
<<<<<<< HEAD
	leftBackMotor->Set(s);
	leftFrontMotor->Set(s);
	rightBackMotor->Set(s);
=======

	leftFrontMotor->Set(s);

>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
	rightFrontMotor->Set(s);

}

void Auto::leftSpeedSet(double s) {
<<<<<<< HEAD
	leftBackMotor->Set(s);
=======
	//leftBackMotor->Set(s);
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
	leftFrontMotor->Set(s);
}

void Auto::rightSpeedSet(double s) {
<<<<<<< HEAD
	rightBackMotor->Set(s);
=======
	//rightBackMotor->Set(s);
>>>>>>> 707a443ad9ea7a31c49fc39c67dcdd8cf44fe1bc
	rightFrontMotor->Set(s);

}
