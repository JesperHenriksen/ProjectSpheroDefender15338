#include "Battlefield.h"
#include "CameraFeed.h"
#include "Minimap.h"
#include "opencv2\opencv.hpp"

using namespace cv;

Battlefield::Battlefield()
{
}


Battlefield::~Battlefield()
{
}




bool Battlefield::isSpheroOutOfBounds(Mat image, double spheroPosCols, double spheroPosRows){
	// find position of green pixels at min y, max y, min x and max x

	// find position of red pixels at corners

	// make a rect 
	// check if sphero pos is outside the rect
	int greenMin = 30;
	int greenMax = 90;
	int maxRow = 0, minRow = 0;
	int maxCol = 0, minCol = 0;
	cvtColor(image, image, CV_BGR2HSV);

	// this has to happen once
	for (int r = 0; r < image.rows; r++){
		for (int c = 0; c < image.cols; c++){
			if (image.at<Vec3b>(r, c)[0] > greenMin && image.at<Vec3b>(r, c)[0] < greenMax){
				if (r < minRow)
					minRow = r;
				if (r > maxRow)
					maxRow = r;
				if (c < minCol)
					minCol = c;
				if (c > maxCol)
					maxCol = c;
			}
		}
	}
	// this has to happen continues
	if (spheroPosRows < minRow ||
		spheroPosRows > maxRow ||
		spheroPosCols < minCol ||
		spheroPosCols > maxCol){
		//return something that indicates sphero is out of bounds
		return true;
	}
	else{
		return false;
	}
}

void Battlefield::trackSphero(CameraFeed webcamSphero, double &xCoordSphero, double &yCoordSphero) {

	Mat frame;
	Minimap minimap;
	frame = webcamSphero.getImageFromWebcam();
	//frame = webcamSphero.convertRGBtoGS(frame);

	cvtColor(frame, frame, CV_BGR2GRAY); // convert from color to HSV
	medianBlur(frame, frame, 9); // remove salt pepper noise
	webcamSphero.thresholdImage(frame, frame, 0, 220, 0, 220, 255, 255); // make high values completly white
	//imshow("sphero", frame);
	minimap.placeSpell(frame, 254, 256, xCoordSphero, yCoordSphero); // find middle point of pixels within the threshold

}

void Battlefield::removeObstacle(Mat inputImage, Mat resetImage, double spheroX, double spheroY, double scalar){
	if (inputImage.at<Vec3b>(spheroY, spheroX)[0] == 128 &&
		inputImage.at<Vec3b>(spheroY, spheroX)[1] == 0 &&
		inputImage.at<Vec3b>(spheroY, spheroX)[2] == 128 ||

		inputImage.at<Vec3b>(spheroY, spheroX)[0] == 0 &&
		inputImage.at<Vec3b>(spheroY, spheroX)[1] == 120 &&
		inputImage.at<Vec3b>(spheroY, spheroX)[2] == 235 ||

		inputImage.at<Vec3b>(spheroY, spheroX)[0] == 0 &&
		inputImage.at<Vec3b>(spheroY, spheroX)[1] == 0 &&
		inputImage.at<Vec3b>(spheroY, spheroX)[2] == 255 ||

		inputImage.at<Vec3b>(spheroY, spheroX)[0] == 255 &&
		inputImage.at<Vec3b>(spheroY, spheroX)[1] == 0 &&
		inputImage.at<Vec3b>(spheroY, spheroX)[2] == 0){
		int distance = 20 * scalar;
		for (int x = spheroX * scalar - distance; x < spheroX * scalar + distance; x++){
			for (int y = spheroY * scalar - distance; y < spheroY * scalar + distance; y++){
				inputImage.at<Vec3b>(y, x)[0] = resetImage.at<Vec3b>(y, x)[0];
				inputImage.at<Vec3b>(y, x)[1] = resetImage.at<Vec3b>(y, x)[1];
				inputImage.at<Vec3b>(y, x)[2] = resetImage.at<Vec3b>(y, x)[2];
			}
		}

	}
}

void Battlefield::throwSpell(Mat inputImage, double minimapXCoord, double minimapYCoord, int handsign, double scalar){
	if (scalar == 1) {
		Mat battlefieldBob = imread("../../../../../Google Drev/MTA15338/Project/Design/ProgramLayers/BattlefieldSmall.png", 1);
		battlefieldBob.copyTo(inputImage);
	}
	else {
		Mat battlefieldBob = imread("../../../../../Google Drev/MTA15338/Project/Design/ProgramLayers/BattlefieldMedium.png", 1);
		battlefieldBob.copyTo(inputImage);
	}

	int distance = 10 * scalar;
	for (int x = minimapXCoord * scalar - distance; x < minimapXCoord * scalar + distance; x++){
		for (int y = minimapYCoord * scalar - distance; y < minimapYCoord * scalar + distance; y++){
			if (x < 0)
				x = 0;
			if (x > inputImage.cols)
				x = inputImage.cols;
			if (y < 0)
				y = 0;
			if (y > inputImage.rows)
				y = inputImage.rows;
			if (handsign == 1) {
				inputImage.at<Vec3b>(y, x)[0] = 128;
				inputImage.at<Vec3b>(y, x)[1] = 0;
				inputImage.at<Vec3b>(y, x)[2] = 128;
			}
			if (handsign == 2) {
				inputImage.at<Vec3b>(y, x)[0] = 0;
				inputImage.at<Vec3b>(y, x)[1] = 120;
				inputImage.at<Vec3b>(y, x)[2] = 235;
			}
			if (handsign == 3) {
				inputImage.at<Vec3b>(y, x)[0] = 0;
				inputImage.at<Vec3b>(y, x)[1] = 0;
				inputImage.at<Vec3b>(y, x)[2] = 255;
			}
			if (handsign == 4) {
				inputImage.at<Vec3b>(y, x)[0] = 255;
				inputImage.at<Vec3b>(y, x)[1] = 0;
				inputImage.at<Vec3b>(y, x)[2] = 0;
			}
		}
	}
}
