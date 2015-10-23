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
	CameraFeed webcamOne(0);
	Mat frame, raw, blob, gs;
	Minimap minimap;
	//for (;;){
	//	Mat erosionKernel = Mat::ones(5,5,CV_8UC1);
	//	raw = standardWebcam.getImageFromWebcam();
	//	raw.copyTo(frame);
	//	//standardWebcam.thresholdImageColor(frame,frame,0,0,0,0,0,0,0,255,0);
	//	imshow("test", frame);
	//	frame.copyTo(gs);
	//	frame = standardWebcam.convertRGBtoGS(frame);
	//	imshow("greyscale",gs);
	//	standardWebcam.thresholdImage(frame, frame, 0, 50, 0, 50, 150, 255, 150, 255, 0);
	//	erode(frame,frame,erosionKernel);
	//	blob = standardWebcam.grassFire(frame);
	//	imshow("fired the Grassfire",blob);
	//	imshow("input", raw);
	//	if (waitKey(30) >= 0)
	//		break;
	//}
	
	
	//for (;;){//uncomment for coordinates (placeSpell)
	//	Mat frame = webcamOne.getImageFromWebcam(), gs;
	//	double x = 0, y = 0;
	//	frame = webcamOne.convertRGBtoGS(frame);
	//	frame.copyTo(gs);
	//	standardWebcam.thresholdImage(frame,frame,100,255,0,0,100,255);
	//	minimap.placeSpell(frame);
	//	imshow(" ", frame);
	//	imshow(".", gs);
	//	if (waitKey(30) >= 0)
	//		break;
	//}

	for (;;){//uncommet if you want the angle
		Mat frame = webcamOne.getImageFromWebcam(), gs, thresholded;
		//webcamOne.thresholdImageColor(frame, frame, 100, 160, 150, 0, 255, 0, 0, 255, 0);
		minimap.thresholdImageArrow(frame, frame, 100, 160, 255, 0, 70, 0, 70);
		frame.copyTo(gs);
		gs = webcamOne.convertRGBtoGS(frame);
		medianBlur(gs, gs, 5);
		gs.copyTo(thresholded);
		webcamOne.thresholdImage(thresholded, thresholded, 49, 255, 0, 0, 49, 150);
		double angle = 0; 
		angle = webcamOne.getAngleOfVector(gs, 150, 255);
		cout << angle << " " << "\n";
		imshow("color", frame);
		imshow("grayscale", gs);
		imshow("threshold", thresholded);
		if (waitKey(30) >= 0)
			break;
	}
	waitKey(0);
	return 0;
}
