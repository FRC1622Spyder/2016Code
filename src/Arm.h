/*
 * Arm.h
 *
 *  Created on: Feb 10, 2016
 *      Author: Admin
 */

#ifndef SRC_ARM_H_
#define SRC_ARM_H_

class Arm {
private:

	// variables used in the code
	DoubleSolenoid *armSolenoid;
	int state;
	Joystick *stick;

	// preference variables
	Preferences *prefs;
	int armSolenoidExtendPCMPort;
	int armSolenoidRetractPCMPort;
	int pcmCANID;
	int armTrigger;
	int driveJoystickNumber;

public:
	void ArmInit();
	void ArmAutoInit();
	void ArmAutoPeriodic();
	void ArmTeleopInit();
	void ArmTeleopPeriodic();
	void ArmDisable();

};

#endif /* SRC_ARM_H_ */
