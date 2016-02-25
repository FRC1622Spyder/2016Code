/*
 * Collect.h
 *
 *  Created on: Feb 10, 2016
 *      Author: Admin
 */

#ifndef SRC_COLLECT_H_
#define SRC_COLLECT_H_

class Collect {

private:
	CANTalon *collectConveyorMotor;
	CANTalon *lowerWheel;

	Joystick *joy;
	float collectTargetSpeed; // This is the target speed for the lower shooter motor when used during intake
	float collectVBusValue; // This is for the intake motor

	Preferences *prefs;

	int collectConveyorMotorCANTalonID;
	int shooterBottomMotorCANTalonID;
	int auxJoystickNumber;
	int collectConveyerInButton;
	int collectConveyerOutButton;

public:
	void CollectInit();
	void CollectAutoInit();
	void CollectAutoPeriodic();
	void CollectTeleopInit();
	void CollectTeleopPeriodic();
	void CollectDisable();

};

#endif /* SRC_COLLECT_H_ */
