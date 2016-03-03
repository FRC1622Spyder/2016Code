#include "WPILib.h"
#include "Arm.h"
#include <iostream>

using namespace std;

void Arm::ArmInit() {

	// Read the preferences from the preferences instance
	prefs = Preferences::GetInstance();
	pcmCANID = prefs->GetInt("pcmCANID");
	armSolenoidExtendPCMPort = prefs->GetInt("armSolenoidExtendPCMPort");
	armSolenoidRetractPCMPort = prefs->GetInt("armSolenoidRetractPCMPort");
	armTrigger = prefs->GetInt("armTrigger");
	driveJoystickNumber = prefs->GetInt("driveJoystickNumber");

	armSolenoid = new DoubleSolenoid(pcmCANID, armSolenoidExtendPCMPort,
			armSolenoidRetractPCMPort);
	stick = new Joystick(driveJoystickNumber);

	armSolenoidExtendPCMPort2 = prefs->GetInt("armSolenoidExtendPCMPort2");
	armSolenoidRetractPCMPort2 = prefs->GetInt("armSolenoidRetractPCMPort2");
	armTrigger2 = prefs->GetInt("armTrigger2");

	armSolenoid2 = new DoubleSolenoid(pcmCANID, armSolenoidExtendPCMPort2,
			armSolenoidRetractPCMPort2);

	armSolenoidExtendPCMPort3 = prefs->GetInt("armSolenoidExtendPCMPort3");
	armSolenoidRetractPCMPort3 = prefs->GetInt("armSolenoidRetractPCMPort3");
	armTrigger3 = prefs->GetInt("armTrigger3");

	armSolenoid3 = new DoubleSolenoid(pcmCANID, armSolenoidExtendPCMPort3,
			armSolenoidRetractPCMPort3);

	armSolenoidExtendPCMPort4 = prefs->GetInt("armSolenoidExtendPCMPort4");
	armSolenoidRetractPCMPort4 = prefs->GetInt("armSolenoidRetractPCMPort4");
	armTrigger4 = prefs->GetInt("armTrigger4");

	armSolenoid4 = new DoubleSolenoid(pcmCANID, armSolenoidExtendPCMPort4,
			armSolenoidRetractPCMPort4);

	state = 0;
	solenoidSelect = 0;
}

void Arm::ArmDisable() {

	armSolenoid->Set(DoubleSolenoid::Value::kReverse);
	armSolenoid2->Set(DoubleSolenoid::Value::kReverse);
	armSolenoid3->Set(DoubleSolenoid::Value::kReverse);
	armSolenoid4->Set(DoubleSolenoid::Value::kReverse);
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
		armSolenoid2->Set(DoubleSolenoid::Value::kForward);
		armSolenoid3->Set(DoubleSolenoid::Value::kForward);
		armSolenoid4->Set(DoubleSolenoid::Value::kForward);
		if (stick->GetRawButton(armTrigger)) {
			solenoidSelect = 1;
			state = 2;
			break;
		}
		else if (stick->GetRawButton(armTrigger2)) {
			solenoidSelect = 2;
			state = 2;
			break;
		}
		else if (stick->GetRawButton(armTrigger3)) {
			solenoidSelect = 3;
			state = 2;
			break;
		}
		else if (stick->GetRawButton(armTrigger4)) {
			solenoidSelect = 4;
			state = 2;
			break;
		}
		break;
	case 1:
		//cout << "Arm: In state 1" << endl;
		if(solenoidSelect == 1){
			armSolenoid->Set(DoubleSolenoid::Value::kReverse);
		}
		else if(solenoidSelect == 2){
			armSolenoid2->Set(DoubleSolenoid::Value::kReverse);
		}
		else if(solenoidSelect == 3){
			armSolenoid3->Set(DoubleSolenoid::Value::kReverse);
		}
		else if(solenoidSelect == 4){
			armSolenoid4->Set(DoubleSolenoid::Value::kReverse);
		}

		if (stick->GetRawButton(armTrigger) ||
				stick->getRawButton(armTrigger2) ||
				stick->getRawButton(armTrigger3) ||
				stick->getRawButton(armTrigger4)){
			solenoidSelect = 0;
			state = 3;
			break;
		}
		break;
	case 2:
		//cout << "Arm: In state 2" << endl;
		if (!stick->GetRawButton(armTrigger) &&
				!stick->GetRawButton(armTrigger2) &&
				!stick->GetRawButton(armTrigger3) &&
				!stick->GetRawButton(armTrigger4)){
			state = 1;
			break;
		}
		break;
	case 3:
		//cout << "Arm: In state 3" << endl;
		if (!stick->GetRawButton(armTrigger) &&
				!stick->GetRawButton(armTrigger2)
				!stick->GetRawButton(armTrigger3)
				!stick->GetRawButton(armTrigger4)){
			state = 0;
			break;
		}
		break;
	}

}
