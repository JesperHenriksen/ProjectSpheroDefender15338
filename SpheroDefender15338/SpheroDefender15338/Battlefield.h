#pragma once
#include "CameraFeed.h"
#include "opencv2\opencv.hpp"

using namespace cv;

class Battlefield
{
public:
	Battlefield();
	~Battlefield();
	bool isSpheroOutOfBounds(Mat image, int spheroPosCols, int spheroPosRows);
	void Battlefield::trackSphero(Mat background, CameraFeed webcamSphero, double &xCoordSphero, double &yCoordSphero);
	/*!
	checks if shero is out of bounds
	!*/
	void spheroOutOfBounds();

};