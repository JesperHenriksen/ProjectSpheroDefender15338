#pragma once
#include "CameraFeed.h"
class Minimap
{
public:
	Minimap();
	~Minimap();
	Mat segmentImage(CameraFeed camfeed);
	/**
	@brief
		Returns the angle value in degrees of the Arrow on the Minimap
	@param inputImage
		The input Mat image
	@param thresholdMin
		The pixel value of the back of the arrow.
	@param thresholdMax
		The pixel value of the front of the arrow.
	@return
		Returns the value of the angle in a double variable
	*/
	double getAngleOfArrow(Mat inputImage, int thresholdMin, int thresholdMax);
	void placeSpell(Mat inputFrame, int thresholdMin, int thresholdMax, double &xCoord, double &yCoord);
	void thresholdImageArrow(Mat inputImage, Mat outputImage, int minThresholdRed, int maxThresholdRed, int newValueRed,
		int minThresholdGreen, int maxThresholdGreen,
		int minThresholdBlue, int maxThresholdBlue);
	/**
	@brief 
		Checks the number of pixels in the input image to see whether or not the current pixel has been "burned". If it hasn't - it burns the pixel. 
	*/
	void grassFire(Mat inputImage, int x, int y, int currentID);
	int getDirection();
	double xCoord;
	double yCoord;
};



