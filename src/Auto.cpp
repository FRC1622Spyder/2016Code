#include "WPILib.h"
#include "Auto.h"
#include <cmath>
#include <iostream>

using namespace std;

void Auto::AutoInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID");
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID");
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID");
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID");
	wheelCircumfrence = prefs->GetDouble("wheelCircumfrence");
	driveRatio = 8.45;

	// assign motors
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);

	// invert left motors
	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);

	//Set drive motors to vBus
	leftBackMotor->SetControlMode(CANSpeedController::kPercentVbus);
	rightBackMotor->SetControlMode(CANSpeedController::kPercentVbus);

	//Set front motors to follow back
	leftFrontMotor->SetControlMode(CANSpeedController::kFollower);
	leftFrontMotor->Set(backLeftMotorCANTalonID);

	rightFrontMotor->SetControlMode(CANSpeedController::kFollower);
	rightFrontMotor->Set(backRightMotorCANTalonID);

	//Setup encoders
	leftBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	leftBackMotor->ConfigEncoderCodesPerRev(20);

	rightBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightBackMotor->ConfigEncoderCodesPerRev(20);


}

void Auto::AutoDisable() {

}

void Auto::AutoAutoInit() {

	timer = 0;
}

void Auto::AutoAutoPeriodic() {

	// Autonomous code goes here


	// go forward for 3 seconds

	if(timer < 150) {
		leftSpeedSet(0.5f);
		rightSpeedSet(0.5f);
	}
	else {
		leftSpeedSet(0.0);
		rightSpeedSet(0.0);
	}
	timer++;

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
	leftBackMotor->Set(s);
}

void Auto::rightSpeedSet(double s) {
	rightBackMotor->Set(s);
}
