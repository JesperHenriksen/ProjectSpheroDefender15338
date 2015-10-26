#pragma once
#include "CameraFeed.h"
class Minimap
{
public:
	Minimap();
	~Minimap();
	Mat segmentImage(CameraFeed camfeed);
	void placeSpell(Mat inputFrame);
	void thresholdImageArrow(Mat inputImage, Mat outputImage, int minThresholdRed, int maxThresholdRed, int newValueRed,
		int minThresholdGreen, int maxThresholdGreen,
		int minThresholdBlue, int maxThresholdBlue);
	/**
	@brief Checks the number of pixels in the input image to see whether or not the current pixel has been "burned". If it hasn't - it burns the pixel. 
	*/
	void grassFire(Mat inputImage, int x, int y, int currentID);
	int getDirection();
	double xCoord;
	double yCoord;
};



