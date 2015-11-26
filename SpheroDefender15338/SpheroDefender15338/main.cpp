#include "opencv2\opencv.hpp"
#include "Sphero.h"
#include "Minimap.h"
#include "CameraFeed.h"
#include <thread>
#include "UserInterface.h"
#include <list>

using namespace cv;
using namespace std;

int main(int, char)
{
	//webcam variables
	CameraFeed wizardWebcam(0); 
	CameraFeed minimapWebcam(1);

	//Mat angleBackground = minimapWebcam.getImageFromWebcam();
	Mat raw, blob, wizardBackground = wizardWebcam.getImageFromWebcam();

    Mat foreground;
	
	UserInterface userInterface;

	//arrow variables
	Mat frame, gs;
	Minimap minimap;
	double x = 0.0, y = 0.0;
	double xEnd = 0.0, yEnd = 0.0;
	double minimapXCoord = 0, minimapYCoord = 0;
	//angle
	double angle = 0;
	Mat angleInput, thresholded, angleGrayscale;

	//hand tracking variables
	Mat handInput, handColorThreshold, handGscale, handThreshold;
	Mat grassfire;

	userInterface.getStartEndPoint(wizardBackground, x, y, xEnd, yEnd);
	cout << x << ", " << y;
	cout << xEnd << "," << yEnd;
	/*UserInterface userInterface;
	userInterface.interfaceLayers();
	imshow("left menu", userInterface.getMenu());
	*/

	Mat sat, hue, intensity;

	
	for (;;){

	//	// get coordinates for arrow
	//	frame = minimapWebcam.getImageFromWebcam();
	//	frame = minimapWebcam.convertRGBtoGS(frame);
	//	frame.copyTo(gs);
	//	wizardWebcam.thresholdImage(frame,frame,100,255,0,0,100,255);
	//	//minimap.placeSpell(frame, 50,255,minimapXCoord,minimapYCoord);
	

	//	//get the angle of arrow
	//	angleInput = minimapWebcam.getImageFromWebcam();
	//	angleInput *= 1.5;
	//	//imshow("raw", angleInput);
	//	medianBlur(angleInput, angleInput, 5);
	//	minimapWebcam.thresholdImageColor(angleInput, angleInput, 80, 255, 255, 100, 255, 255, 100, 255, 255);
	//	minimapWebcam.thresholdImageColor(angleInput, angleInput, 0, 80, 0, 0, 100, 0, 0, 100, 0);
	//	angleGrayscale = minimapWebcam.convertRGBtoGS(angleInput);
	//	angleGrayscale = angleGrayscale * 1.5;
	//	medianBlur(angleGrayscale, angleGrayscale, 7);
	//	angleGrayscale *= 2;
	//	angleGrayscale.copyTo(thresholded);
	//	minimapWebcam.thresholdImage(thresholded, thresholded, 150, 255, 255, 60, 150, 100, 0, 60, 0);
	//	//imshow("threshold", thresholded);
	//	angle = minimap.getAngleOfArrow(thresholded, 0, 100);
	//	//cout << angle << " " << "\n";
	//
		////threshold hand
		//int kernelSize = 9;
		//handInput = wizardWebcam.getImageFromWebcam();
		//blur(handInput, handInput, Size(kernelSize,kernelSize));
		//cvtColor(handInput, sat, COLOR_BGR2HSV);
		//sat.copyTo(handColorThreshold);
		//minimapWebcam.thresholdHand(sat, handColorThreshold, 30, 90, 255);
		//cvtColor(handColorThreshold, handColorThreshold, CV_BGR2GRAY);
		//medianBlur(handColorThreshold, handColorThreshold, 9);
		//Mat kernel;
		//kernel.ones(kernelSize, kernelSize, CV_8UC1);
		//erode(handColorThreshold,handColorThreshold,kernel);
		//medianBlur(handColorThreshold, handColorThreshold, 9);
		//dilate(handColorThreshold,handColorThreshold,kernel);
		////grassfire = Mat::zeros(handColorThreshold.rows, handColorThreshold.cols, handColorThreshold.type());
		////wizardWebcam.grassFire(handColorThreshold, grassfire);
		////wizardWebcam.grassFire(grassfire, grassfire);
		//imshow("threshold", handColorThreshold);
		//imshow("sat", handInput);
		////imshow("grassfire", grassfire);
		//
		////recognize hand
		//


		//end of code
		if (waitKey(30) >= 0)
			break;
	}
	waitKey(0);
	return 0;
}

//for (;;){
//	Mat erosionKernel = Mat::ones(5,5,CV_8UC1);
//	raw = wizardWebcam.getImageFromWebcam();
//	raw.copyTo(frame);
//	//wizardWebcam.thresholdImageColor(frame,frame,0,0,0,0,0,0,0,255,0);
//	imshow("test", frame);
//	frame.copyTo(gs);
//	frame = wizardWebcam.convertRGBtoGS(frame);
//	imshow("greyscale",gs);
//	wizardWebcam.thresholdImage(frame, frame, 0, 50, 0, 50, 150, 255, 150, 255, 0);
//	erode(frame,frame,erosionKernel);
//	blob = wizardWebcam.grassFire(frame);
//	imshow("fired the Grassfire",blob);
//	imshow("input", raw);
//	if (waitKey(30) >= 0)
//		break;
//}

//for (;;) {
//       frame = minimapWebcam.getImageFromWebcam();
//       frame = minimapWebcam.convertRGBtoGS(frame);
//       addWeighted(wizardBackground, 0.995, frame, 0.005, 0, wizardBackground); 
//       foreground.zeros(frame.rows,frame.cols, frame.type());
//       subtract(frame, wizardBackground, foreground);
//       //medianBlur(image, image, 3);
//       // medianBlur(foreground,foreground, 5);
//	threshold(foreground, foreground,0,255,THRESH_BINARY);
//	//imshow("New Image", newImage);
//	imshow("final", foreground);
//	if (waitKey(30) >= 0)
//		break;