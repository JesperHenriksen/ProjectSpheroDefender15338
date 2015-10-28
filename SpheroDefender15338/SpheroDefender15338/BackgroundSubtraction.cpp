#include "BackgroundSubtraction.h"
#include <queue>
#include <list>

using namespace cv;
using namespace std;

const int FRAMES_TO_LEARN = 200;

BackgroundSubtraction::BackgroundSubtraction()
{
}

BackgroundSubtraction::~BackgroundSubtraction()
{
}

Mat BackgroundSubtraction::subtractBackground(Mat inputFrame, CameraFeed webcam){
	Mat gscale, outputFrame;
	//outputFrame.zeros(inputFrame.rows, inputFrame.cols, CV_8UC1);
	inputFrame.copyTo(gscale);
	gscale = webcam.convertRGBtoGS(inputFrame);
	Mat model = Mat(inputFrame.rows, inputFrame.cols, CV_8UC1, Scalar(0));
	addMatFrames(gscale,model, model);
	//subtractFrame(inputFrame, model, outputFrame);
	return model;
}

void BackgroundSubtraction::addMatFrames(Mat inputOne, Mat inputTwo, Mat dst){
	for (int y = 0; y < dst.rows; y++){
		for (int x = 0; x < dst.cols; x++){
			if ((x - 1) >= 0 && (y - 1) >= 0)
				dst.at<uchar>(y, x) = (inputOne.at<uchar>(y, x) + inputTwo.at<uchar>(y, x)) / 2;
		}
	}
}
void BackgroundSubtraction::subtractFrame(Mat inputOne, Mat inputTwo, Mat dst){
	for (int y = 0; y < dst.rows; y++){
		for (int x = 0; x < dst.cols; x++){
			if ((x - 1) >= 0 && (y - 1) >= 0){
				dst.at<uchar>(y, x) = abs((inputOne.at<uchar>(y, x) - inputTwo.at<uchar>(y, x)));
			}
		}
	}
}
/*
Mat BackgroundSubtraction::subtractBackground(Mat frame, CameraFeed webcam) {
	vector<Mat> model;

	int frameLimit = 300; //Maximum number of frames stored in queue
	if (model.size() >= frameLimit) {
		subtract(frame, getMask(), frame);
	}
	else {
		averageBackground(frame, webcam);
	}
	return frame;
}
/*
void BackgroundSubtraction::averageBackground(Mat frame, CameraFeed webcam, int frameLimit, vector<Mat> model) {
	Mat collectedBackground;
	Mat grayFrame;
	frame.copyTo(grayFrame);
	webcam.convertRGBtoGS(grayFrame);
    grayFrame.convertTo(grayFrame, CV_16UC1);
	
    model.push_back(grayFrame);

    for (int i = 1; i < model.size(); i++) {
        add(model.at(i), collectedBackground, collectedBackground);
    }

    applyMask(collectedBackground, model);
        
    if (model.size() >= frameLimit) {
        model.erase(model.begin());
    }
}

void BackgroundSubtraction::applyMask(Mat collectedBackground, vector<Mat> model) {
	Mat mask;
    collectedBackground.convertTo(mask, CV_8UC1);
    convertScaleAbs(collectedBackground, mask, 1.0 / model.size());
}
*/
