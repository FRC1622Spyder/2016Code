#include "WPILib.h"
#include "Arm.h"
#include <iostream>

using namespace std;

void Arm::ArmInit() {

	// Read the preferences from the preferences instance
	prefs = Preferences::GetInstance();
	pcmCANID = prefs->GetInt("pcmCANID", 7);
	armSolenoidExtendPCMPort = prefs->GetInt("armSolenoidExtendPCMPort", 0);
	armSolenoidRetractPCMPort = prefs->GetInt("armSolenoidRetractPCMPort", 1);
	armTrigger = prefs->GetInt("armTrigger", 5);
	driveJoystickNumber = prefs->GetInt("driveJoystickNumber", 0);

	armSolenoid = new DoubleSolenoid(pcmCANID, armSolenoidExtendPCMPort,
			armSolenoidRetractPCMPort);
	stick = new Joystick(driveJoystickNumber);
	state = 0;
}

void Arm::ArmDisable() {

	armSolenoid->Set(DoubleSolenoid::Value::kOff);
}

void Arm::ArmAutoInit() {
}

void Arm::ArmAutoPeriodic() {
}

void Arm::ArmTeleopInit() {

}

void Arm::ArmTeleopPeriodic() {
	switch (state) {
	case 0:
		//cout << "Arm: In state 0" << endl;
		armSolenoid->Set(DoubleSolenoid::Value::kForward);
		if (stick->GetRawButton(armTrigger)) {
			state = 2;
			break;
		}
		break;
	case 1:
		//cout << "Arm: In state 1" << endl;
		armSolenoid->Set(DoubleSolenoid::Value::kReverse);
		if (stick->GetRawButton(armTrigger)) {
			state = 3;
			break;
		}
		break;
	case 2:
		//cout << "Arm: In state 2" << endl;
		if (!stick->GetRawButton(armTrigger)) {
			state = 1;
			break;
		}
		break;
	case 3:
		//cout << "Arm: In state 3" << endl;
		if (!stick->GetRawButton(armTrigger)) {
			state = 0;
			break;
		}
		break;
	}

}

