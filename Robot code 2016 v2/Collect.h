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
	CANTalon *collectArmMotor;
	CANTalon *shooterTopMotor;
	CANTalon *shooterBottomMotor;
	Joystick *joy;

	Preferences *prefs;

	int collectConveyorMotorCANTalonID;
	int collectArmMotorCANTalonID;
	int shooterBottomMotorCANTalonID;
	int collectBallDetectSwitch1;
	int collectBallDetectSwitch2;
	int collectConveyerUpSwitch;
	int collectConveyerDownSwitch;
	int auxJoystickNumber;
	int collectConveyerInButton;
	int collectConveyerOutButton;
	int collectConveyerUpButton;
	int collectConveyerDownButton;
	int collectFinalLoadButton;

public:
	void CollectInit();
	void CollectAutoInit();
	void CollectAutoPeriodic();
	void CollectTeleopInit();
	void CollectTeleopPeriodic();
	void CollectDisable();

};

#endif /* SRC_COLLECT_H_ */
