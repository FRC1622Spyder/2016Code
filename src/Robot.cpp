#include "WPILib.h"
#include "Config.h"
#include "Arm.h"
#include "Drive.h"
#include "Shooter.h"
#include "Camera.h" // Does not hurt to leave this on, even if camera disabled.
#include "Lift.h"
#include "Prefs.h"
#include "Auto.h"  // Does not hurt to leave this on, even if auto disabled.



using namespace std;

class Robot: public IterativeRobot {

public:


	// here we create the variables that represent each subsystem
	Lift lift;
	Arm arm;
	Drive drive;
	Shooter shooter;
#if USE_CAMERA == 1
	Camera camera;
#endif
	Prefs prefSystem;
#if USE_AUTONOMOUS == 1
	Auto autoSystem;
#endif
	Compressor *compressor;

	void RobotInit() {

		// call init on each subsystem
		prefSystem.PrefsInit(); // has to be first
		lift.LiftInit();
		arm.ArmInit();
		drive.DriveInit();
		shooter.ShooterInit();
#if USE_AUTONOMOUS == 1
		autoSystem.AutoInit();
#endif
		compressor = new Compressor(0);
#if USE_CAMERA == 1
		camera.CameraInit(); // this subsystem needs to be called last
		camera.CameraAutoInit();
#endif
	}

	void AutonomousInit() {

			//Default Auto goes here
#if USE_AUTONOMOUS == 1
			autoSystem.AutoAutoInit();
#endif
#if USE_CAMERA == 1
			camera.CameraAutoInit(); // this subsystem needs to be called last
#endif
	}

	void AutonomousPeriodic() {
			//Default Auto goes here
#if USE_AUTONOMOUS == 1
			autoSystem.AutoAutoPeriodic();
#endif
#if USE_CAMERA == 1
			camera.CameraAutoPeriodic(); // this subsystem needs to be called last
#endif
	}

	void TeleopInit() {
		compressor->SetClosedLoopControl(true);
#if USE_CAMERA == 1
		camera.CameraTeleopInit(); // this subsystem needs to be called last
#endif
	}

	void TeleopPeriodic() {
		lift.LiftTeleopPeriodic();
		arm.ArmTeleopPeriodic();
		drive.DriveTeleopPeriodic();
		shooter.ShooterTeleopPeriodic();
#if USE_CAMERA == 1
		camera.CameraAutoPeriodic(); // this subsystem needs to be called last
#endif
	}

	void DisabledPeriodic() {
		compressor->SetClosedLoopControl(false);
		lift.LiftDisable();
		arm.ArmDisable();
		drive.DriveDisable();
		shooter.ShooterDisable();
#if USE_AUTONOMOUS == 1
    //    autoSystem.AutoDisable();
#endif
#if USE_CAMERA == 1
		camera.CameraDisable(); // this subsystem needs to be called last
#endif
	}

};

START_ROBOT_CLASS(Robot)















