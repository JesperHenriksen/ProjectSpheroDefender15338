#include "SpheroCoordinate.h"
#include "CameraFeed.h"
#include "opencv2/opencv.hpp"
#include "BackgroundSubtraction.h"

using namespace cv;
using namespace std;


SpheroCoordinate::SpheroCoordinate(){}
SpheroCoordinate::SpheroCoordinate(int xCoord, int yCoord)
{
	setXCoord(xCoord);
	setYCoord(yCoord);
}


SpheroCoordinate::~SpheroCoordinate()
{
}

void SpheroCoordinate::setXCoord(int xCoord){
	this->xCoord = xCoord;
}

void SpheroCoordinate::setYCoord(int yCoord){
	this->yCoord = yCoord;
}

int SpheroCoordinate::getXCoord(){
	return this->xCoord;
}

int SpheroCoordinate::getYCoord(){
	return this->yCoord;
}

void SpheroCoordinate::startSpheroTracking(CameraFeed webcam){
    Mat image, background, newImage, fina;
    CameraFeed webcamImage(0);

}
