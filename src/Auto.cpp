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
	autoDistance = 100;


	// assign motors
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);

	// invert right motors
	rightBackMotor->SetInverted(true);
	rightFrontMotor->SetInverted(true);
	leftBackMotor->SetInverted(false);
	leftFrontMotor->SetInverted(false);

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

	// set PID
	leftBackMotor->SelectProfileSlot(0);
	rightBackMotor->SelectProfileSlot(0);
	leftBackMotor->SetPID(0.8f, 0.0f, 0.0f, 0.0f);
	rightBackMotor->SetPID(0.8f, 0.0f, 0.0f, 0.0f);
	leftFrontMotor->SelectProfileSlot(0);
	rightFrontMotor->SelectProfileSlot(0);
	leftFrontMotor->SetPID(0.8f, 0.0f, 0.0f, 0.0f);
	rightFrontMotor->SetPID(0.8f, 0.0f, 0.0f, 0.0f);

	// set ramp
	//leftBackMotor->SetVoltageRampRate(10);
	//rightBackMotor->SetVoltageRampRate(10);

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
		leftSpeedSet(1.0f);
		rightSpeedSet(1.0f);
			std::cout << "timer: " << timer << std::endl;
	}
	else {
		leftSpeedSet(0.0);
		rightSpeedSet(0.0);
		//std::cout << "leftDistance: " << leftDistance << std::endl;
		//std::cout << "rightDistance: " << rightDistance << std::endl;
	}
	timer++;
	//leftBackMotor->SetPosition(100);
	//rightBackMotor->SetPosition(100);
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
