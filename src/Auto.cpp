#include "WPILib.h"
#include "Auto.h"
#include <cmath>
#include <iostream>

<<<<<<< HEAD

using namespace std;

void Auto::AutoInit(std::string autoObstacleSelected) {
=======
using namespace std;

void Auto::AutoInit() {
>>>>>>> refs/remotes/origin/master

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
<<<<<<< HEAD
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

	//Auto selector code

}




}


}
=======
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
>>>>>>> refs/remotes/origin/master
}

void Auto::AutoDisable() {

<<<<<<< HEAD
//leftBackMotor->Set(0);
//leftFrontMotor->Set(0);
//rightBackMotor->Set(0);
//rightFrontMotor->Set(0);
=======
	//leftBackMotor->Set(0);
	//leftFrontMotor->Set(0);
	//rightBackMotor->Set(0);
	//rightFrontMotor->Set(0);
>>>>>>> refs/remotes/origin/master

}

void Auto::AutoAutoInit() {
<<<<<<< HEAD
=======

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
>>>>>>> refs/remotes/origin/master

//Prepping auto state
autoLoopCounter = 0;
leftFrontMotor->SetPosition(0);
rightFrontMotor->SetPosition(0);

//0 the sensor and position
leftFrontMotor->SetPosition(0);
rightFrontMotor->SetPosition(0);
targetPosition = 0.0;

<<<<<<< HEAD
leftFrontMotor->SetControlMode(CANTalon::ControlMode::kPosition);
rightFrontMotor->SetControlMode(CANTalon::ControlMode::kPosition);

// turn obstacle string into integers
obstacle = selectToInt(autoObstacleSelected);
//position = selectToInt(autoPositionSelected);
}

void Auto::AutoAutoPeriodic() {

// Autonomous code goes here

	int findObstacle(obstacle) { //uses integers to choose what actions to take for the obstacle
		switch (obstacle) {
		case 0:
			std::cout << "Default" << std::endl;
			break;
		case 1:
			std::cout << "Moat" << std::endl;
			break;
		case 2:
			std::cout << "Rough Terrain" << std::endl;
			break;
		case 3:
			std::cout << "Ramparts" << std::endl;
			break;
		case 4:
			std::cout << "Seesaw" << std::endl;
			break;
		case 5:
			std::cout << "Drawbridge" << std::endl;
			break;
		case 6:
			std::cout << "Portcullis" << std::endl;
			break;
		case 7:
			std::cout << "Sallyport" << std::endl;
			break;
		case 8:
			std::cout << "Rockwall" << std::endl;
			break;
		}
		/*int findPosition(position) { // uses integers to choose where to move after the robot crossed over
			switch (position) {
			case 0:
				findObstacle(obstacle);
				std::cout << "Default" << std::endl;
			case 1:
				findObstacle(obstacle);
				std::cout << "move left then straight forward" << std::endl;
				break;
			case 2:
				findObstacle(obstacle);
				std::cout << "move straight forward then move slightly left"
						<< std::endl;
				break;
			case 3:
				findObstacle(obstacle);
				std::cout << "move straight forward then move slightly right"
						<< std::endl;
				break;
			case 4:
				findObstacle(obstacle);
				std::cout << "move right then straight forward" << std::endl;
				break;
			}*/
=======
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
>>>>>>> refs/remotes/origin/master
}

void Auto::AutoTeleopInit() {

}

void Auto::AutoTeleopPeriodic() {

}

void Auto::allSpeedSet(double s) {

<<<<<<< HEAD
leftFrontMotor->Set(s);

rightFrontMotor->Set(s);
=======
	leftBackMotor->Set(s);

	rightBackMotor->Set(s);
>>>>>>> refs/remotes/origin/master

}

void Auto::leftSpeedSet(double s) {
<<<<<<< HEAD
//leftBackMotor->Set(s);
leftFrontMotor->Set(s);
}

void Auto::rightSpeedSet(double s) {
//rightBackMotor->Set(s);
rightFrontMotor->Set(s);
=======
	//leftBackMotor->Set(s);
	leftBackMotor->Set(s);
}

void Auto::rightSpeedSet(double s) {
	//rightBackMotor->Set(s);
	rightBackMotor->Set(s);
>>>>>>> refs/remotes/origin/master

}
int selectToInt(std::string obstacleString) { //function that changes strings to integers
if (obstacleString = "Default") {
	return 0;
}
if (obstacleString = "Moat") {
	return 1;
}
if (obstacleString = "Rough Terrain") {
	return 2;
}
if (obstacleString = "Ramparts") {
	return 3;
}
if (obstacleString = "Seesaw") {
	return 4;
}
if (obstacleString = "Drawbridge") {
	return 5;
}
if (obstacleString = "Portcullis") {
	return 6;
}
if (obstacleString = "Sally Port") {
	return 7;
}
if (obstacleString = "Rock Wall") {
	return 8;
}
}
