#include "opencv2\opencv.hpp"
#include "Minimap.h"
#include "CameraFeed.h"
#include <thread>
#include "UserInterface.h"
#include <list>
#include "Pipeserver.h"
#include <time.h>

using namespace cv;
using namespace std;

int main(int, char)
{
	int score;
	clock_t timer;
	timer = clock();
	double time = timer / CLOCKS_PER_SEC;
	
	//webcam variables
	CameraFeed wizardWebcam(0); 
	CameraFeed minimapWebcam(1);

	Mat raw, blob, wizardBackground = wizardWebcam.getImageFromWebcam();
    Mat foreground;
	//arrow variables
	Mat arrowInput, arrowThreshold, arrowGrayscale;
	Minimap minimap;
	double x = 0.0, y = 0.0;
	double minimapXCoord = 0, minimapYCoord = 0;
	//angle
	double angle = 0;
	Mat angleInput, thresholded, angleGrayscale;

	//hand tracking variables
	Mat handInput, handColorThreshold, handGscale, handThreshold;
	
	int kernelSize = 11;
	Mat kernel;
	Mat sat, hue, intensity;

	for (;;){

		//// get coordinates for arrow
		//arrowInput = minimapWebcam.getImageFromWebcam();
		//arrowInput.copyTo(arrowThreshold);
		//arrowInput.copyTo(arrowGrayscale);
		//arrowGrayscale = minimapWebcam.convertRGBtoGS(arrowInput);
		//imshow("grayscale", arrowGrayscale);
		//wizardWebcam.thresholdImage(arrowGrayscale, arrowThreshold, 100, 255, 0, 0, 100, 255);
		////minimap.placeSpell(arrowThreshold, 50,255,minimapXCoord,minimapYCoord);
		//imshow("input arrow image", arrowInput);
		//imshow("threshold arrow", arrowThreshold);

		//get the angle of arrow
		//angleInput = minimapWebcam.getImageFromWebcam();
		//angleInput *= 1.5;
		//medianBlur(angleInput, angleInput, 5);
		//minimapWebcam.thresholdImageColor(angleInput, angleInput, 80, 255, 255, 100, 255, 255, 100, 255, 255);
		//minimapWebcam.thresholdImageColor(angleInput, angleInput, 0, 80, 0, 0, 100, 0, 0, 100, 0);
		//angleGrayscale = minimapWebcam.convertRGBtoGS(angleInput);
		//angleGrayscale = angleGrayscale * 1.5;
		//medianBlur(angleGrayscale, angleGrayscale, 7);
		//angleGrayscale *= 2;
		//angleGrayscale.copyTo(thresholded);
		//minimapWebcam.thresholdImage(thresholded, thresholded, 150, 255, 255, 60, 150, 100, 0, 60, 0);
		//angle = minimap.getAngleOfArrow(thresholded, 0, 100);
		//cout << angle << " " << "\n";
		//imshow("threshold", thresholded);
		//imshow("raw", angleInput);
		
		//threshold hand
		handInput = wizardWebcam.getImageFromWebcam();
		//blur(handInput, handInput, Size(kernelSize, kernelSize));
		cvtColor(handInput, sat, COLOR_BGR2HSV);
		sat.copyTo(handColorThreshold);
		minimapWebcam.thresholdHand(sat, handColorThreshold, 30, 90, 255);
		cvtColor(handColorThreshold, handColorThreshold, CV_BGR2GRAY);
		medianBlur(handColorThreshold, handColorThreshold, 9);
		kernel.ones(kernelSize, kernelSize, CV_8UC1);
		//opening
		erode(handColorThreshold, handColorThreshold, kernel);
		medianBlur(handColorThreshold, handColorThreshold, 9);
		dilate(handColorThreshold, handColorThreshold, kernel);
		//closing
		dilate(handColorThreshold, handColorThreshold, kernel);
		erode(handColorThreshold, handColorThreshold, kernel);
		Mat grassfire;
		grassfire = Mat::zeros(handColorThreshold.rows, handColorThreshold.cols, handColorThreshold.type());
		minimapWebcam.grassFire(handColorThreshold, grassfire);
		Mat fixedGrassfire;
		handColorThreshold.copyTo(fixedGrassfire);
		minimapWebcam.thresholdGrassfireID(grassfire,fixedGrassfire);

		imshow("threshold", handColorThreshold);
		//imshow("grassfire", grassfire);
		imshow("fixed grassfire", fixedGrassfire);
		imshow("input", handInput);

		//recognize hand
		int handsign = 0;
		handsign = wizardWebcam.chooseHandsign(handColorThreshold);

		//end of code
		if (waitKey(30) >= 0)
			break;
	}
	waitKey(0);
	return 0;
}