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
	frame = webcamSphero.convertRGBtoGS(frame);
	addWeighted(background, 0.995, frame, 0.005, 0, background);
	foreground.zeros(frame.rows, frame.cols, frame.type());
	subtract(frame, background, foreground);
	medianBlur(foreground, foreground, 5);
	webcamSphero.thresholdImage(foreground, foreground, 50, 255, 255, 0, 100, 0);
	minimap.placeSpell(foreground, 200, 256, xCoordSphero, yCoordSphero);
}