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
	piston = prefs->GetInt("piston");

	timer = 0;
	choice = 0;
	targetSpeed = prefs->GetFloat("shooterTargetSpeed");
//	actualTopSpeed = 0.0f;
//	actualLowerSpeed = 0.0f;

//Set up wheels
	topWheel = new CANTalon(shooterTopMotorCANTalonID);
	lowerWheel = new CANTalon(shooterBottomMotorCANTalonID);
	collectConveyorMotor = new CANTalon(collectConveyorMotorCANTalonID);

	// set up encoders
//	topWheel->SetFeedbackDevice(CANTalon::QuadEncoder);
//	topWheel->ConfigEncoderCodesPerRev(250);
//	lowerWheel->SetFeedbackDevice(CANTalon::QuadEncoder);
//	lowerWheel->ConfigEncoderCodesPerRev(250);
//	lowerWheel->SetSensorDirection(true);

// set control mode to closed-loop velocity
	topWheel->SetControlMode(CANSpeedController::kPercentVbus);
	lowerWheel->SetControlMode(CANSpeedController::kPercentVbus);
	collectConveyorMotor->SetControlMode(CANSpeedController::kPercentVbus);
	collectVBusValue = 0.9; // TODO need to figure out what the right speed is for this. (Percent VBus)

	//set speeds to 0
	topWheel->Set(0);
	lowerWheel->Set(0);

	//set voltages
//	topWheel->ConfigNominalOutputVoltage(+0.0f, -0.0f);
//	lowerWheel->ConfigNominalOutputVoltage(+0.0f, -0.0f);
//	topWheel->ConfigPeakOutputVoltage(+12.0f, -12.0f);
//	lowerWheel->ConfigPeakOutputVoltage(+12.0f, -12.0f);

	//set closed loop gains
	//TODO == play with these to get the speed consistent
//	topWheel->SelectProfileSlot(0);
//	lowerWheel->SelectProfileSlot(0);
//	topWheel->SetPID(0.8f, 0.008f, 20.0f, 0.3897f);
//	lowerWheel->SetPID(0.8f, 0.008f, 20.0f, 0.3897f);

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


	if (shooterJoystick->GetRawButton(collectConveyerInButton)) {
		collectConveyorMotor->Set(collectVBusValue);
		lowerWheel->Set(collectVBusValue);
		collectTargetSpeed = prefs->GetFloat("collectTargetSpeed"); // get this speed from prefs file
		//		lowerWheel->Set(collectTargetSpeed);
	} else if (shooterJoystick->GetRawButton(collectConveyerOutButton)) {
		cout << "out" << endl;
		collectConveyorMotor->Set(-1 * collectVBusValue);
		lowerWheel->Set(-1 * collectVBusValue);
		collectTargetSpeed = prefs->GetFloat("collectTargetSpeed"); // get this speed from prefs file
		//		lowerWheel->Set(-1 * collectTargetSpeed);
	} else if (shooterJoystick->GetRawButton(shooterTrigger)) {
		targetSpeed = prefs->GetFloat("shooterTargetSpeed"); // get new target speed from prefs file in case changed through dashboard
		topWheel->Set(targetSpeed);
		lowerWheel->Set(targetSpeed);
	} else {
		topWheel->Set(0);
		lowerWheel->Set(0);
		collectConveyorMotor->Set(0);
	}

	switch (choice) {
		case 0:
			//cout << "Arm: In state 0" << endl;
			exsole->Set(DoubleSolenoid::Value::kReverse);
			if (shooterJoystick->GetRawButton(piston)) {
				choice = 2;
				break;
			}
			break;
		case 1:
			//cout << "Arm: In state 1" << endl;
			exsole->Set(DoubleSolenoid::Value::kForward);
			if (shooterJoystick->GetRawButton(piston)) {
				choice = 3;
				break;
			}
			break;
		case 2:
			//cout << "Arm: In state 2" << endl;
			if (!shooterJoystick->GetRawButton(piston)) {
				choice = 1;
				break;
			}
			break;
		case 3:
			//cout << "Arm: In state 3" << endl;
			if (!shooterJoystick->GetRawButton(piston)) {
				choice = 0;
				break;
			}
			break;
		}

}

