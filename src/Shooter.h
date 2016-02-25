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
	DoubleSolenoid *exsole;
	CANTalon *topWheel;
	CANTalon *lowerWheel; // public so it can be accessed by collect
	int timer;
	float targetSpeed;
	float actualTopSpeed;
	float actualLowerSpeed;

	Preferences *prefs;
	int pcmCANID;
	int shooterSolenoidExtend;
	int shooterSolenoidRetract;
	int shooterTopMotorCANTalonID;
	int shooterBottomMotorCANTalonID;
	int shooterBallDetectSwitch;
	int driveJoystickNumber;
	int shooterTrigger;

	bool WithinPercent(float target,float actual);

public:

	void ShooterInit();
	void ShooterAutoInit();
	void ShooterAutoPeriodic();
	void ShooterTeleopInit();
	void ShooterTeleopPeriodic();
	void ShooterDisable();

};

#endif /* SRC_SHOOTER_H_ */
