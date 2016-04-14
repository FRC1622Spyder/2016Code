#include "WPILib.h"
#include "Auto.h"
#include <cmath>
#include <iostream>

void Auto::AutoInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID");
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID");
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID");
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID");
	wheelCircumfrence = prefs->GetDouble("wheelCircumfrence");
	driveRatio = 8.45;

	// assign motors and drive joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);

	// setup motors
	// in the drive code of this folder, the /left/ motors are inverted, not right
		leftBackMotor->SetInverted(false);
		leftFrontMotor->SetInverted(false);
		rightBackMotor->SetInverted(true);
		rightFrontMotor->SetInverted(true);

	//Set back motors to follow front
	//leftFrontMotor->SetControlMode(CANSpeedController::kFollower);
	//leftFrontMotor->Set(1);

	//rightFrontMotor->SetControlMode(CANSpeedController::kFollower);
	//rightFrontMotor->Set(5);

	//Setup encoders
	rightBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightBackMotor->ConfigEncoderCodesPerRev(20);

	leftBackMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	leftBackMotor->ConfigEncoderCodesPerRev(20);

	//set closed loop gains
	//leftBackMotor->SetPID(2.0f, 0, 200.0f, 0);
	//rightBackMotor->SetPID(2.0f, 0, 200.0f, 0);
	//leftBackMotor->SetCloseLoopRampRate(24);
	//rightBackMotor->SetCloseLoopRampRate(24);

	//shooterSolenoidExtend = prefs->GetInt("shooterSolenoidExtend");
	//shooterSolenoidRetract = prefs->GetInt("shooterSolenoidRetract");

	topWheel = new CANTalon(shooterTopMotorCANTalonID);
	lowerWheel = new CANTalon(shooterBottomMotorCANTalonID);
	shooterTopMotorCANTalonID = prefs->GetInt("shooterTopMotorCANTalonID");
	shooterBottomMotorCANTalonID = prefs->GetInt("shooterBottomMotorCANTalonID");
	firePhase = 0;
	state = 1;
	pcmCANID = prefs->GetInt("pcmCANID");
	//exsole = new DoubleSolenoid(pcmCANID, shooterSolenoidExtend,shooterSolenoidRetract);

	targetSpeed = prefs->GetFloat("shooterTargetSpeed");

	topWheel->Set(0);
	lowerWheel->Set(0);


	turnChooser = new SendableChooser();
	autoStraight = "Forward immediately";
	autoLeft = "Turn left, then forward";
	autoRight = "Turn right, then forward";
	turnChooser->AddDefault(autoStraight, (void*) &autoStraight);
	turnChooser->AddObject(autoLeft, (void*) &autoLeft);
	turnChooser->AddObject(autoRight, (void*) &autoRight);
	SmartDashboard::PutData("Autonomous Starting Turn", turnChooser);

	rotateChooser = new SendableChooser();
	autoRotateNone = "Don't rotate after obstacle";
	autoRotateLeft = "Rotate left after obstacle";
	autoRotateRight = "Rotate right after obstacle";
	rotateChooser->AddDefault(autoRotateNone, (void*) &autoRotateNone);
	rotateChooser->AddObject(autoRotateLeft, (void*) &autoRotateLeft);
	rotateChooser->AddObject(autoRotateRight, (void*) &autoRotateRight);
	SmartDashboard::PutData("Autonomous Rotation", rotateChooser);

	obstacleChooser = new SendableChooser();
	Default = "Default obstacle";
	Moat = "Moat";
	RoughTerrain = "Rough Terrain";
	Ramparts = "Ramparts";
	Seesaw = "Seesaw";
	Drawbridge = "Drawbridge";
	Portcullis = "Portcullis";
	SallyPort = "Sally Port";
	RockWall = "Rock Wall";
	obstacleChooser->AddDefault(Default, (void*) &Default);
	obstacleChooser->AddObject(Moat, (void*) &Moat);
	obstacleChooser->AddObject(RoughTerrain, (void*) &RoughTerrain);
	obstacleChooser->AddObject(Ramparts, (void*) &Ramparts);
	obstacleChooser->AddObject(Seesaw, (void*) &Seesaw);
	obstacleChooser->AddObject(Drawbridge, (void*) &Drawbridge);
	obstacleChooser->AddObject(Portcullis, (void*) &Portcullis);
	obstacleChooser->AddObject(SallyPort, (void*) &SallyPort);
	obstacleChooser->AddObject(RockWall, (void*) &RockWall);
	SmartDashboard::PutData("Autonomous Obstacle Select", obstacleChooser);

}

void Auto::AutoDisable() {

	leftBackMotor->Set(0);
	leftFrontMotor->Set(0);
	rightBackMotor->Set(0);
	rightFrontMotor->Set(0);

}

void Auto::AutoAutoInit() {
	toBeReplaced = 0; //Replace this integer with values once the robot can be tested to find them
	  	  	  	  	  //The different instances of toBeReplaced WILL BE REPLACED WITH DIFFERENT INTEGERS
	  	  	  	  	  //Ex: tBR-A next to a line of code means a different integer than tBR-B
					  //tBR-A, tBR-B, tBR-C, tBR-D, tBR-E: values to compare against encoder positions, determine how far robot will move
					  //tBR-M: value for motor speed while moving forward
					  //tBR-R: value for motor speed while rotating
	turnSelected = *((std::string*) turnChooser->GetSelected());
	rotateSelected = *((std::string*) rotateChooser->GetSelected());
	//int obstable = Auto::SelectionToInt(*((std::string*) obstacleChooser->GetSelected()));

	leftBackMotor->SetPosition(0);
	rightBackMotor->SetPosition(0);
	targetPosition = 0.0;

	leftBackMotor->SetControlMode(CANTalon::ControlMode::kPosition);
	rightBackMotor->SetControlMode(CANTalon::ControlMode::kPosition);
}

