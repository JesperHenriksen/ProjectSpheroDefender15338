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
	CameraFeed standardWebcam(0); 
	CameraFeed webcamOne(1);

	//Mat angleBackground = webcamOne.getImageFromWebcam();
	Mat raw, blob, wizardBackground = webcamOne.getImageFromWebcam();

    Mat foreground;
	
	//UserInterface userInterface;

	//arrow variables
	Mat frame, gs;
	Minimap minimap;
	double x = 0.0, y = 0.0;
	double minimapXCoord = 0, minimapYCoord = 0;
	//angle
	double angle = 0;
	Mat angleInput, thresholded, angleGrayscale;

	//hand tracking variables
	Mat handInput, handColorThreshold, handGscale, handThreshold;

	//userInterface.getStartPoint(wizardBackground, x, y);
	cout << x << ", " << y;
	/*UserInterface userInterface;
	userInterface.interfaceLayers();
	imshow("left menu", userInterface.getMenu());
	*/

	Mat sat, hue, intensity;

	
	for (;;){

	//	// get coordinates for arrow
	//	frame = webcamOne.getImageFromWebcam();
	//	frame = webcamOne.convertRGBtoGS(frame);
	//	frame.copyTo(gs);
	//	standardWebcam.thresholdImage(frame,frame,100,255,0,0,100,255);
	//	//minimap.placeSpell(frame, 50,255,minimapXCoord,minimapYCoord);
	

	//	//get the angle of arrow
	//	angleInput = webcamOne.getImageFromWebcam();
	//	angleInput *= 1.5;
	//	//imshow("raw", angleInput);
	//	medianBlur(angleInput, angleInput, 5);
	//	webcamOne.thresholdImageColor(angleInput, angleInput, 80, 255, 255, 100, 255, 255, 100, 255, 255);
	//	webcamOne.thresholdImageColor(angleInput, angleInput, 0, 80, 0, 0, 100, 0, 0, 100, 0);
	//	angleGrayscale = webcamOne.convertRGBtoGS(angleInput);
	//	angleGrayscale = angleGrayscale * 1.5;
	//	medianBlur(angleGrayscale, angleGrayscale, 7);
	//	angleGrayscale *= 2;
	//	angleGrayscale.copyTo(thresholded);
	//	webcamOne.thresholdImage(thresholded, thresholded, 150, 255, 255, 60, 150, 100, 0, 60, 0);
	//	//imshow("threshold", thresholded);
	//	angle = minimap.getAngleOfArrow(thresholded, 0, 100);
	//	//cout << angle << " " << "\n";
	//
		
		//hand thresholding
		handInput = standardWebcam.getImageFromWebcam();
		//webcamOne.thresholdImageColor(handColorThreshold, handColorThreshold, 0, 0, 0, 0, 0, 0, 0, 256, 0);
		cvtColor(handInput, sat, COLOR_BGR2HSV);
		//split(handColorThreshold,handColorThreshold);
		webcamOne.thresholdHand(sat, sat, 40, 90, 255, 0, 256, 0, 256);
		//cvtColor(handColorThreshold, handColorThreshold, CV_THRESH_BINARY);
		//webcamOne.negateChannel(1, sat);
		//webcamOne.negateChannel(2, sat);
		sat.copyTo(handColorThreshold);
		cvtColor(sat, handColorThreshold, CV_BGR2GRAY);
		//sat *= 5;
		blur(sat, sat, Size(3, 3));
		medianBlur(sat, sat, 5);
		webcamOne.thresholdImage(handColorThreshold, handColorThreshold, 50, 255, 0, 0, 20, 0, 20, 50, 255);
		medianBlur(handColorThreshold, handColorThreshold, 5);
		imshow("no hand color", handInput);
		imshow("threshold", handColorThreshold);
		imshow("sat", sat);
		//imshow("hue", hue);
		//imshow("int", intensity);
		//end of code
		if (waitKey(30) >= 0)
			break;
	}
	waitKey(0);
	return 0;
}

//for (;;){
//	Mat erosionKernel = Mat::ones(5,5,CV_8UC1);
//	raw = standardWebcam.getImageFromWebcam();
//	raw.copyTo(frame);
//	//standardWebcam.thresholdImageColor(frame,frame,0,0,0,0,0,0,0,255,0);
//	imshow("test", frame);
//	frame.copyTo(gs);
//	frame = standardWebcam.convertRGBtoGS(frame);
//	imshow("greyscale",gs);
//	standardWebcam.thresholdImage(frame, frame, 0, 50, 0, 50, 150, 255, 150, 255, 0);
//	erode(frame,frame,erosionKernel);
//	blob = standardWebcam.grassFire(frame);
//	imshow("fired the Grassfire",blob);
//	imshow("input", raw);
//	if (waitKey(30) >= 0)
//		break;
//}

//for (;;) {
//       frame = webcamOne.getImageFromWebcam();
//       frame = webcamOne.convertRGBtoGS(frame);
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