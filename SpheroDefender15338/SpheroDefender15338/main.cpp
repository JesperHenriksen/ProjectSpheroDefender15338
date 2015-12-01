#include "opencv2\opencv.hpp"
#include "Minimap.h"
#include "CameraFeed.h"
#include <thread>
#include "UserInterface.h"
#include <list>

using namespace cv;
using namespace std;

int main(int, char)
{
	int score;
	clock_t timer;
	static struct leaderboard {
		int score = 0;
		char name = ' ';
		char playerType = ' ';
	};

	//webcam variables
	CameraFeed wizardWebcam(0); 
	CameraFeed minimapWebcam(1);

	//Mat angleBackground = minimapWebcam.getImageFromWebcam();
	Mat raw, blob, wizardBackground = wizardWebcam.getImageFromWebcam();

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
	
	
	vector<vector<Point> > contours;
	vector<Vec4i> hierachy;
	int kernelSize = 11;
	Mat handContours, kernel;;
	//userInterface.getStartPoint(wizardBackground, x, y);
	//cout << x << ", " << y;
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
		
		//threshold hand
		handInput = wizardWebcam.getImageFromWebcam();
		imshow("input", handInput);
		blur(handInput, handInput, Size(kernelSize, kernelSize));
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
		grassfire *= 25;
		imshow("grassfire", grassfire);
		imshow("threshold", handColorThreshold);
	
		////recognize hand
		//handColorThreshold.copyTo(handContours);
		//findContours(handContours, contours, hierachy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
		//vector <vector<Point>> hull(contours.size());
		//vector<vector<Vec4i>> convexDef(contours.size());


		//for (int i = 0; i < contours.size(); i++) {
		//	convexHull(Mat(contours[i]), hull[i], false);
		//	//if (contours.size() > 3)
		//		//convexityDefects(Mat(contours[i]), hull[i], convexDef[i]);
		//}
		//Mat contoursMat = Mat::zeros(handColorThreshold.size(), CV_8UC3);
		//RNG rng(12345);
		//for (int i = 0; i < contours.size(); i++){
		//	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//	drawContours(contoursMat, contours, i, color, 1, 8, hierachy, 0, Point());
		//	drawContours(contoursMat, hull, i, color, 1, 8, hierachy, 0, Point());

		//}
		//imshow("contours", contoursMat);

		int handsign = 0;
		handsign = wizardWebcam.chooseHandsign(handColorThreshold);


		//end of code
		if (waitKey(30) >= 0)
			break;
	}
	waitKey(0);
	return 0;
}