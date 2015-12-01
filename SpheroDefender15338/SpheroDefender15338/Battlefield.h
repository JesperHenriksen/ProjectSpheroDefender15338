#pragma once
#include "CameraFeed.h"
#include "opencv2\opencv.hpp"

using namespace cv;

class Battlefield
{
public:
	Battlefield();
	~Battlefield();
	void Battlefield::trackSphero(Mat background, CameraFeed webcamSphero, double &xCoordSphero, double &yCoordSphero);
	/*!
	checks if shero is out of bounds
	!*/
	void spheroOutOfBounds();
	/*!
	Projects battlefield
	!*/
	void projectBattlefield();
	/*!
	Detects if sphero gets hit
	!*/
	void doesSheroGetHit();
};