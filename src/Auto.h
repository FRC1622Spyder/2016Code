#ifndef SRC_AUTO_H_
#define SRC_AUTO_H_

class Auto {

private:
	int autoLoopCounter;
	CANTalon *leftBackMotor;
	CANTalon *rightBackMotor;
	CANTalon *leftFrontMotor;
	CANTalon *rightFrontMotor; //TODO add firing motors

	Preferences *prefs;

	int frontRightMotorCANTalonID;
	int frontLeftMotorCANTalonID;
	int backRightMotorCANTalonID;
	int backLeftMotorCANTalonID;

	int shooterSolenoidExtend;
	int shooterSolenoidRetract;
	int shooterTopMotorCANTalonID;
	int shooterBottomMotorCANTalonID;
	int firePhase;
	int pcmCANID;
	DoubleSolenoid *exsole;

	float targetSpeed;

	CANTalon *topWheel;
	CANTalon *lowerWheel;

	double wheelCircumfrence;
	double driveRatio;
    double targetPosition;

	SendableChooser *turnChooser;
	std::string autoStraight;
	std::string autoLeft;
	std::string autoRight;
	std::string turnSelected;
	SendableChooser *rotateChooser;
	std::string autoRotateNone;
	std::string autoRotateLeft;
	std::string autoRotateRight;
	std::string rotateSelected;
	SendableChooser *obstacleChooser;
	std::string Default;
	std::string Moat;
	std::string RoughTerrain;
	std::string Ramparts;
	std::string Seesaw;
	std::string Drawbridge;
	std::string Portcullis;
	std::string SallyPort;
	std::string RockWall;
	std::string obstacleSelected;

	int state;
	int leftEncoderPosition;
	int rightEncoderPosition;
	int toBeReplaced; //TODO remove this later

	void driveForward(double speed);
	void driveBackward(double speed);
	void driveTurnLeft(double speed);
	void driveTurnRight(double speed);
	void driveStop();
	int SelectionToInt(std::string ObstacleString);

public:
	void AutoInit();
	void AutoAutoInit();
	void AutoAutoPeriodic();
	void AutoTeleopInit();
	void AutoTeleopPeriodic();
	void AutoDisable();

};

#endif /* SRC_AUTO_H_ */
