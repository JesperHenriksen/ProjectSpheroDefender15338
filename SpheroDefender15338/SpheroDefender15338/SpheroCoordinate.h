#include "opencv2\opencv.hpp"
#include "CameraFeed.h"
#pragma once
class SpheroCoordinate
{
public:
	SpheroCoordinate();
	SpheroCoordinate(int xCoord,int yCoord);
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
	void startSpheroTracking(CameraFeed webcam);

private:
	int xCoord; //X coordinate of the Sphero.
	int yCoord; //Y coordinate of the Sphero.
};

