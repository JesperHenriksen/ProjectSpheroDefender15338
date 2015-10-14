#include "opencv2/opencv.hpp"
#include "Sphero.h"
#include "Minimap.h"
#include "CameraFeed.h"
#include <thread>

using namespace cv;
using namespace std;

int main(int, char)
{
	CameraFeed camfeed(0); 
    SpheroCoordinate spheros;
    spheros.startSpheroTracking();  //should run in its own thread
	//Mat frame;
	//frame = camfeed.getImageFromWebcam(0);
	//frame = camfeed.convertRGBtoGS(frame);
	//frame = camfeed.segmentImage(frame);
	//imshow("test", frame);
	Minimap hej;
	hej.segmentImage();
	waitKey(0);
	return 0;
}
