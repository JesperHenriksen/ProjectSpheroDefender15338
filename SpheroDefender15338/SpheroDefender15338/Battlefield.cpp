#include "Battlefield.h"
#include "CameraFeed.h"
#include "Minimap.h"
#include "opencv2\opencv.hpp"

using namespace cv;

Battlefield::Battlefield()
{
}


Battlefield::~Battlefield()
{
}




bool isSpheroOutOfBounds(Mat image, int spheroPosCols, int spheroPosRows){
	// find position of green pixels at min y, max y, min x and max x

	// find position of red pixels at corners

	// make a rect 
	// check if sphero pos is outside the rect
	int greenMin = 30;
	int greenMax = 90;
	int maxRow = 0, minRow = 0;
	int maxCol = 0, minCol = 0;
	cvtColor(image, image, CV_BGR2HSV);

	// this has to happen once
	for (int r = 0; r < image.rows; r++){
		for (int c = 0; c < image.cols; c++){
			if (image.at<Vec3b>(r, c)[0] > greenMin && image.at<Vec3b>(r, c)[0] < greenMax){
				if (r < minRow)
					minRow = r;
				if (r > maxRow)
					maxRow = r;
				if (c < minCol)
					minCol = c;
				if (c > maxCol)
					maxCol = c;

			}
		}
	}
	// this has to happen continues
	if (spheroPosRows < minRow ||
		spheroPosRows > maxRow ||
		spheroPosCols < minCol ||
		spheroPosCols > maxCol){
		//return something that indicates sphero is out of bounds
		return true;
	}
	else{
		return false;
	}
}

void Battlefield::trackSphero(Mat background, CameraFeed webcamSphero, double &xCoordSphero, double &yCoordSphero) {

	Mat frame, foreground;
	Minimap minimap;
	frame = webcamSphero.getImageFromWebcam();
	//frame = webcamSphero.convertRGBtoGS(frame);

	cvtColor(frame, frame, CV_BGR2HSV); // convert from color to HSV
	cvtColor(background, background, CV_BGR2HSV); // convert from color to HSV
	
	addWeighted(background, 0.995, frame, 0.005, 0, background); // update background
	foreground.zeros(frame.rows, frame.cols, frame.type()); // prepare foreground variable
	subtract(frame, background, foreground); // subtract the background
	medianBlur(foreground, foreground, 5); // remove salt pepper noise
	webcamSphero.thresholdImage(foreground, foreground, 0, 0, 0, 0, 0, 0, 240, 255, 255); // make high values completly white
	cvtColor(foreground, foreground, CV_8UC1); // convert from HSV to grayscale	
	minimap.placeSpell(foreground, 200, 256, xCoordSphero, yCoordSphero); // find middle point of pixels within the threshold

}