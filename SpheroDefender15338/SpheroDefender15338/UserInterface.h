#pragma once
#include "opencv2\opencv.hpp"
using namespace cv;
class UserInterface
{
public:
	UserInterface();
	~UserInterface();
	Mat getMenu();
	Mat getBoomerang();
	Mat getSentry();
	Mat getStone();
	Mat getIcePatch();
	Mat getWall();
	void interfaceImages();
	void rotation(Mat input, int degrees, int xOffset, int yOffset);
	void getStartPoint(Mat input, double &startX, double &startY);
	void interfaceLayers();
    void addLayer(Mat input1, Mat input2, Mat output);
	void boomerangSpell(double xCoord, double yCoord, int angle);
	void icePatchSpell(double xCoord, double yCoord, int angle);
	void stoneSpell(Mat input, double xCoord, double yCoord, int angle);
	void sentrySpell(double xCoord, double yCoord, int angle);
	void wallSpell(double xCoord, double yCoord, int angle);
};

