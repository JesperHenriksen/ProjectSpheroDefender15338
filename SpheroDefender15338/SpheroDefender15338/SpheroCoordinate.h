#include "opencv2\opencv.hpp"
#include "CameraFeed.h"
#pragma once
class SpheroCoordinate
{
public:
	SpheroCoordinate();
	~SpheroCoordinate();
	
	/*!
		Returns the Y coordinate value.
	!*/
	int getYCoord();
	/*!
		Sets the Y coordinate value.
	!*/
	void setYCoord(int yCoord);
	/*!
		Returns the X coordinate value.
	!*/
	int getXCoord();
	/*!
		Sets the X coordinate value.
	!*/
	void setXCoord(int xCoord);
	/*!
		Start tracking of sphero on the Battlefield. This starts a thread that continues sends Sphero coordinates.
	!*/
    void trackSphero(Mat background, CameraFeed webcamSphero);

private:
    double xCoordSphero = 0.0; //X coordinate of the Sphero.
    double yCoordSphero = 0.0; //Y coordinate of the Sphero.
};

