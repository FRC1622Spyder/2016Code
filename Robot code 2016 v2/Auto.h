/*
 * Auto.h
 *
 *  Created on: Feb 10, 2016
 *      Author: Admin
 */

#ifndef SRC_AUTO_H_
#define SRC_AUTO_H_

class Auto {

private:
	int autoLoopCounter;
	CANTalon *leftBackMotor;
	CANTalon *rightBackMotor;
	CANTalon *leftFrontMotor;
	CANTalon *rightFrontMotor; //TODO add firing motors

	Preferences *prefs;

	int frontRightMotorCANTalonID;
	int frontLeftMotorCANTalonID;
	int backRightMotorCANTalonID;
	int backLeftMotorCANTalonID;
	
	double wheelCircumfrence;
	double driveRatio;
    	double targetPosition;

	SendableChooser *turnChooser;
	const std::string autoStraight;
	const std::string autoLeft;
	const std::string autoRight;
	std::string turnSelected;
	SendableChooser *rotateChooser;
	const std::string autoRotateNone;
	const std::string autoRotateLeft;
	const std::string autoRotateRight;
	std::string rotateSelected;
	SendableChooser *obstacleChooser;
	const std::string Default;
	const std::string Moat;
	const std::string RoughTerrain;
	const std::string Ramparts;
	const std::string Seesaw;
	const std::string Drawbridge;
	const std::string Portcullis;
	const std::string SallyPort;
	const std::string RockWall;
	std::string obstacleSelected;

	int state;
	int leftEncoderPosition;
	int rightEncoderPosition;
	int toBeReplaced; //TODO remove this later

	void driveForward(double speed);
	void driveBackward(double speed);
	void driveTurnLeft(double speed);
	void driveTurnRight(double speed);
	void driveStop();

public:
	void AutoInit();
	void AutoAutoInit();
	void AutoAutoPeriodic();
	void AutoTeleopInit();
	void AutoTeleopPeriodic();
	void AutoDisable();

};

#endif /* SRC_AUTO_H_ */
