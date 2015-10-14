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
	inputArrow = camfeed.getImageFromWebcam(0);
	outputArrow = camfeed.getImageFromWebcam(0);
	inputArrow = camfeed.convertRGBtoGS(inputArrow);
	outputArrow = camfeed.convertRGBtoGS(outputArrow);
	camfeed.thresholdImage(inputArrow, outputArrow, 60, 255, 0);
	camfeed.thresholdImage(outputArrow, outputArrow, 0, 60, 255);

	//median
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

void grassFire(Mat inputImage, Mat output){
	output.zeros(inputImage.rows, inputImage.cols, inputImage.type());
	int currentID = 1;
	for (int x = 0; x < inputImage.cols; x++) {
		for (int y = 0; y < inputImage.rows; y++) { //runs through the pixels
			if (inputImage.at<uchar>(y, x) > 60) { //if there is informations in the input pixel
				if (output.at<uchar>(y, x - 1) != 0 || output.at<uchar>(y - 1, x) != 0){ //if there is information either in the pixel above or the pixel in the pixel before
					if ((x - 1) >= 0 && (y - 1) >= 0) { //and if both of the kernel pixels is inside the bounderies of the inputimage
						if (output.at<uchar>(y, x - 1) != 0 && output.at<uchar>(y - 1, x) != 0){ //if there is information in two different blobs in both x and y direction 
							if (output.at<uchar>(y, x - 1) < output.at<uchar>(y - 1, x)){ //if the x value is lower than the y value
								output.at<uchar>(y - 1, x) = output.at<uchar>(y, x - 1); // set the y value equal to the x value;
							}
							else{
								output.at<uchar>(y, x - 1) = output.at<uchar>(y - 1, x); //otherwise set x value equal to y value
							}
						}
					}
					if ((x - 1) >= 0){ // if there is a pixels behind the current pixel
						if (output.at<uchar>(y, x - 1) != 0) { // if there is information behind the current pixel
							output.at<uchar>(y, x) = output.at<uchar>(y, x - 1); // set the current pixel value to the value of the x pixel
						}
					}
					if ((y - 1) >= 0){ //if there is a pixel above the current pixel
						if (output.at<uchar>(y - 1, x) != 0){ // if there is information above the current pixel
							output.at<uchar>(y, x) = output.at<uchar>(y - 1, x); // set the current pixel value to the value of the y pixel
						}
					}
				}
				else
					output.at<uchar>(y, x) = currentID; //otherwise set the pixel to the current id
				if (inputImage.at<uchar>(y, x + 1) == 0) //if the next pixel is black,
					currentID++;//increase id
			}
		}
	}
	return;
}




int getDirection(){
	return 0;
}

