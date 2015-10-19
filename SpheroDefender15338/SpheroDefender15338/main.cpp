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
		Mat frame, raw, blob;
		raw = standardWebcam.getImageFromWebcam();
		frame = standardWebcam.getImageFromWebcam();
		frame = standardWebcam.convertRGBtoGS(frame);
		standardWebcam.thresholdImage(frame, frame, 0, 100, 0);
		standardWebcam.thresholdImage(frame, frame, 100, 230, 255);
		standardWebcam.thresholdImage(frame,frame, 230,255,0);
		imshow("test", frame);
		blob = standardWebcam.grassFire(frame);
		imshow("raw input",blob);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}
