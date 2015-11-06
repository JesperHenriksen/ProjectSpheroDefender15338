#include "SpheroCoordinate.h"
#include "CameraFeed.h"
#include "Minimap.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

CameraFeed webcamSphero(2);

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

void SpheroCoordinate::trackSphero() {
    Mat backgroundSphero = webcamSphero.getImageFromWebcam();
    backgroundSphero = webcamSphero.convertRGBtoGS(backgroundSphero);
    Mat frame, foreground;
    Minimap minimap;
    double xCoord, yCoord;


    for (;;) {
        frame = webcamSphero.getImageFromWebcam();
        frame = webcamSphero.convertRGBtoGS(frame);
        addWeighted(backgroundSphero, 0.995, frame, 0.005, 0, backgroundSphero);
        foreground.zeros(frame.rows, frame.cols, frame.type());
        subtract(frame, backgroundSphero, foreground);
        //medianBlur(foreground,foreground, 5);
        threshold(foreground, foreground, 0, 255, THRESH_BINARY);
        //imshow("sphero", foreground);
        minimap.placeSpell(foreground, 200, 255, xCoord, yCoord);
        setXCoord(xCoord);
        setYCoord(yCoord);
    }
}