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

double Minimap::getAngleOfArrow(Mat inputImage, int thresholdMin, int thresholdMax){
	double result = 0;
	int recCollectiveX = 0, recCollectiveY = 0, recTotalPixels = 0;
	int triCollectiveX = 0, triCollectiveY = 0, triTotalPixels = 0;
	double recCenterX = 0, recCenterY = 0;
	double triCenterX = 0, triCenterY = 0;
	for (int y = 0; y < inputImage.rows; y++){
		for (int x = 0; x < inputImage.cols; x++){
			if (inputImage.at<uchar>(y, x) >(thresholdMin - 5) && inputImage.at<uchar>(y, x) < (thresholdMin + 5)){
				recCollectiveX += x;
				recCollectiveY += y;
				recTotalPixels++;
			}
			if (inputImage.at<uchar>(y, x) > (thresholdMax - 5) && inputImage.at<uchar>(y, x) < (thresholdMax + 5)){
				triCollectiveX += x;
				triCollectiveY += y;
				triTotalPixels++;
			}
		}
	}
	if (recTotalPixels != 0){
		recCenterX = recCollectiveX / recTotalPixels;
		recCenterY = recCollectiveY / recTotalPixels;
	}
	if (triTotalPixels != 0){
		triCenterX = triCollectiveX / triTotalPixels;
		triCenterY = triCollectiveY / triTotalPixels;
	}
	result = atan2(triCenterY - recCenterY, triCenterX - recCenterX) * 180 / 3.14;
 	return result;
}

void Minimap::placeSpell(Mat inputImage, int thresholdMin, int thresholdMax, double& xCoord, double& yCoord){

	int collectiveX = 0, collectiveY = 0;
	int totalPixels = 0;
	for (int x = 0; x < inputImage.cols; x++) {
		for (int y = 0; y < inputImage.rows; y++) { //runs through the pixels
			if (inputImage.at<uchar>(y, x) > thresholdMin && inputImage.at<uchar>(y, x) < thresholdMax) { //if there is informations in the input pixel
				collectiveX += x;
				collectiveY += y;
				totalPixels++;
			}
		}
	}
	xCoord = collectiveX / totalPixels;
	yCoord = collectiveY / totalPixels;
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


void Minimap::thresholdImageArrow(Mat inputImage, Mat outputImage, int minThresholdRed, int maxThresholdRed, int newValueRed,
	int minThresholdGreen, int maxThresholdGreen,
	int minThresholdBlue, int maxThresholdBlue){
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<Vec3b>(r, c)[0] > minThresholdBlue && inputImage.at<Vec3b>(r, c)[0] < maxThresholdBlue)
				if (inputImage.at<Vec3b>(r, c)[1] >minThresholdGreen && inputImage.at<Vec3b>(r, c)[1] < maxThresholdGreen)
					if (inputImage.at<Vec3b>(r, c)[2] > minThresholdRed && inputImage.at<Vec3b>(r, c)[2] < maxThresholdRed){
						outputImage.at<Vec3b>(r, c)[2] = newValueRed;
						outputImage.at<Vec3b>(r, c)[1] = newValueRed;
						outputImage.at<Vec3b>(r, c)[0] = newValueRed;
					}
					else
						outputImage.at<Vec3b>(r, c)[2] = inputImage.at<Vec3b>(r, c)[2];
		}
	}
}


