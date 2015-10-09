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

//Blob
struct blob{
	int coords[500][500];
	int id;
} blobs[150];

void Minimap::segmentImage(){
	CameraFeed camfeed;
	Mat inputArrow, outputArrow, imageThreshold;
	inputArrow = camfeed.getImageFromWebcam(0);
	outputArrow = camfeed.getImageFromWebcam(0);
	inputArrow = camfeed.convertRGBtoGS(inputArrow);
	outputArrow = camfeed.convertRGBtoGS(outputArrow);
	camfeed.thresholdImage(inputArrow, outputArrow, 60, 255, 0);
	camfeed.thresholdImage(outputArrow, outputArrow, 0, 60, 255);

	//median
	medianBlur(outputArrow, outputArrow, 5);


	imshow("MiniMap", outputArrow);
	
	return;
}


void Minimap::placeSpell(Mat inputImage, double xCoord, double yCoord){
	int pixelvalue = inputImage.rows*inputImage.cols;
	int atID = 1;
	for (int y = 0; y < inputImage.rows; ++y) {
		for (int x = 0; x < inputImage.cols; ++x) {
			if (inputImage.at<uchar>(y, x) > 60) {
				grassFire(inputImage,x, y, atID);
				atID++;
			}
		}
	}
}

void grassFire(Mat inputImage,int x, int y, int currentID){
	//if (blobs[0].id == currentID)
	if (inputImage.at<uchar>(y, x + 1) > 60){
		grassFire(inputImage, x + 1, y, currentID);
	} 
	if (inputImage.at<uchar>(y + 1, x) > 60){
		grassFire(inputImage, x, y + 1, currentID);
	}
	if (inputImage.at<uchar>(y, x - 1) > 60){
		grassFire(inputImage, x - 1, y, currentID);
	}
	if (inputImage.at<uchar>(y - 1, x) > 60){
		grassFire(inputImage, x, y - 1, currentID);
	}

	return;
}


int getDirection(){
	return 0;
}

