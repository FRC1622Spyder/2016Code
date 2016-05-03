#include "WPILib.h"
#include "Arm.h"
#include "Drive.h"
#include "Shooter.h"
//#include "Camera.h" //Uncomment this to turn on camera
#include "Lift.h"
#include "Prefs.h"
#include "Auto.h"  // Comment out to disable autonomous



using namespace std;

class Robot: public IterativeRobot {

public:


	// here we create the variables that represent each subsystem
	Lift lift;
	Arm arm;
	Drive drive;
	Shooter shooter;
	//Camera camera; //Uncomment to enable camera
	Prefs prefSystem;
	Auto autoSystem; // Comment out to disable autonomous
	Compressor *compressor;

	void RobotInit() {

		// call init on each subsystem
		prefSystem.PrefsInit(); // has to be first
		lift.LiftInit();
		arm.ArmInit();
		drive.DriveInit();
		shooter.ShooterInit();
		autoSystem.AutoInit(); // Comment out to disable autonomous
		compressor = new Compressor(0);
		//camera.CameraInit(); // this subsystem needs to be called last
		//camera.CameraAutoInit();  //Uncomment these to enable camera
	}

	void AutonomousInit() {

			//Default Auto goes here
			autoSystem.AutoAutoInit(); // Comment out to disable autonomous
			//camera.CameraAutoInit(); // this subsystem needs to be called last
	}

	void AutonomousPeriodic() {
			//Default Auto goes here
			autoSystem.AutoAutoPeriodic(); // Comment out to disable autonomous
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
		//camera.CameraAutoPeriodic(); // this subsystem needs to be called last - uncomment to enable camera
	}

	void DisabledPeriodic() {
		compressor->SetClosedLoopControl(false);
		lift.LiftDisable();
		arm.ArmDisable();
		drive.DriveDisable();
		shooter.ShooterDisable();
    //    autoSystem.AutoDisable();
		//camera.CameraDisable(); // this subsystem needs to be called last - uncomment to enable
	}

};

START_ROBOT_CLASS(Robot)















