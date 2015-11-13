#include "SpheroCoordinate.h"
#include "CameraFeed.h"
#include "Minimap.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;



SpheroCoordinate::SpheroCoordinate(){}

SpheroCoordinate::~SpheroCoordinate()
{
}

void SpheroCoordinate::setXCoord(int xCoord){
	xCoordSphero = xCoord;
}

void SpheroCoordinate::setYCoord(int yCoord){
	yCoordSphero = yCoord;
}

int SpheroCoordinate::getXCoord(){
	return xCoordSphero;
}

int SpheroCoordinate::getYCoord(){
	return yCoordSphero;
}

void SpheroCoordinate::trackSphero(Mat background, CameraFeed webcamSphero) {

    Mat frame, foreground;
    Minimap minimap;

        frame = webcamSphero.getImageFromWebcam();
        frame = webcamSphero.convertRGBtoGS(frame);
        addWeighted(background, 0.995, frame, 0.005, 0, background);
        foreground.zeros(frame.rows, frame.cols, frame.type());
        subtract(frame, background, foreground);
        medianBlur(foreground,foreground, 5);
        //threshold(foreground, foreground, 0, 255, THRESH_BINARY);
        imshow("background", foreground);
        webcamSphero.thresholdImage(foreground, foreground, 50, 255, 255, 0, 100, 0);
        imshow("sphero", foreground);
        minimap.placeSpell(foreground, 200, 256, xCoordSphero, yCoordSphero);
}