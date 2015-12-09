#pragma once
#include "CameraFeed.h"
#include "opencv2\opencv.hpp"

using namespace cv;

class Battlefield
{
public:
	Battlefield();
	~Battlefield();
	void trackSphero(CameraFeed webcamSphero, double &xCoordSphero, double &yCoordSphero);
	/*!
	checks if shero is out of bounds
	!*/
	bool isSpheroOutOfBounds(Mat image, double spheroPosCols, double spheroPosRows);
	void throwSpell(Mat inputImage, double minimapXCoord, double minimapYCoord, int handsign, double scalar);
	void removeObstacle(Mat inputImage, Mat resetImage, double spheroX, double spheroY, double scalar);
};