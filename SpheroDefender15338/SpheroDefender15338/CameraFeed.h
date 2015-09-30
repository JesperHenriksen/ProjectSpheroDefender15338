#include "opencv2/opencv.hpp"
#pragma once
using namespace cv;
class CameraFeed
{
public:
	CameraFeed();
	~CameraFeed();
	Mat getImageFromWebcam(VideoCapture capture);
	Mat negateChannel(int channelNegate1, Mat frame);
	Mat setZeroesInChannel(Mat inputFrame);
};

