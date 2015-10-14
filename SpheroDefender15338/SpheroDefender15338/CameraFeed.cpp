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
	for (int x = 0; x < inputImage.cols; x++) {
		for (int y = 0; y < inputImage.rows; y++) { //runs through the pixels
			if (inputImage.at<uchar>(y, x) > 60) { //if there is informations in the input pixel
				if ((x - 1) >= 0 && (y - 1) >= 0) { //if both of the kernel pixels is inside the bounderies of the inputimage
					if (output.at<uchar>(y, (x - 1)) != 0 || output.at<uchar>((y - 1), x) != 0){ //if there is information either in the pixel above or in the pixel before
						if (output.at<uchar>(y, x - 1) != 0 && output.at<uchar>(y - 1, x) != 0){ //if there is information in two different blobs in both x and y direction 
							if (output.at<uchar>(y, x - 1) < output.at<uchar>(y - 1, x)){ //if the x value is lower than the y value
								output.at<uchar>(y - 1, x) = output.at<uchar>(y, x - 1); // set the y value equal to the x value;
								continue;
							}
							else{
								output.at<uchar>(y, x - 1) = output.at<uchar>(y - 1, x); //otherwise set x value equal to y value
								continue;
							}
						}
					}
				} // if there is not information in both the pixel above and the pixel behind
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
				output.at<uchar>(y, x) = currentID; //otherwise set the pixel to the current id
				currentID++;//increase id
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
