#include "WPILib.h"
#include "Auto.h"
#include <cmath>
#include <iostream>

void Auto::AutoInit() {

	// get preferences
	prefs = Preferences::GetInstance();
	frontRightMotorCANTalonID = prefs->GetInt("frontRightMotorCANTalonID", 7);
	backRightMotorCANTalonID = prefs->GetInt("backRightMotorCANTalonID", 7);
	frontLeftMotorCANTalonID = prefs->GetInt("frontLeftMotorCANTalonID", 7);
	backLeftMotorCANTalonID = prefs->GetInt("backLeftMotorCANTalonID", 7);

	// assign motors and drive joystick
	leftBackMotor = new CANTalon(backLeftMotorCANTalonID);
	rightBackMotor = new CANTalon(backRightMotorCANTalonID);
	leftFrontMotor = new CANTalon(frontLeftMotorCANTalonID);
	rightFrontMotor = new CANTalon(frontRightMotorCANTalonID);

	// setup motors
	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);

	turnChooser = new SendableChooser();
	turnChooser->AddDefault(autoStraight, (void*) &autoStraight);
	turnChooser->AddObject(autoLeft, (void*) &autoLeft);
	turnChooser->AddObject(autoRight, (void*) &autoRight);
	SmartDashboard::PutData("Autonomous Starting Turn", turnChooser);
	rotateChooser = new SendableChooser();
	rotateChooser->AddDefault(autoRotateNone, (void*) &autoRotateNone);
	rotateChooser->AddObject(autoRotateLeft, (void*) &autoRotateLeft);
	rotateChooser->AddObject(autoRotateRight, (void*) &autoRotateRight);
	SmartDashboard::PutData("Autonomous Rotation", rotateChooser);

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
		if (leftEncoderPosition < toBeReplaced) { 			//tBR-D
			driveForward(toBeReplaced);						//tBR-M
		} else {
			driveStop();
			state = 3;
			leftFrontMotor->SetPosition(0);
			rightFrontMotor->SetPosition(0);
		}
	}
	if (state == 3) {
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
		//TODO add firing code
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
