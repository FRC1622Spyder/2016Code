/*
 * Lift.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Admin
 */

#ifndef SRC_LIFT_H_
#define SRC_LIFT_H_


class Lift {
private:
	int state = 0;
	Joystick *stick;
	Preferences *prefs;
	DigitalInput *liftLimitSwitch1;
	DigitalInput *liftLimitSwitch2;
	DigitalInput *liftLimitSwitch3;
	CANTalon *liftMotor;
	bool logOnce;
	int liftMotorCANTalonID;
	int liftLimitSwitchLow;
	int liftLimitSwitchMed;
	int liftLimitSwitchHigh;
	int liftUpButton;
	int liftDownButton;
	int driveJoystickNumber;

public:
	void LiftInit();
	void LiftAutoInit();
	void LiftAutoPeriodic();
	void LiftTeleopInit();
	void LiftTeleopPeriodic();
	void LiftDisable();

};



#endif /* SRC_LIFT_H_ */