void Auto::AutoAutoPeriodic() {
	leftEncoderPosition = leftFrontMotor->GetPosition();
	rightEncoderPosition = rightFrontMotor->GetPosition();

	if (state == 1) {
		if (turnSelected == autoStraight) {
			state = 2;
		} else if (turnSelected == autoLeft) {
			if (rightEncoderPosition < toBeReplaced) { 			//tBR-A
				driveTurnLeft(toBeReplaced);					//tBR-R
			} else if (rightEncoderPosition == toBeReplaced) {	//tBR-A
				driveStop();
			} else if (rightEncoderPosition < toBeReplaced) { 	//tBR-B
				driveForward(toBeReplaced);						//tBR-M
			} else if (rightEncoderPosition == toBeReplaced) { 	//tBR-B
				driveStop();
			} else if (rightEncoderPosition < toBeReplaced) { 	//tBR-C
				driveTurnRight(toBeReplaced);					//tBR-R
			} else if (rightEncoderPosition >= toBeReplaced) { 	//tBR-C
				driveStop();
				state = 2;
				leftFrontMotor->SetPosition(0);
				rightFrontMotor->SetPosition(0);
			}
		} else if (turnSelected == autoRight) {
			if (leftEncoderPosition < toBeReplaced) { 			//tBR-A
				driveTurnRight(toBeReplaced);					//tBR-R
			} else if (leftEncoderPosition == toBeReplaced) {	//tBR-A
				driveStop();
			} else if (leftEncoderPosition < toBeReplaced) { 	//tBR-B
				driveForward(toBeReplaced);						//tBR-M
			} else if (leftEncoderPosition == toBeReplaced) { 	//tBR-B
				driveStop();
			} else if (leftEncoderPosition < toBeReplaced) { 	//tBR-C
				driveTurnLeft(toBeReplaced);					//tBR-R
			} else if (leftEncoderPosition >= toBeReplaced) { 	//tBR-C
				driveStop();
				state = 2;
				leftFrontMotor->SetPosition(0);
				rightFrontMotor->SetPosition(0);
			}

		}
	}

	else if (state == 2) {
		if (leftEncoderPosition < 5) { 			//tBR-D --Test Value
			driveForward(10);						//tBR-M --Test Value
		} else {
			driveStop();
			state = 3;
			leftFrontMotor->SetPosition(0);
			rightFrontMotor->SetPosition(0);
		}
	}
	else if (state == 3) {
		if (rotateSelected == autoRotateNone) {
			state = 4;
		} else if (rotateSelected == autoRotateLeft) {
			if (rightEncoderPosition < toBeReplaced) { 		//tBR-E
				driveTurnLeft(toBeReplaced);				//tBR-R
			} else {
				driveStop();
				state = 4;
				leftFrontMotor->SetPosition(0);
				rightFrontMotor->SetPosition(0);
			}
		} else if (rotateSelected == autoRotateRight) {
			if (leftEncoderPosition < toBeReplaced) { 		//tBR-E
				driveTurnRight(toBeReplaced);				//tBR-R
			} else {
				driveStop();
				state = 4;
				leftFrontMotor->SetPosition(0);
				rightFrontMotor->SetPosition(0);
			}
		}
	}

	else if (state == 4) {
		//TODO add targeting code
		state = 5;
	}

	else if (state == 5) {
		topWheel->Set(targetSpeed);
		lowerWheel->Set(targetSpeed);
		//wait(4000);
		exsole->Set(DoubleSolenoid::Value::kReverse);
		exsole->Set(DoubleSolenoid::Value::kForward);
		state = 6;
	}

	else if (state == 6) {
		//Do nothing
	}

	autoLoopCounter++;

}

void Auto::AutoTeleopInit() {

}

void Auto::AutoTeleopPeriodic() {

}

void Auto::driveForward(double speed) {
	leftFrontMotor->Set(speed);
	leftBackMotor->Set(speed);
	rightFrontMotor->Set(speed);
	rightBackMotor->Set(speed);
}

void Auto::driveBackward(double speed) {
	leftFrontMotor->Set(-speed);
	leftBackMotor->Set(-speed);
	rightFrontMotor->Set(-speed);
	rightBackMotor->Set(-speed);
}

void Auto::driveTurnLeft(double speed) {
	leftFrontMotor->Set(-speed);
	leftBackMotor->Set(-speed);
	rightFrontMotor->Set(speed);
	rightBackMotor->Set(speed);
}

void Auto::driveTurnRight(double speed) {
	leftFrontMotor->Set(speed);
	leftBackMotor->Set(speed);
	rightFrontMotor->Set(-speed);
	rightBackMotor->Set(-speed);
}

void Auto::driveStop() {
	leftFrontMotor->Set(0);
	leftBackMotor->Set(0);
	rightFrontMotor->Set(0);
	rightBackMotor->Set(0);
}

int Auto::SelectionToInt(std::string obstacleString) { //function that changes strings to integers
	if (obstacleString == "Default") {
		return 0;
	}
	if (obstacleString == "Moat") {
		return 1;
	}
	if (obstacleString == "Rough Terrain") {
		return 2;
	}
	if (obstacleString == "Ramparts") {
		return 3;
	}
	if (obstacleString == "Seesaw") {
		return 4;
	}
	if (obstacleString == "Drawbridge") {
		return 5;
	}
	if (obstacleString == "Portcullis") {
		return 6;
	}
	if (obstacleString == "Sally Port") {
		return 7;
	}
	if (obstacleString == "Rock Wall") {
		return 8;
	}
	else return -1;
	}
