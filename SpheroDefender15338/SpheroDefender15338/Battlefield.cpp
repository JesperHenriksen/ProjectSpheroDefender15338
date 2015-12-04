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

void Battlefield::trackSphero(CameraFeed webcamSphero, double &xCoordSphero, double &yCoordSphero) {

	Mat frame;
	Minimap minimap;
	frame = webcamSphero.getImageFromWebcam();
	//frame = webcamSphero.convertRGBtoGS(frame);

	cvtColor(frame, frame, CV_BGR2GRAY); // convert from color to HSV
	medianBlur(frame, frame, 5); // remove salt pepper noise
	webcamSphero.thresholdImage(frame, frame, 0, 180, 0, 180, 255, 255); // make high values completly white
	imshow("sphero", frame);
	minimap.placeSpell(frame, 254, 256, xCoordSphero, yCoordSphero); // find middle point of pixels within the threshold

}