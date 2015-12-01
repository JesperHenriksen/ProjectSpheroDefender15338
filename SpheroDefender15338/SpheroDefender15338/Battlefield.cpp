#include "Battlefield.h"
#include "CameraFeed.h"
#include "Minimap.h"
#include "opencv2\opencv.hpp"

using namespace cv;

Battlefield::Battlefield()
{
}


Battlefield::~Battlefield()
{
}

void projectBattlefield(){

}

void doesSpheroGetHit(){

}

void spheroOutOfBounds(){

}

void Battlefield::trackSphero(Mat background, CameraFeed webcamSphero, double &xCoordSphero, double &yCoordSphero) {

	Mat frame, foreground;
	Minimap minimap;
	frame = webcamSphero.getImageFromWebcam();
	//frame = webcamSphero.convertRGBtoGS(frame);

	cvtColor(frame, frame, CV_BGR2HSV); // convert from color to HSV
	cvtColor(background, background, CV_BGR2HSV); // convert from color to HSV
	
	addWeighted(background, 0.995, frame, 0.005, 0, background); // update background
	foreground.zeros(frame.rows, frame.cols, frame.type()); // prepare foreground variable
	subtract(frame, background, foreground); // subtract the background
	medianBlur(foreground, foreground, 5); // remove salt pepper noise
	webcamSphero.thresholdImage(foreground, foreground, 0, 0, 0, 0, 0, 0, 240, 255, 255); // make high values completly white
	cvtColor(foreground, foreground, CV_8UC1); // convert from HSV to grayscale	
	minimap.placeSpell(foreground, 200, 256, xCoordSphero, yCoordSphero); // find middle point of pixels within the threshold

}