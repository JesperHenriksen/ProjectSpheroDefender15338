#include "SpheroCoordinate.h"
#include "CameraFeed.h"
#include "opencv2/opencv.hpp"

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

void SpheroCoordinate::startSpheroTracking(){
    char c = cin.get();
    Mat image, background, newImage, fina;
    CameraFeed webcamImage(0);
    CameraFeed imageThreshold();

    for (;;) {
        background = webcamImage.getImageFromWebcam();
        cvtColor(background, background, CV_RGB2GRAY);
        //imshow("Webcam", background);

        image = webcamImage.getImageFromWebcam();
        cvtColor(image, image, CV_RGB2GRAY);
        //imshow("New Image", image);

        newImage = abs(background - image);
        webcamImage.thresholdImage(newImage, newImage, 20, 25, 20);
        medianBlur(newImage, fina, 3);
        //imshow("New Image", newImage);
        imshow("fina", fina);
        if (waitKey(30) >= 0)
            break;
    }
}
