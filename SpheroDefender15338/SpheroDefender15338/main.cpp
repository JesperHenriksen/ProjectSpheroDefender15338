#include "opencv2/opencv.hpp"
#include "Sphero.h"
#include "Minimap.h"
#include "CameraFeed.h"
#include <thread>

using namespace cv;
using namespace std;

int main(int, char)
{
	CameraFeed camfeed(1); 
	Minimap minimap;
	for (;;){
		Mat frame;
		frame = minimap.segmentImage(camfeed);
		imshow("test", frame);
		if (waitKey(30) >= 0)
			break;
	}
	//Mat frame;
	//frame = camfeed.getImageFromWebcam(0);
	//frame = camfeed.convertRGBtoGS(frame);
	//frame = camfeed.segmentImage(frame);
	//imshow("test", frame);
	waitKey(0);
	return 0;
}
