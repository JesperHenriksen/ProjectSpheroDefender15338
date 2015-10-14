#include "opencv2/opencv.hpp"
#include "Sphero.h"
#include "Minimap.h"
#include "CameraFeed.h"
#include <thread>

using namespace cv;
using namespace std;

int main(int, char)
{
	CameraFeed standardWebcam(0); 
	Minimap minimap;
	for (;;){
		Mat frame;
		frame = standardWebcam.getImageFromWebcam();
		frame = standardWebcam.convertRGBtoGS(frame);
		standardWebcam.thresholdImage(frame, frame, 0, 100, 0);
		standardWebcam.thresholdImage(frame, frame, 100, 255, 255);
		imshow("test", frame);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}
