#include "CameraFeed.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

CameraFeed::CameraFeed()
{
}


CameraFeed::~CameraFeed()
{
}
Mat CameraFeed::getImageFromWebcam(VideoCapture capture){
	Mat frame;
	if (!capture.isOpened())
		return frame;
	capture >> frame;
	return frame;
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
