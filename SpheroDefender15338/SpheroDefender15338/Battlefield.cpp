#include "Battlefield.h"
#include "CameraFeed.h"
#include "Minimap.h"
#include "opencv2\opencv.hpp"

using namespace std;
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
	Mat input;
	image.copyTo(input);
	// make a rect 
	// check if sphero pos is outside the rect
	int greenMin = 30;
	int greenMax = 90;
	int maxRow = 0, minRow = 0;
	int maxCol = 0, minCol = 0;
	cvtColor(image, input, CV_BGR2HSV);

	// this has to happen once
	for (int r = 0; r < image.rows; r++){
		for (int c = 0; c < image.cols; c++){
			if (input.at<Vec3b>(r, c)[0] > greenMin && input.at<Vec3b>(r, c)[0] < greenMax){
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
	imshow("sphero input", frame);

	cvtColor(frame, frame, CV_BGR2GRAY); // convert from color to HSV
	medianBlur(frame, frame, 9); // remove salt pepper noise
	webcamSphero.thresholdImage(frame, frame, 0, 180, 0, 180, 255, 255); // make high values completly white
	imshow("sphero", frame);
	minimap.placeSpell(frame, 254, 256, xCoordSphero, yCoordSphero); // find middle point of pixels within the threshold

}

void Battlefield::removeObstacle(Mat inputImage, Mat resetImage, double spheroX, double spheroY, double scalar){
	int x = (spheroX) *scalar, y = (spheroY) * scalar;
	double distance = 40 * scalar;
	int forgiveness = 50;
	for (double k = x - forgiveness; k < x + forgiveness; k++){
		for (double h = y - forgiveness; h < y + forgiveness; h++){
			if (k < 0)
				continue;
			if (k > inputImage.cols)
				continue;;
			if (h < 0)
				continue;
			if (h > inputImage.rows)
					continue;
			if (inputImage.at<Vec3b>(h, k)[0] == 128 &&
				inputImage.at<Vec3b>(h, k)[1] == 0 &&
				inputImage.at<Vec3b>(h, k)[2] == 128 ||

				inputImage.at<Vec3b>(h, k)[0] == 0 &&
				inputImage.at<Vec3b>(h, k)[1] == 120 &&
				inputImage.at<Vec3b>(h, k)[2] == 235 ||

				inputImage.at<Vec3b>(h, k)[0] == 0 &&
				inputImage.at<Vec3b>(h, k)[1] == 0 &&
				inputImage.at<Vec3b>(h, k)[2] == 255 ||

				inputImage.at<Vec3b>(h, k)[0] == 255 &&
				inputImage.at<Vec3b>(h, k)[1] == 0 &&
				inputImage.at<Vec3b>(h, k)[2] == 0){

				for (double i = x - distance; i < x + distance; i++){
					for (double j = y - distance; j < y + distance; j++){
						inputImage.at<Vec3b>(j, i)[0] = resetImage.at<Vec3b>(j, i)[0];
						inputImage.at<Vec3b>(j, i)[1] = resetImage.at<Vec3b>(j, i)[1];
						inputImage.at<Vec3b>(j, i)[2] = resetImage.at<Vec3b>(j, i)[2];
					}
				}
			}
		}
	}
	//for (double i = x - distance; i < x + distance; i++){
	//	for (double j = y - distance; j < y + distance; j++){
	//		inputImage.at<Vec3b>(j, i)[0] = 255;
	//		inputImage.at<Vec3b>(j, i)[1] = 255;
	//		inputImage.at<Vec3b>(j, i)[2] = 255;
	//	}
	//}
}

void Battlefield::throwSpell(Mat inputImage, double minimapXCoord, double minimapYCoord, int handsign, double scalar){
	if (scalar == 1) {
		cout << "scalar == 1";
		Mat battlefieldBob = imread("../../../../../Google Drev/MTA15338/Project/Design/ProgramLayers/BattlefieldSmall.png", 1);
		battlefieldBob.copyTo(inputImage);
	}
	else {
		cout << "scalar not 1";
		Mat battlefieldBob = imread("../../../../../Google Drev/MTA15338/Project/Design/ProgramLayers/BattlefieldMedium.png", 1);
		battlefieldBob.copyTo(inputImage);
	}

	double distance = 10 * scalar;
	for (double x = (minimapXCoord * scalar) - distance; x < minimapXCoord * scalar + distance; x++){
		for (double y = minimapYCoord * scalar - distance; y < minimapYCoord * scalar + distance; y++){
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
