#include "opencv2/opencv.hpp"
#include "Sphero.h"
#include "Minimap.h"
#include <thread>

using namespace cv;
using namespace std;

int main(int, char)
{
	Minimap minimap;
	int direction = minimap.getDirection();
	/*VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()) // check if we succeeded
		return 0;
	Mat original;
	//thread getImageThread (getImageFromWebcam,cap);
	cvtColor(frame, original, CV_8U); // RGB 8-Bit Color image
	Mat channel[3], red[3], green[3], blue[3];
	//bool gR = true, rR = true, bR = true;
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		//cvtClor(frame, edges, CV_BGR2GRAY); //greyscale
		displayChannel(red,0,1,frame,"red");
		//displayChannel(blue, 1, 2, frame, "Blue");
		//displayChannel( green, 0, 2, frame, "Green");
		if (waitKey(30) >= 0)
			break;
	}*/
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
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