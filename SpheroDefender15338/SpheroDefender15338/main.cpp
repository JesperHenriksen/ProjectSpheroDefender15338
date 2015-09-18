#include "opencv2/opencv.hpp"
#include "Sphero.h"
#include <thread>

using namespace cv;
using namespace std;


Mat selectChannel(Mat frame);
void displayChannel(Mat channel[], int channelNegate1, int channelNegate2, Mat frame, String color);

int main(int, char)
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()) // check if we succeeded
		return -1;
	Mat original;
	Mat channel[3], red[3], green[3], blue[3];
	bool gR = true, rR = true, bR = true;
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		//cvtColor(frame, edges, CV_BGR2GRAY); //greyscale
		cvtColor(frame, original, CV_8U); // RGB 8-Bit Color image
		//displayChannel(red,0,1,frame,"red");
		//displayChannel(blue, 1, 2, frame, "Blue");
		//displayChannel( green, 0, 2, frame, "Green");
		if (waitKey(30) >= 0)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}

void displayChannel(Mat channel[], int channelNegate1, int channelNegate2, Mat frame, String color) 
{
	Mat newFrame = frame;
	split(newFrame, channel);
	channel[channelNegate1] = selectChannel(newFrame);
	channel[channelNegate2] = selectChannel(newFrame);
	merge(channel, 3, newFrame);
	imshow(color, newFrame);
}

Mat selectChannel(Mat frame){
	Mat newFrame = frame;
	return Mat::zeros(newFrame.rows, newFrame.cols, CV_8UC1);
}


/*imshow("Original", original);
//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
//Canny(edges, edges, 1, 10,3);
channel[0] = selectChannel(frame);
channel[1] = selectChannel(frame);
merge(channel, 3, frame);
imshow("Red", frame);
cap >> frame2;
green[0] = selectChannel(frame2);
green[2] = selectChannel(frame2);
merge(green, 3, frame2);
imshow("Green", frame2);
cap >> frame;
blue[1] = selectChannel(frame);
blue[2] = selectChannel(frame);
merge(blue, 3, frame);
imshow("Blue", frame);*/