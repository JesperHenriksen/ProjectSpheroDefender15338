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
	void spheroOutOfBounds();

};