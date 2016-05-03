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
	DoubleSolenoid *exsole;
	CANTalon *topWheel;
	CANTalon *lowerWheel;
	CANTalon *collectConveyorMotor;
	int timer;
	float targetSpeed;
	float actualTopSpeed;
	float actualLowerSpeed;
	float collectVBusValue;
	float collectTargetSpeed;

	Relay *flashlightRelay;

	Preferences *prefs;
	int pcmCANID;
	int shooterSolenoidExtend;
	int shooterSolenoidRetract;
	int shooterTopMotorCANTalonID;
	int shooterBottomMotorCANTalonID;
	int shooterBallDetectSwitch;
	int auxJoystickNumber;
	int shooterTrigger;
	int collectConveyorMotorCANTalonID;
	int collectConveyerInButton;
	int collectConveyerOutButton;
	int altIntakeIn;
	int altIntakeOut;
	int flashlight;
	int choice;
	int piston;
	int counter;


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
