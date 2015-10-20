#include "CameraFeed.h"
#include "opencv2/opencv.hpp"
#include "math.h"

using namespace cv;
using namespace std;

CameraFeed::CameraFeed(int capture)
{
	cap.open(capture);
}


CameraFeed::~CameraFeed()
{
}

double CameraFeed::getAngleOfVector(Mat inputImage, int thresholdOne, int thresholdTwo){
	double result = 0;
	int xMinRec = 0, xMaxRec = 0, yMinRec = 0, yMaxRec= 0;
	int triXMin = 0, triXMax = 0, triYMin = 0, triYMax = 0;
	for (int y = 0; y < inputImage.rows; y++){
		for (int x = 0; x < inputImage.cols; x++){
			if (inputImage.at<uchar>(y, x) != 0 && inputImage.at<uchar>(y, x) < thresholdOne && x < xMinRec){
				xMinRec = x;
			}
			if (inputImage.at<uchar>(y, x) != 0 && inputImage.at<uchar>(y, x) < thresholdOne && x > xMaxRec){
				xMaxRec = x;
			}
			if (inputImage.at<uchar>(y, x) != 0 && inputImage.at<uchar>(y, x) < thresholdOne && y < yMinRec){
				yMinRec = y;
			}
			if (inputImage.at<uchar>(y, x) != 0 && inputImage.at<uchar>(y, x) < thresholdOne && y > yMaxRec){
				yMaxRec = y;
			}

			if (inputImage.at<uchar>(y, x) > thresholdOne && inputImage.at<uchar>(y, x) < thresholdTwo && triXMin < x){
				triXMin = x;
			}
			if (inputImage.at<uchar>(y, x) > thresholdOne && inputImage.at<uchar>(y, x) < thresholdTwo && triXMax > x){
				triXMax = x;
			}
			if (inputImage.at<uchar>(y, x) > thresholdOne && inputImage.at<uchar>(y, x) < thresholdTwo && triYMin < y){
				triYMin = y;
			}
			if (inputImage.at<uchar>(y, x) > thresholdOne && inputImage.at<uchar>(y, x) < thresholdTwo && triYMax > y){
				triYMax = y;
			}
		}
	}
	double recCenterX = 0, recCenterY = 0;
	recCenterX = (xMinRec - xMaxRec) / 2; 
	recCenterY = (yMinRec - yMaxRec) / 2;
	double triCenterX = 0, triCenterY = 0;
	triCenterX = (triXMin - triXMax) / 2;
	triCenterY = (triXMin - triYMax) / 2;
	result = atan2(recCenterY - triCenterY, recCenterX - triCenterX) * 180 / 3.14;
	return result;
}

Mat CameraFeed::getImageFromWebcam(){
	Mat frame;
	if (!cap.isOpened())
		return frame;
	cap >> frame;
	return frame;
}

Mat CameraFeed::grassfireSecondRunthrough(Mat inputImage){
	Mat result;
	inputImage.copyTo(result);
	for (int x = inputImage.cols - 1; x > 10; x--) {
		for (int y = inputImage.rows -1; y > 10; y--) { //runs through the pixels backwards
			if (!(result.at<uchar>(y, x) != 0)){
				continue;
			}
			if ((y - 1) >= 0) {
				if (result.at<uchar>(y - 1, x) > result.at<uchar>(y, x))
					result.at<uchar>(y - 1, x) = result.at<uchar>(y, x);
			}
			if ((x - 1) >= 0) {
				if (result.at<uchar>(y, x - 1) > result.at<uchar>(y, x))
					result.at<uchar>(y, x - 1) = result.at<uchar>(y, x);
			}
		}
	}
	return result;
}

Mat CameraFeed::grassFire(Mat inputImage){
	Mat output;
	output = output.zeros(inputImage.rows, inputImage.cols, inputImage.type());
	int currentID = 1;
	for (int y = 0; y < inputImage.rows; y++) { //runs through the pixels
		for (int x = 0; x < inputImage.cols; x++) {
			if (inputImage.at<uchar>(y, x) > 60) { //if there is informations in the input pixel
				if ((x - 1) >= 0 && (y - 1) >= 0) { //if both of the kernel pixels is inside the bounderies of the inputimage
					if (output.at<uchar>(y, (x - 1)) != 0 || output.at<uchar>((y - 1), x) != 0){ //if there is information either in the pixel above or in the pixel before
						if (output.at<uchar>(y, x - 1) != 0 && output.at<uchar>(y - 1, x) != 0){ //if there is information in two different blobs in both x and y direction 
							if (output.at<uchar>(y, x - 1) < output.at<uchar>(y - 1, x)){ //if the x value is lower than the y value
								output.at<uchar>(y, x) = output.at<uchar>(y, x - 1); // set the y value equal to the x value;
								continue;
							}
							else{
								output.at<uchar>(y, x) = output.at<uchar>(y - 1, x); //otherwise set x value equal to y value
								continue;
							}
						}// if there is not information in both the pixel above and the pixel behind
						if ((x - 1) >= 0){ // if there is a pixel behind the current pixel
							if (output.at<uchar>(y, x - 1) != 0) { // if there is information in the pixel behind the current pixel
								output.at<uchar>(y, x) = output.at<uchar>(y, x - 1); // set the current pixel value to the value of the x pixel
								continue;
							}
						}
						if ((y - 1) >= 0){ //if there is a pixel above the current pixel
							if (output.at<uchar>(y - 1, x) != 0){ // if there is information above the current pixel
								output.at<uchar>(y, x) = output.at<uchar>(y - 1, x); // set the current pixel value to the value of the y pixel
								continue;
							}
						}
					}
					else{ //if there is no information in the output image
						output.at<uchar>(y, x) = currentID; //otherwise set the pixel to the current id
						currentID++;//increase id
					}
				}
			}
		}
	}
	output = grassfireSecondRunthrough(output); //connect the connected blobs 
	return output;
}

