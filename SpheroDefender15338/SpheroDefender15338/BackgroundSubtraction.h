#include "opencv2\opencv.hpp"
#include "CameraFeed.h"
#pragma once
using namespace cv;

class BackgroundSubtraction
{
public:
    BackgroundSubtraction();
    ~BackgroundSubtraction();

	void averageBackground(Mat frame, CameraFeed webcam);
    Mat subtractBackground(Mat frame, CameraFeed webcam);
	void subtractBackgroundTwo(Mat frame, CameraFeed webcam);
private:
//	void applyMask(Mat collectedBackground, vector<Mat> model);
	void addMatFrames(Mat inputOne, Mat inputTwo, Mat dst);
	void subtractFrame(Mat inputOne, Mat inputTwo, Mat dst);

};

