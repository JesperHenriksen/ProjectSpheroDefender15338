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

Mat CameraFeed::getImageFromWebcam(int x){
	Mat frame;
	if (!cap.isOpened())
		return frame;
	cap >> frame;
	return frame;
}

void CameraFeed::grassfireSecondRunthrough(Mat inputImage, Mat outputImage){
	for (int x = inputImage.cols; x > 0; x--) {
		for (int y = inputImage.rows; y > 0; y--) { //runs through the pixels backwards
			if (inputImage.at<uchar>(y, x) == 0){
				continue;
			}
			if (inputImage.at<uchar>(y, x)){
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
