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
	// DoubleSolenoid *armSolenoid;
	DoubleSolenoid *armSolenoid2;
	DoubleSolenoid *armSolenoid3;
	// DoubleSolenoid *exsole;
	int state;
	int state2;
	int state3;
	Joystick *stick;

	// preference variables
	Preferences *prefs;
	int armSolenoidExtendPCMPort;
	int armSolenoidRetractPCMPort;
	int pcmCANID;
	int armTrigger;
	int armSolenoidExtendPCMPort2;
	int armSolenoidRetractPCMPort2;
	int armTrigger2;
	int armSolenoidExtendPCMPort3;
	int armSolenoidRetractPCMPort3;
	int shooterSolenoidExtend;
	int shooterSolenoidRetract;
	int armTrigger3;
	int auxJoystickNumber;

public:
	void ArmInit();
	void ArmAutoInit();
	void ArmAutoPeriodic();
	void ArmTeleopInit();
	void ArmTeleopPeriodic();
	void ArmDisable();

};

#endif /* SRC_ARM_H_ */
