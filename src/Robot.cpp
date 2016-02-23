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
	SendableChooser *chooserObstacle;
	SendableChooser *chooserPosition;
	const std::string autoObstacleMoat = "Moat";
	const std::string autoObstacleRoughTerrain = "Rough Terrain";
	const std::string autoObstacleRamparts = "Ramparts";
	const std::string autoObstacleSeesaw = "Seesaw";
	const std::string autoObstacleDrawbridge = "Drawbridge";
	const std::string autoObstaclePortcullis = "Portcullis";
	const std::string autoObstacleSallyPort = "Sally Port";
	const std::string autoObstacleRockWall = "Rock Wall";

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
		chooserObstacle = new SendableChooser();
		chooserObstacle->AddObject(autoObstacleMoat, (void*) &autoObstacleMoat);
		chooserObstacle->AddObject(autoObstacleRoughTerrain,
				(void*) &autoObstacleRoughTerrain);
		chooserObstacle->AddObject(autoObstacleRamparts,
				(void*) &autoObstacleRamparts);
		chooserObstacle->AddObject(autoObstacleSeesaw,
				(void*) &autoObstacleSeesaw);
		chooserObstacle->AddObject(autoObstacleDrawbridge,
				(void*) &autoObstacleDrawbridge);
		chooserObstacle->AddObject(autoObstaclePortcullis,
				(void*) &autoObstaclePortcullis);
		chooserObstacle->AddObject(autoObstacleSallyPort,
				(void*) &autoObstacleSallyPort);
		chooserObstacle->AddObject(autoObstacleRockWall,
				(void*) &autoObstacleRockWall);
		SmartDashboard::PutData("Auto Obstacles", chooserObstacle);

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

<<<<<<< HEAD
		autoObstacleSelected = *((std::string*) chooserObstacle->GetSelected());
=======
		autoSelected = *((std::string*) chooser->GetSelected());
		std::cout << "Auto selected: " << autoSelected << std::endl;
>>>>>>> refs/remotes/origin/master

		// autosselected holds the obstacle option selected as a string

		autoSystem.AutoAutoInit(autoObstacleSelected);
		camera.CameraAutoInit(); // this subsystem needs to be called last

<<<<<<< HEAD
=======
			//Default Auto goes here
			autoSystem.AutoAutoInit();
			//camera.CameraAutoInit(); // this subsystem needs to be called last
		}
>>>>>>> refs/remotes/origin/master
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			//Custom Auto goes here -- not using this
		} else {
			//Default Auto goes here
<<<<<<< HEAD
			autoSystem.AutoAutoPeriodic(obstacle, position);

			camera.CameraAutoPeriodic(); // this subsystem needs to be called last
=======
			autoSystem.AutoAutoPeriodic();
			//camera.CameraAutoPeriodic(); // this subsystem needs to be called last
>>>>>>> refs/remotes/origin/master
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
