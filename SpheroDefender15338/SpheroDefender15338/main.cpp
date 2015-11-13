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
	CameraFeed webcamOne(0);

	//Mat angleBackground = webcamOne.getImageFromWebcam();
	Mat raw, blob, wizardBackground = webcamOne.getImageFromWebcam();

    Mat foreground;
	Minimap minimap;
	UserInterface userInterface;
	double x = 0.0, y = 0.0;

	userInterface.getStartPoint(wizardBackground, x, y);
	cout << x << ", " << y;

	waitKey(0);

	
	//for (;;){
	//	//arrow position variables
	//	double x = 0, y = 0;
	//	double minimapXCoord = 0, minimapYCoord = 0;
	//	Mat frame, gs;
	//	// get coordinates for arrow
	//	frame = webcamOne.getImageFromWebcam();
	//	frame = webcamOne.convertRGBtoGS(frame);
	//	frame.copyTo(gs);
	//	standardWebcam.thresholdImage(frame,frame,100,255,0,0,100,255);
	//	//minimap.placeSpell(frame, 50,255,minimapXCoord,minimapYCoord);

	//	//angle of arrow variables
	//	double angle = 0;
	//	Mat angleInput, thresholded, angleGrayscale;
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
	//	//hand tracking variables
	//	Mat handInput, handColorThreshold, handGscale, handThreshold;
	//	//hand thresholding
	//	handInput = standardWebcam.getImageFromWebcam();
	//	handInput *= 2;
	//	handInput.copyTo(handColorThreshold);
	//	webcamOne.thresholdImageColor(handInput, handColorThreshold, 100, 255, 0, 140, 200, 255, 100, 255, 0);
	//	webcamOne.thresholdImageColor(handColorThreshold, handColorThreshold, 0, 100, 0, 0, 140, 0, 0, 100, 0);



	//	//end of code
	//	if (waitKey(30) >= 0)
	//		break;
	//}
	//waitKey(0);
	
	//wizardBackground = webcamOne.convertRGBtoGS(wizardBackground);

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
	//}


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
	
	return 0;
}
