#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
#include "Camera.h"

void Camera::SendCameraFeed() {
	//while(IsEnabled()==true)
	//{
	camera->GetImage(frame.GetImaqImage());
	CameraServer::GetInstance()->SetImage(frame.GetImaqImage());
	//}
}

void Camera::PutPixels() {
	RGBImage pixelFrame;
	MonoImage greenPixels;
	//PixelValue *pixel;
	//Point current;
	//Rect rectangle;
	//int *columns;
	//int *rows;
	camera->GetImage(pixelFrame.GetImaqImage());
	//greenPixels = new MonoImage(pixelFrame.GetGreenPlane());
	ImageInfo info;
	imaqGetImageInfo(greenPixels.GetImaqImage(), &info);
	//table = NetworkTable::GetTable("pixelTable");
	//int area = info.yRes * info.xRes;
	//char *pixels[area];
	//int currentPixel = 0;
	table->PutNumber("X-Axis", info.xRes);
	table->PutNumber("Y-Axis", info.yRes);
	for (int y = 0; y < info.yRes; y++) {
		for (int x = 0; x < info.xRes; x++) {
			char *current = (char*) info.imageStart + y * info.pixelsPerLine
					+ x;
			int pixel = (int) current;
			table->PutNumber(x + ", " + y, pixel);
			std::cout << "Pixel Written to Table";
			//pixels[currentPixel] = (char*) info.imageStart + y * info.pixelsPerLine + x;
			//currentPixel++;
		}
	}
	/*columns = new int(pixelFrame.GetWidth());
	 rows = new int(pixelFrame.GetHeight());
	 int area = pixelFrame.GetWidth() * pixelFrame.GetHeight();
	 double pixelArray[area];
	 pixelArray = imaqImageToArray(pixelFrame.GetImaqImage(), rectangle, columns, rows);
	 table = NetworkTable::GetTable("pixelTable");
	 for(int x = 0; x<=area; x++){
	 table->PutNumber("Image Pixel " + x, pixelArray[x]);
	 std::cout << "Pixel Written to Table";
	 }*/
	/*for(int x = 1; x<=pixelFrame.GetWidth; x=x*1){
	 for(int y; y<=pixelFrame.GetHeight; y=y*1){
	 current = new Point(x,y);
	 frcGetPixelValue(pixelFrame.GetImaqImage, current.Point_struct, pixel->PixelValue_union);
	 }
	 }*/
}

void Camera::CameraInit() {
	prefs = Preferences::GetInstance();
	brightness = prefs->GetInt("brightness", 40);
	cameraSendButton = prefs->GetInt("cameraSendButton", 5);
	auxJoystickNumber = prefs->GetInt("auxJoystickNumber", 1);

	camera = new USBCamera("cam0", true);
	stick = new Joystick(auxJoystickNumber);
	autoTargetStart = false;
	lw = LiveWindow::GetInstance();


}

void Camera::CameraDisable() {

}

void Camera::CameraAutoInit() {
	camera->OpenCamera();
	camera->SetExposureHoldCurrent();
	camera->SetExposureManual(0);
	camera->SetBrightness(brightness);
	camera->SetFPS(30);
	camera->UpdateSettings();
	camera->StartCapture();
}

void Camera::CameraAutoPeriodic() {
	SendCameraFeed();
	/*while(IsEnabled()==true)
	 {
	 camera.GetImage(frame.GetImaqImage());
	 CameraServer::GetInstance()->SetImage(frame.GetImaqImage());
	 }*/
}

void Camera::CameraTeleopInit() {
	table->SetServerMode();
	table->SetTeam(1622);
	table = NetworkTable::GetTable("pixelTable");
	camera->OpenCamera();
	camera->SetExposureHoldCurrent();
	camera->SetExposureManual(0);
	camera->SetBrightness(brightness);
	camera->SetFPS(30);
	camera->UpdateSettings();
	camera->StartCapture();
	//SendCameraFeed(); //TODO move to Periodic
}

void Camera::CameraTeleopPeriodic() {
	bool send = stick->GetRawButton(cameraSendButton);
	if (send) {
		std::cout << "Button Pressed!";
		table->PutNumber("X-Axis", 3);
		table->PutNumber("Y-Axis", 3);
		table->PutNumber("1, 1", 35);
		table->PutNumber("1, 2", 64);
		table->PutNumber("1, 3", 53);
		table->PutNumber("2, 1", 953);
		table->PutNumber("2, 2", 432);
		table->PutNumber("2, 3", 4);
		table->PutNumber("3, 1", 21);
		table->PutNumber("3, 2", 98);
		table->PutNumber("3, 3", -35);
	}
	SendCameraFeed();
}

/*void TestPeriodic()
 {
 lw->Run();
 }*/
