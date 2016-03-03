#include "WPILib.h"
#include "Shooter.h"
#include <iostream>
#include <cmath>
using namespace std;

void Shooter::ShooterInit() {

	prefs = Preferences::GetInstance();
	pcmCANID = prefs->GetInt("pcmCANID");
	shooterSolenoidExtend = prefs->GetInt("shooterSolenoidExtend");
	shooterSolenoidRetract = prefs->GetInt("shooterSolenoidRetract");
	shooterTopMotorCANTalonID = prefs->GetInt("shooterTopMotorCANTalonID");
	shooterBottomMotorCANTalonID = prefs->GetInt(
			"shooterBottomMotorCANTalonID");
	collectConveyorMotorCANTalonID = prefs->GetInt(
			"collectConveyorMotorCANTalonID");
	auxJoystickNumber = prefs->GetInt("auxJoystickNumber");
	shooterTrigger = prefs->GetInt("shooterTrigger");
	firePhase = 0;
	shooterJoystick = new Joystick(auxJoystickNumber);
	shooterButtonvalue = false;
	exsole = new DoubleSolenoid(pcmCANID, shooterSolenoidExtend,
			shooterSolenoidRetract);
	collectConveyerInButton = prefs->GetInt("collectConveyerInButton");
	collectConveyerOutButton = prefs->GetInt("collectConveyerOutButton");

	timer = 0;
	targetSpeed = prefs->GetFloat("shooterTargetSpeed", 10.0f);
	actualTopSpeed = 0.0f;
	actualLowerSpeed = 0.0f;

	//Set up wheels
	topWheel = new CANTalon(shooterTopMotorCANTalonID);
	lowerWheel = new CANTalon(shooterBottomMotorCANTalonID);
	collectConveyorMotor = new CANTalon(collectConveyorMotorCANTalonID);

	// set up encoders
	topWheel->SetFeedbackDevice(CANTalon::QuadEncoder);
	topWheel->ConfigEncoderCodesPerRev(250);
	lowerWheel->SetFeedbackDevice(CANTalon::QuadEncoder);
	lowerWheel->ConfigEncoderCodesPerRev(250);
	lowerWheel->SetSensorDirection(true);

	// set control mode to closed-loop velocity
	topWheel->SetControlMode(CANSpeedController::kSpeed);
	lowerWheel->SetControlMode(CANSpeedController::kSpeed);
	collectConveyorMotor->SetControlMode(CANSpeedController::kPercentVbus);
	collectVBusValue = 0.5; // TODO need to figure out what the right speed is for this. (Percent VBus)

	//set speeds to 0
	topWheel->Set(0);
	lowerWheel->Set(0);

	//set voltages
	topWheel->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	lowerWheel->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	topWheel->ConfigPeakOutputVoltage(+12.0f, -12.0f);
	lowerWheel->ConfigPeakOutputVoltage(+12.0f, -12.0f);

	//set closed loop gains
	//TODO == play with these to get the speed consistent
	topWheel->SelectProfileSlot(0);
	lowerWheel->SelectProfileSlot(0);
	topWheel->SetPID(1.023f, 0.0f, 0.0f, 0.3897f);
	lowerWheel->SetPID(1.023f, 0.0f, 0.0f, 0.3897sf);

}

void Shooter::ShooterDisable() {

	lowerWheel->Set(0);
	topWheel->Set(0);
	exsole->Set(DoubleSolenoid::Value::kReverse);
	collectConveyorMotor->Set(0.0f);
}

void Shooter::ShooterAutoInit() {

}

void Shooter::ShooterAutoPeriodic() {

}

void Shooter::ShooterTeleopInit() {

}

void Shooter::ShooterTeleopPeriodic() {

	double leftYstick = shooterJoystick->GetRawAxis(1);
	double motorOutput = lowerWheel->GetOutputVoltage() / lowerWheel->GetBusVoltage();
	double targetSpeed = leftYstick * 1500.0;

	if(shooterJoystick->GetRawButton(shooterTrigger)) {
		lowerWheel->SetControlMode(CANSpeedController::kSpeed);
		lowerWheel->Set(targetSpeed);
	}
	else {
		lowerWheel->SetControlMode(CANSpeedController::kPercentVbus);
		lowerWheel->Set(leftYstick);
	}

	if (++timer >= 10) {
		timer = 0;
		cout << "out: " << motorOutput << " spd: " << lowerWheel->GetSpeed();
		cout << " err: " << lowerWheel->GetClosedLoopError() << " trg: " << targetSpeed << endl;
	}
}

// checks whether actual speed is within a certain percentage of target speed
bool Shooter::WithinPercent(float target, float actual) {
	float difference = 1.0 - (actual / target);
	// put percentage in next line
	if (difference < .05 and difference > -.05) {
		return true;
	} else {
		return false;
	}
}