Mat CameraFeed::convertRGBtoGS(Mat inputFrame){
	Mat outputFrame;
	cvtColor(inputFrame, outputFrame, CV_RGB2GRAY);
	return outputFrame;
}

Mat CameraFeed::segmentImage(Mat inputFrame){
	Mat outputFrame;
	medianBlur(inputFrame, outputFrame, 3);
	thresholdImage(outputFrame, outputFrame, 0, 100, 0);
	imshow("WizardMinimap", outputFrame);
	imshow("input", inputFrame);
	return outputFrame;
}

void CameraFeed::thresholdImage(Mat inputImage, Mat outputImage, int minThreshold, int maxThreshold, int newValue){
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<uchar>(r, c) > minThreshold &&
				inputImage.at<uchar>(r, c) < maxThreshold)
				outputImage.at<uchar>(r, c) = newValue;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);
		}
	}
}
void CameraFeed::thresholdImage(Mat inputImage, Mat outputImage, int minThresholdOne, int maxThresholdOne, int newValueOne, 
	int minThresholdTwo, int maxThresholdTwo, int newValueTwo)
{
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<uchar>(r, c) > minThresholdOne &&
				inputImage.at<uchar>(r, c) < maxThresholdOne)
				outputImage.at<uchar>(r, c) = newValueOne;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);
			if (inputImage.at<uchar>(r, c) > minThresholdTwo &&
				inputImage.at<uchar>(r, c) < maxThresholdTwo)
				outputImage.at<uchar>(r, c) = newValueTwo;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);
		}
	}
}

void CameraFeed::thresholdImage(Mat inputImage, Mat outputImage, 
	int minThresholdOne, int maxThresholdOne, int newValueOne,
	int minThresholdTwo, int maxThresholdTwo, int newValueTwo,
	int minThresholdThree, int maxThresholdThree, int newValueThree)
{
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<uchar>(r, c) > minThresholdOne &&
				inputImage.at<uchar>(r, c) < maxThresholdOne)
				outputImage.at<uchar>(r, c) = newValueOne;
			else if (true)
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);

			if (inputImage.at<uchar>(r, c) > minThresholdTwo &&
				inputImage.at<uchar>(r, c) < maxThresholdTwo)
				outputImage.at<uchar>(r, c) = newValueTwo;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);

			if (inputImage.at<uchar>(r, c) > minThresholdThree &&
				inputImage.at<uchar>(r, c) < maxThresholdThree)
				outputImage.at<uchar>(r, c) = newValueThree;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);
		}
	}
}

void CameraFeed::thresholdImageColor(Mat inputImage, Mat outputImage, int minThresholdRed, int maxThresholdRed, int newValueRed, 
																	  int minThresholdGreen, int maxThresholdGreen, int newValueGreen,
																	  int minThresholdBlue, int maxThresholdBlue, int newValueBlue){
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<Vec3b>(r, c)[0] < maxThresholdBlue)
				outputImage.at<Vec3b>(r, c)[0] = newValueBlue;
			else
				outputImage.at<Vec3b>(r, c)[0] = inputImage.at<Vec3b>(r, c)[0];

			if (inputImage.at<Vec3b>(r, c)[1] < maxThresholdGreen)
				outputImage.at<Vec3b>(r, c)[1] = newValueGreen;
			else
				outputImage.at<Vec3b>(r, c)[1] = inputImage.at<Vec3b>(r, c)[1];

			if (inputImage.at<Vec3b>(r, c)[2] < maxThresholdRed)
				outputImage.at<Vec3b>(r, c)[2] = newValueRed;
			else
				outputImage.at<Vec3b>(r, c)[2] = inputImage.at<Vec3b>(r, c)[1];
		}
	}
}

Mat CameraFeed::negateChannel(int channelNegate1, Mat frame)
{
	Mat newFrame = frame;
	Mat channel[3];
	split(newFrame, channel);
	channel[channelNegate1] = setZeroesInChannel(newFrame);
	merge(channel, 3, newFrame);
	return newFrame;
}

Mat CameraFeed::setZeroesInChannel(Mat inputFrame){
	Mat newFrame;
	inputFrame.copyTo(newFrame);
	return Mat::zeros(newFrame.rows, newFrame.cols, CV_8UC1);
}
