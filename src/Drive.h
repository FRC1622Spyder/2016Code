/*
 * Drive.h
 *
 *  Created on: Feb 10, 2016
 *      Author: Admin
 */

#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_

class Drive {

private:
	int autoLoopCounter;
	CANTalon *leftBackMotor;
	CANTalon *rightBackMotor;
	CANTalon *leftFrontMotor;
	CANTalon *rightFrontMotor;
	Joystick *joy;
	bool halfButtonValue;

	Preferences *prefs;

	int frontRightMotorCANTalonID;
	int frontLeftMotorCANTalonID;
	int backRightMotorCANTalonID;
	int backLeftMotorCANTalonID;
	int driveJoystickNumber;
	int leftAxis;
	int rightAxis;

	double wheelCircumfrence;
	double driveRatio;
	double rampRate;

public:
	void DriveInit();
	void DriveAutoInit();
	void DriveAutoPeriodic();
	void DriveTeleopInit();
	void DriveTeleopPeriodic();
	void DriveDisable();

	void allSpeedSet(double s);
	void leftSpeedSet(double s);
	void rightSpeedSet(double s);


};

#endif /* SRC_DRIVE_H_ */
