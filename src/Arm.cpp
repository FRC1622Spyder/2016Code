#include "WPILib.h"
#include "Arm.h"
#include <iostream>

using namespace std;

void Arm::ArmInit() {

	// Read the preferences from the preferences instance
	prefs = Preferences::GetInstance();
	pcmCANID = prefs->GetInt("pcmCANID");
	//armSolenoidExtendPCMPort = prefs->GetInt("armSolenoidExtendPCMPort");
	//armSolenoidRetractPCMPort = prefs->GetInt("armSolenoidRetractPCMPort");
	//armTrigger = prefs->GetInt("armTrigger");
	armSolenoidExtendPCMPort2 = prefs->GetInt("armSolenoidExtendPCMPort2");
	armSolenoidRetractPCMPort2 = prefs->GetInt("armSolenoidRetractPCMPort2");
	armTrigger2 = prefs->GetInt("armTrigger2");
	armSolenoidExtendPCMPort3 = prefs->GetInt("armSolenoidExtendPCMPort3");
	armSolenoidRetractPCMPort3 = prefs->GetInt("armSolenoidRetractPCMPort3");
	armTrigger3 = prefs->GetInt("armTrigger3");
	auxJoystickNumber = prefs->GetInt("auxJoystickNumber");

	//armSolenoid = new DoubleSolenoid(pcmCANID, shooterSolenoidExtend,
		//	shooterSolenoidRetract);
	armSolenoid2 = new DoubleSolenoid(pcmCANID, armSolenoidExtendPCMPort2,
			armSolenoidRetractPCMPort2);
	armSolenoid3 = new DoubleSolenoid(pcmCANID, armSolenoidExtendPCMPort3,
			armSolenoidRetractPCMPort3);
	stick = new Joystick(auxJoystickNumber);
	state = 0;
}

void Arm::ArmDisable() {

	//armSolenoid->Set(DoubleSolenoid::Value::kReverse);
	armSolenoid2->Set(DoubleSolenoid::Value::kReverse);
	armSolenoid3->Set(DoubleSolenoid::Value::kReverse);
}

void Arm::ArmAutoInit() {
}

void Arm::ArmAutoPeriodic() {
}

void Arm::ArmTeleopInit() {

}

void Arm::ArmTeleopPeriodic() {
/*	switch (state) {
	case 0:
		//cout << "Arm: In state 0" << endl;
		armSolenoid->Set(DoubleSolenoid::Value::kReverse);
		if (stick->GetRawButton(armTrigger)) {
			state = 2;
			break;
		}
		break;
	case 1:
		//cout << "Arm: In state 1" << endl;
		armSolenoid->Set(DoubleSolenoid::Value::kForward);
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
	}*/

	switch (state2) {
	case 0:
		//cout << "Arm: In state 0" << endl;
		if (stick->GetRawButton(armTrigger2)) {
			armSolenoid2->Set(DoubleSolenoid::Value::kForward);
			state2 = 2;
			break;
		}
		break;
	case 1:
		//cout << "Arm: In state 1" << endl;
		armSolenoid2->Set(DoubleSolenoid::Value::kReverse);
		if (stick->GetRawButton(armTrigger2)) {
			state2 = 3;
			break;
		}
		break;
	case 2:
		//cout << "Arm: In state 2" << endl;
		if (!stick->GetRawButton(armTrigger2)) {
			state2 = 1;
			break;
		}
		break;
	case 3:
		//cout << "Arm: In state 3" << endl;
		if (!stick->GetRawButton(armTrigger2)) {
			state2 = 0;
			break;
		}
		break;
	}

	switch (state3) {
	case 0:
		//cout << "Arm: In state 0" << endl;
		armSolenoid3->Set(DoubleSolenoid::Value::kForward);
		if (stick->GetRawButton(armTrigger3)) {
			state3 = 2;
			break;
		}
		break;
	case 1:
		//cout << "Arm: In state 1" << endl;
		armSolenoid3->Set(DoubleSolenoid::Value::kReverse);
		if (stick->GetRawButton(armTrigger3)) {
			state3 = 3;
			break;
		}
		break;
	case 2:
		//cout << "Arm: In state 2" << endl;
		if (!stick->GetRawButton(armTrigger3)) {
			state3 = 1;
			break;
		}
		break;
	case 3:
		//cout << "Arm: In state 3" << endl;
		if (!stick->GetRawButton(armTrigger3)) {
			state3 = 0;
			break;
		}
		break;
	}


}
