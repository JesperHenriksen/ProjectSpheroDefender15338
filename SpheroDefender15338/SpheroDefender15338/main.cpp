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
	CameraFeed webcamOne(1);
	Mat frame, raw, blob, gs;
	Minimap minimap;
    //SpheroCoordinate spheroTrack;
    //spheroTrack.startSpheroTracking();
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
		imshow("color", frame);
		minimap.thresholdImageArrow(frame, frame, 100, 160, 255, 0, 70, 0, 70);
		gs.zeros(frame.cols, frame.rows, frame.type());
		gs = webcamOne.convertRGBtoGS(frame);
		thresholded.zeros(gs.cols,gs.rows,gs.type());
		medianBlur(gs, thresholded, 5);
		webcamOne.thresholdImage(thresholded, thresholded, 49, 255, 0, 0, 50, 150);
		double angle = 0; 
		angle = webcamOne.getAngleOfArrow(thresholded, 150, 255);
		cout << angle << " " << "\n";
		//imshow("grayscale", gs);
		//imshow("threshold", thresholded);
		if (waitKey(30) >= 0)
			break;
	}
	waitKey(0);
	return 0;
}
