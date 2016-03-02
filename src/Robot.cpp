#include "WPILib.h"
#include "Arm.h"
#include "Drive.h"
#include "Shooter.h"
#include "Camera.h"
#include "Lift.h"
#include "Prefs.h"
#include "Auto.h"



using namespace std;

class Robot: public IterativeRobot {

public:


	// here we create the variables that represent each subsystem
	Lift lift;
	Arm arm;
	Drive drive;
	Shooter shooter;
	Camera camera;
	Prefs prefSystem;
	Auto autoSystem;

	void RobotInit() {

		// call init on each subsystem
		prefSystem.PrefsInit(); // has to be first
		lift.LiftInit();
		arm.ArmInit();
		drive.DriveInit();
		shooter.ShooterInit();
		autoSystem.AutoInit();
		camera.CameraInit(); // this subsystem needs to be called last



	}

	void AutonomousInit() {

			//Default Auto goes here
			autoSystem.AutoAutoInit();
			//camera.CameraAutoInit(); // this subsystem needs to be called last
	}

	void AutonomousPeriodic() {
			//Default Auto goes here
			autoSystem.AutoAutoPeriodic();
			//camera.CameraAutoPeriodic(); // this subsystem needs to be called last
	}

	void TeleopInit() {
		//camera.CameraTeleopInit(); // this subsystem needs to be called last
	}

	void TeleopPeriodic() {
		lift.LiftTeleopPeriodic();
		arm.ArmTeleopPeriodic();
		drive.DriveTeleopPeriodic();
		shooter.ShooterTeleopPeriodic();
		//camera.CameraTeleopPeriodic(); // this subsystem needs to be called last
	}

	void DisabledPeriodic() {
		lift.LiftDisable();
		arm.ArmDisable();
		drive.DriveDisable();
		shooter.ShooterDisable();
		autoSystem.AutoDisable();
		//camera.CameraDisable(); // this subsystem needs to be called last
	}

};

START_ROBOT_CLASS(Robot)
