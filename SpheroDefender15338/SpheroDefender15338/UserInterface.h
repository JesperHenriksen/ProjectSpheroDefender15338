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
	Mat getWall();
	void interfaceImages();
	void rotation(Mat input, int degrees, int xOffset, int yOffset);
	void getStartEndPoint(Mat input, double &startX, double &startY, double &endX, double &endY);
	void vectorDirection(Mat input, double startX, double startY, double endX, double endY);
	void interfaceLayers();
    void addLayer(Mat input1, Mat input2, Mat output);
	void boomerangSpell(Mat boomerang, double startX, double startY, double arrowX, double arrowY, int angle);
	void stoneSpell(Mat input, int angle, double startX, double startY, double endX, double endY);
	void sentrySpell(Mat input, double xCoord, double yCoord, int angle);
	void wallSpell(Mat wall, double xCoord, double yCoord, int angle);
};

