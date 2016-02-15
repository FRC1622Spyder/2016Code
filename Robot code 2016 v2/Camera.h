/*
 * Camera.h
 *
 *  Created on: Feb 10, 2016
 *      Author: Admin
 */

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

class Camera {
public:
	LiveWindow *lw;
	Joystick *stick;
	bool autoTargetStart;
	int autoLoopCounter;
	USBCamera *camera;
	RGBImage frame;
	MonoImage *plane;
	std::shared_ptr<NetworkTable> table;

	Preferences *prefs;

	int brightness;
	int auxJoystickNumber;
	int cameraSendButton;

	void CameraInit();
	void CameraAutoInit();
	void CameraAutoPeriodic();
	void CameraTeleopInit();
	void CameraTeleopPeriodic();
	void SendCameraFeed();
	void PutPixels();
	void CameraDisable();
};

#endif /* SRC_CAMERA_H_ */
