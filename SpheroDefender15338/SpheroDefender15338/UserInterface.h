#pragma once
#include "opencv2\opencv.hpp"
using namespace cv;
class UserInterface
{
public:
	UserInterface();
	~UserInterface();
	void interfaceImages();
	void rotation(Mat input, int degrees, int xOffset, int yOffset);
	void interfaceLayers();
	void boomerangSpell(double xCoord, double yCoord, int angle);
	//Mat icePatchSpell();
	//Mat stoneSpell();
	//Mat sentrySpell();
	void wallSpell(double xCoord, double yCoord, int angle);
};