/* actualTopSpeed = topWheel->GetSpeed();
 actualLowerSpeed = lowerWheel->GetSpeed();
 cout << "Top Speed: " << actualTopSpeed << endl;
 cout << "Lower Speed: " << actualLowerSpeed << endl;
 if (WithinPercent(targetSpeed, actualTopSpeed)
 & WithinPercent(targetSpeed, actualLowerSpeed)) {
 exsole->Set(DoubleSolenoid::Value::kForward);
 //if(actualTopSpeed )

 } else {
 cout << "nothing" << endl;
 lowerWheel->Set(0);
 topWheel->Set(0);
 exsole->Set(DoubleSolenoid::Value::kReverse);
 collectConveyorMotor->Set(0.0f);
 }

 }



switch (firePhase) //meant to fire then reset
 {

 case 0: //check if launch button pressed
 cout << "0" << endl;
 // If in button is pressed, go in
 if (shooterJoystick->GetRawButton(collectConveyerInButton)) {
 cout << "in pressed" << endl;

 collectConveyorMotor->Set(collectVBusValue);
 collectTargetSpeed = prefs->GetFloat("collectTargetSpeed"); // get this speed from prefs file
 lowerWheel->Set(collectTargetSpeed);
 }

 // If out button is pressed, go out
 else if (shooterJoystick->GetRawButton(collectConveyerOutButton)) {
 cout << "out pressed" << endl;

 collectConveyorMotor->Set(-1 * collectVBusValue);
 collectTargetSpeed = prefs->GetFloat("collectTargetSpeed"); // get this speed from prefs file
 lowerWheel->Set(-1 * collectTargetSpeed);
 }

 // If no button is pressed, stop motors
 else {
 cout << "nothing pressed" << endl;
 collectConveyorMotor->Set(0);
 lowerWheel->Set(0);
 }

 // Check if shoot trigger pressed
 shooterButtonvalue = shooterJoystick->GetRawButton(shooterTrigger);
 if (shooterButtonvalue) {
 firePhase++;
 shooterButtonvalue = false;
 }
 break;

 case 1: //spin up flywheels
 cout << "1: timer: " << timer << endl;
 targetSpeed = prefs->GetFloat("shooterTargetSpeed"); // get new target speed from prefs file in case changed through dashboard
 topWheel->Set(targetSpeed);
 lowerWheel->Set(targetSpeed);
 //	 actualTopSpeed = topWheel->GetSpeed();
 //	 actualLowerSpeed = lowerWheel->GetSpeed();
 //	 cout << "Top Speed: " << actualTopSpeed << endl;
 //	 cout << "Lower Speed: " << actualLowerSpeed << endl;
 timer = timer + 1;
 if (timer >= 150) {
 timer = 0;
 firePhase++;

 //		} else if (WithinPercent(targetSpeed, actualTopSpeed)
 //				and WithinPercent(targetSpeed, actualLowerSpeed)) {
 //			timer = 0;
 //			firePhase++;
 }
 break;

 case 2: //fire piston

 exsole->Set(DoubleSolenoid::Value::kForward);
 firePhase++;

 break;

 case 3: // wait 1.5 seconds to make sure ball is gone

 timer = timer + 1;
 if (timer >= 75) {
 firePhase++;
 }
 break;

 case 4: //reset piston , deactivate flywheels

 topWheel->Set(0);
 lowerWheel->Set(0);
 exsole->Set(DoubleSolenoid::Value::kReverse);
 firePhase = 0;
 break;

 }
 //

 }

 // checks whether actual speed is within a certain percentage of target speed
 bool Shooter::WithinPercent(float target, float actual) {
 float difference = 1.0 - (actual / target);
 // put percentage in next line
 if (difference < .01 and difference > -.01) {
 return true;
 } else {
 return false;
 }
 }*/
