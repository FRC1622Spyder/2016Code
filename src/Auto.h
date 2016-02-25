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
	CANTalon *leftBackMotor;
	CANTalon *rightBackMotor;
	CANTalon *leftFrontMotor;
	CANTalon *rightFrontMotor;

	Preferences *prefs;

	int frontRightMotorCANTalonID;
	int frontLeftMotorCANTalonID;
	int backRightMotorCANTalonID;
	int backLeftMotorCANTalonID;

	double wheelCircumfrence;
	double driveRatio;
	int timer;

public:
	void AutoInit();
	void AutoAutoInit();
	void AutoAutoPeriodic();
	void AutoTeleopInit();
	void AutoTeleopPeriodic();
	void AutoDisable();

	void allSpeedSet(double s);
	void leftSpeedSet(double s);
	void rightSpeedSet(double s);

};

#endif /* SRC_AUTO_H_ */
