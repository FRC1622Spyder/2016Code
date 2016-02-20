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
	CANTalon *rightFrontMotor;

	Preferences *prefs;

	double wheelCircumfrence;
	double driveRatio;

	int frontRightMotorCANTalonID;
	int frontLeftMotorCANTalonID;
	int backRightMotorCANTalonID;
	int backLeftMotorCANTalonID;

	void allSpeedSet(double s);
	void leftSpeedSet(double s);
	void rightSpeedSet(double s);

public:
	void AutoInit();
	void AutoAutoInit();
	void AutoAutoPeriodic();
	void AutoTeleopInit();
	void AutoTeleopPeriodic();
	void AutoDisable();

};

#endif /* SRC_AUTO_H_ */
