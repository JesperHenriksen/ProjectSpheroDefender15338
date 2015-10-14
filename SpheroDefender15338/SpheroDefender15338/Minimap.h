#pragma once
#include "CameraFeed.h"
class Minimap
{
public:
	Minimap();
	~Minimap();
	Mat segmentImage(CameraFeed camfeed);
	void placeSpell(Mat inputFrame,double xCoord, double yCoord);
	/**
	@brief Checks the number of pixels in the input image to see whether or not the current pixel has been "burned". If it hasn't - it burns the pixel. 
	*/
	void grassFire(Mat inputImage, int x, int y, int currentID);
	int getDirection();
	double xCoord;
	double yCoord;
};



