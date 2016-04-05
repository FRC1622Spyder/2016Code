#include "WPILib.h"
#include "Arm.h"
#include "Drive.h"
#include "Shooter.h"
#include "Camera.h"
#include "Lift.h"
#include "Prefs.h"
#include "Auto.h" //disable



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
	Auto autoSystem; //disable
	Compressor *compressor;

	void RobotInit() {

		// call init on each subsystem
		prefSystem.PrefsInit(); // has to be first
		lift.LiftInit();
		arm.ArmInit();
		drive.DriveInit();
		shooter.ShooterInit();
		autoSystem.AutoInit(); //disable
		compressor = new Compressor(0);
		 camera.CameraInit(); // this subsystem needs to be called last
		camera.CameraAutoInit();
	}

	void AutonomousInit() {

			//Default Auto goes here
			autoSystem.AutoAutoInit(); //disable
			//camera.CameraAutoInit(); // this subsystem needs to be called last
	}

	void AutonomousPeriodic() {
			//Default Auto goes here
			autoSystem.AutoAutoPeriodic(); //disable
			//camera.CameraAutoPeriodic(); // this subsystem needs to be called last
	}

	void TeleopInit() {
		compressor->SetClosedLoopControl(true);
		// camera.CameraTeleopInit(); // this subsystem needs to be called last
	}

	void TeleopPeriodic() {
		lift.LiftTeleopPeriodic();
		arm.ArmTeleopPeriodic();
		drive.DriveTeleopPeriodic();
		shooter.ShooterTeleopPeriodic();
		 camera.CameraAutoPeriodic(); // this subsystem needs to be called last
	}

	void DisabledPeriodic() {
		compressor->SetClosedLoopControl(false);
		lift.LiftDisable();
		arm.ArmDisable();
		drive.DriveDisable();
		shooter.ShooterDisable();
    //    autoSystem.AutoDisable();
		// camera.CameraDisable(); // this subsystem needs to be called last
	}

};

START_ROBOT_CLASS(Robot)















