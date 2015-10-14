#include "CameraFeed.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

CameraFeed::CameraFeed(int capture)
{
	cap.open(capture);
}


CameraFeed::~CameraFeed()
{
}

Mat CameraFeed::getImageFromWebcam(){
	Mat frame;
	if (!cap.isOpened())
		return frame;
	cap >> frame;
	return frame;
}


/*
Does the pixel to the left(West) have the same value as the current pixel ?
	Yes – We are in the same region.Assign the same label to the current pixel
	No – Check next condition
Do both pixels to the North and West of the current pixel have the same value as the current pixel but not the same label ?
	Yes – We know that the North and West pixels belong to the same region and must be merged.Assign the current pixel the minimum of the North and West labels, and record their equivalence relationship
	No – Check next condition
Does the pixel to the left(West) have a different value and the one to the North the same value as the current pixel ?
	Yes – Assign the label of the North pixel to the current pixel
	No – Check next condition
Do the pixel's North and West neighbors have different pixel values than current pixel?
	Yes – Create a new label id and assign it to the current pixel
*/
void CameraFeed::grassfireSecondRunthrough(Mat inputImage, Mat outputImage){
	for (int x = inputImage.cols; x > 0; x--) {
		for (int y = inputImage.rows; y > 0; y--) { //runs through the pixels
			if (inputImage.at<uchar>(y, x) == inputImage.at<uchar>(y, x - 1)){
				inputImage.at<uchar>(y, x) = inputImage.at<uchar>(y, x - 1);
			}
			else if (inputImage.at<uchar>(y, x) == inputImage.at<uchar>(y, x - 1)){

			}
		}
	}
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
	//threshold(outputFrame, outputFrame, 70, 255, THRESH_BINARY); //thresholds the image to 30 and 255 with binary values.
	imshow("WizardMinimap", outputFrame);
	imshow("input", inputFrame);
	if (waitKey(30) >= 0)
		return outputFrame;
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
	Mat newFrame = inputFrame;
	return Mat::zeros(newFrame.rows, newFrame.cols, CV_8UC1);
}
