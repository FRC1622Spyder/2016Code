/*
 * Shooter.h
 *
 *  Created on: Feb 10, 2016
 *      Author: Admin
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

class Shooter {
private:
	int firePhase;
	Joystick *shooterJoystick;
	bool shooterButtonvalue;
	int ceeout;
	Solenoid *exsole;
	Timer *rightTimer;
	DigitalInput *shooterLimitSwitch;
	DigitalInput *shooterLimitSwitch1;
	DigitalInput *shooterLimitSwitch2;
	CANTalon *topWheel;
	CANTalon *lowerWheel;
	int timer;

	Preferences *prefs;
	int pcmCANID;
	int shooterSolenoidExtend;
	int shooterSolenoidRetract;
	int shooterTopMotorCANTalonID;
	int shooterBottomMotorCANTalonID;
	int shooterBallDetectSwitch;
	int driveJoystickNumber;
	int shooterTrigger;

public:
	void ShooterInit();
	void ShooterAutoInit();
	void ShooterAutoPeriodic();
	void ShooterTeleopInit();
	void ShooterTeleopPeriodic();
	void ShooterDisable();

};

#endif /* SRC_SHOOTER_H_ */
