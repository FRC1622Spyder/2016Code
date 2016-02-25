#include "WPILib.h"
#include "Arm.h"
#include "Drive.h"
#include "Shooter.h"
#include "Camera.h"
#include "Lift.h"
#include "Prefs.h"
#include "Auto.h"
#include "Collect.h"


using namespace std;

class Robot: public IterativeRobot {

public:

	// used for selecting which autonomous code is called.  unsused currently.
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	// here we create the variables that represent each subsystem
	Lift lift;
	Arm arm;
	Drive drive;
	Shooter shooter;
	Camera camera;
	Prefs prefSystem;
	Collect collect;
	Auto autoSystem;

	void RobotInit() {

		// selecting autonomous code -- not used
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*) &autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*) &autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);

		// call init on each subsystem
		prefSystem.PrefsInit(); // has to be first
		lift.LiftInit();
		arm.ArmInit();
		drive.DriveInit();
		shooter.ShooterInit();
		collect.CollectInit();
		autoSystem.AutoInit();
		camera.CameraInit(); // this subsystem needs to be called last



	}

	void AutonomousInit() {

		autoSelected = *((std::string*) chooser->GetSelected());
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			//Custom Auto goes here - not using this
		} else {

			//Default Auto goes here
			autoSystem.AutoAutoInit();
			//camera.CameraAutoInit(); // this subsystem needs to be called last
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			//Custom Auto goes here -- not using this
		} else {
			//Default Auto goes here
			autoSystem.AutoAutoPeriodic();
			//camera.CameraAutoPeriodic(); // this subsystem needs to be called last
		}
	}

	void TeleopInit() {
		//camera.CameraTeleopInit(); // this subsystem needs to be called last
	}

	void TeleopPeriodic() {
		lift.LiftTeleopPeriodic();
		arm.ArmTeleopPeriodic();
		drive.DriveTeleopPeriodic();
		shooter.ShooterTeleopPeriodic();
		collect.CollectTeleopPeriodic();
		//camera.CameraTeleopPeriodic(); // this subsystem needs to be called last
	}

	void DisabledPeriodic() {
		lift.LiftDisable();
		arm.ArmDisable();
		drive.DriveDisable();
		shooter.ShooterDisable();
		collect.CollectDisable();
		autoSystem.AutoDisable();
		//camera.CameraDisable(); // this subsystem needs to be called last
	}

};

START_ROBOT_CLASS(Robot)
