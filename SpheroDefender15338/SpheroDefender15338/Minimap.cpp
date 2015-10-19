#include "Minimap.h"
#include "opencv2\opencv.hpp"
#include "CameraFeed.h"

using namespace std;
using namespace cv;

Minimap::Minimap()
{
}

Minimap::~Minimap()
{
}

Mat Minimap::segmentImage(CameraFeed camfeed){ 
	Mat inputArrow, outputArrow, imageThreshold;
	inputArrow = camfeed.getImageFromWebcam();
	outputArrow = camfeed.getImageFromWebcam();
	inputArrow = camfeed.convertRGBtoGS(inputArrow);
	outputArrow = camfeed.convertRGBtoGS(outputArrow);
	camfeed.thresholdImage(inputArrow, outputArrow, 60, 255, 0);
	camfeed.thresholdImage(outputArrow, outputArrow, 0, 60, 255);
	medianBlur(outputArrow, outputArrow, 5);
	imshow("MiniMap", outputArrow);
	return outputArrow;
}

void Minimap::placeSpell(Mat inputImage, double xCoord, double yCoord){
	int xMin = 0, xMax = 0, yMin = 0, yMax = 0;
	for (int x = 0; x < inputImage.cols; x++) {
		for (int y = 0; y < inputImage.rows; y++) { //runs through the pixels
			if (inputImage.at<uchar>(y, x) > 60) { //if there is informations in the input pixel
				if (x < xMin){
					xMin = x;
				}
				else if (x > xMax){
					xMax = x;
				}
				if (y < yMin){
					yMin = y;
				}
				else if (y > yMax){
					yMax = y;
				}
			}
		}
	}

	xCoord = (xMax - xMin)/2;
	yCoord = (yMax - yMin)/2;
}

int getDirection(){
	return 0;
}

