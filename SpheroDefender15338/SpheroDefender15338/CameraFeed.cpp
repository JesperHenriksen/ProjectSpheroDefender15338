#include "CameraFeed.h"
#include "opencv2/opencv.hpp"
#include "math.h"

using namespace cv;
using namespace std;

CameraFeed::CameraFeed(int capture)
{
	cap.open(capture);
}


CameraFeed::~CameraFeed()
{
}

Mat CameraFeed::getImageFromWebcam(){
	Mat frame;
	if (!cap.isOpened())
		return frame;
	cap >> frame;
	return frame;
}

void CameraFeed::inputImageFixing(Mat inputImage, Mat dst, int minThreshold, int maxThreshold){
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			dst.at<uchar>(r, c) = (255 / (maxThreshold - minThreshold)) * (inputImage.at<uchar>(r, c) - minThreshold);
		}
	}
}

Mat CameraFeed::equalizeHistogram(Mat inputImage, Mat dst) {
	Mat result = inputImage.clone();
	result.zeros(inputImage.rows, inputImage.cols, inputImage.type());
	if (inputImage.data && !inputImage.empty()) {
		int histogram[256]; //Array for storing histogram values
		int cumuHistogram[256]; //Array for storing the cumulative histogram values
		int grayscale = 256;
		//inputImage histogram
		for (int i = 0; i < grayscale; i++) {
			histogram[i] = 0;
		}
		for (int y = 0; y < inputImage.rows; y++) {
			for (int x = 0; x < inputImage.cols; x++) {
				histogram[inputImage.at<unsigned char>(y, x)]++;
			}
		}

		//cumulativeHistogram
		cumuHistogram[0] = histogram[0];
		for (int i = 1; i < grayscale; i++) {
			histogram[i] = histogram[i - 1] + cumuHistogram[i];
		}
		//equalizedImage
		int size = inputImage.rows * inputImage.cols;
		float probability = 255.0 / size;
		for (int y = 0; y < inputImage.rows; y++) {
			for (int x = 0; x < inputImage.cols; x++) {
				result.at<unsigned char>(y, x) = ((cumuHistogram[inputImage.at<unsigned char>(y, x)]) * probability);
			}
		}
	}
	return result;
}

Mat CameraFeed::grassfireSecondRunthrough(Mat inputImage){
	Mat result;
	inputImage.copyTo(result);
	for (int x = inputImage.cols - 1; x > 10; x--) {
		for (int y = inputImage.rows -1; y > 10; y--) { //runs through the pixels backwards
			if (result.at<uchar>(y, x) == 0){
				continue;
			}
			if ((y - 1) >= 0) {
				if (result.at<uchar>(y - 1, x) > result.at<uchar>(y, x))
					result.at<uchar>(y - 1, x) = result.at<uchar>(y, x);
			}
			if ((x - 1) >= 0) {
				if (result.at<uchar>(y, x - 1) > result.at<uchar>(y, x))
					result.at<uchar>(y, x - 1) = result.at<uchar>(y, x);
			}
		}
	}
	return result;
}

Mat CameraFeed::grassFire(Mat inputImage){
	Mat output;
	output = output.zeros(inputImage.rows, inputImage.cols, inputImage.type());
	int currentID = 1;
	for (int y = 0; y < inputImage.rows; y++) { //runs through the pixels
		for (int x = 0; x < inputImage.cols; x++) {
			if (inputImage.at<uchar>(y, x) > 60) { //if there is informations in the input pixel
				if ((x - 1) >= 0 && (y - 1) >= 0) { //if both of the kernel pixels is inside the bounderies of the inputimage
					if (output.at<uchar>(y, (x - 1)) != 0 || output.at<uchar>((y - 1), x) != 0){ //if there is information either in the pixel above or in the pixel before
						if (output.at<uchar>(y, x - 1) != 0 && output.at<uchar>(y - 1, x) != 0){ //if there is information in two different blobs in both x and y direction 
							if (output.at<uchar>(y, x - 1) < output.at<uchar>(y - 1, x)){ //if the x value is lower than the y value
								output.at<uchar>(y, x) = output.at<uchar>(y, x - 1); // set the y value equal to the x value;
								continue;
							}
							else{
								output.at<uchar>(y, x) = output.at<uchar>(y - 1, x); //otherwise set x value equal to y value
								continue;
							}
						}// if there is not information in both the pixel above and the pixel behind
						if ((x - 1) >= 0){ // if there is a pixel behind the current pixel
							if (output.at<uchar>(y, x - 1) != 0) { // if there is information in the pixel behind the current pixel
								output.at<uchar>(y, x) = output.at<uchar>(y, x - 1); // set the current pixel value to the value of the x pixel
								continue;
							}
						}
						if ((y - 1) >= 0){ //if there is a pixel above the current pixel
							if (output.at<uchar>(y - 1, x) != 0){ // if there is information above the current pixel
								output.at<uchar>(y, x) = output.at<uchar>(y - 1, x); // set the current pixel value to the value of the y pixel
								continue;
							}
						}
					}
					else{ //if there is no information in the output image
						output.at<uchar>(y, x) = currentID; //otherwise set the pixel to the current id
						currentID++;//increase id
					}
				}
				else {//if not both kernels are inside the inputImage aka what should happend at the borders?
					if ((x - 1) >= 0){ // if there is a pixel behind the current pixel
						if (output.at<uchar>(y, x - 1) != 0) { // if there is information in the pixel behind the current pixel
							output.at<uchar>(y, x) = output.at<uchar>(y, x - 1); // set the current pixel value to the value of the x pixel
							continue;
						}
					}
					if ((y - 1) >= 0){ //if there is a pixel above the current pixel
						if (output.at<uchar>(y - 1, x) != 0){ // if there is information above the current pixel
							output.at<uchar>(y, x) = output.at<uchar>(y - 1, x); // set the current pixel value to the value of the y pixel
							continue;
						}
					}
				}
			}
		}
	}
	output = grassfireSecondRunthrough(output); //connect the connected blobs 
	return output;
}

Mat CameraFeed::convertRGBtoGS(Mat inputFrame){
	Mat outputFrame;
	cvtColor(inputFrame, inputFrame, CV_RGB2GRAY);
	return inputFrame;
}

Mat CameraFeed::segmentImage(Mat inputFrame){
	Mat outputFrame;
	medianBlur(inputFrame, outputFrame, 3);
	thresholdImage(outputFrame, outputFrame, 0, 100, 0);
	imshow("WizardMinimap", outputFrame);
	imshow("input", inputFrame);
	return outputFrame;
}

void CameraFeed::thresholdImage(Mat inputImage, Mat outputImage, int minThreshold, int maxThreshold, int newValue){
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<uchar>(r, c) >= minThreshold &&
				inputImage.at<uchar>(r, c) < maxThreshold)
				outputImage.at<uchar>(r, c) = newValue;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);
		}
	}
}
void CameraFeed::thresholdImage(Mat inputImage, Mat outputImage, 
	int minThresholdOne, int maxThresholdOne, int newValueOne, 
	int minThresholdTwo, int maxThresholdTwo, int newValueTwo)
{
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<uchar>(r, c) >= minThresholdOne &&
				inputImage.at<uchar>(r, c) < maxThresholdOne)
				outputImage.at<uchar>(r, c) = newValueOne;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);
			
			if (inputImage.at<uchar>(r, c) >= minThresholdTwo &&
				inputImage.at<uchar>(r, c) < maxThresholdTwo)
				outputImage.at<uchar>(r, c) = newValueTwo;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);
		}
	}
}

void CameraFeed::thresholdImage(Mat inputImage, Mat outputImage, 
	int minThresholdOne, int maxThresholdOne, int newValueOne,
	int minThresholdTwo, int maxThresholdTwo, int newValueTwo,
	int minThresholdThree, int maxThresholdThree, int newValueThree)
{
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<uchar>(r, c) >= minThresholdOne &&
				inputImage.at<uchar>(r, c) < maxThresholdOne)
				outputImage.at<uchar>(r, c) = newValueOne;
			else if (true)
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);

			if (inputImage.at<uchar>(r, c) >= minThresholdTwo &&
				inputImage.at<uchar>(r, c) < maxThresholdTwo)
				outputImage.at<uchar>(r, c) = newValueTwo;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);

			if (inputImage.at<uchar>(r, c) >= minThresholdThree &&
				inputImage.at<uchar>(r, c) < maxThresholdThree)
				outputImage.at<uchar>(r, c) = newValueThree;
			else
				outputImage.at<uchar>(r, c) = inputImage.at<uchar>(r, c);
		}
	}
}

void CameraFeed::thresholdImageColor(Mat inputImage, Mat outputImage, int minThresholdRed, int maxThresholdRed, int newValueRed, 
																	  int minThresholdGreen, int maxThresholdGreen, int newValueGreen,
																	  int minThresholdBlue, int maxThresholdBlue, int newValueBlue){
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<Vec3b>(r, c)[0] > minThresholdBlue && inputImage.at<Vec3b>(r, c)[0] < maxThresholdBlue)
				outputImage.at<Vec3b>(r, c)[0] = newValueBlue;
			else
				outputImage.at<Vec3b>(r, c)[0] = inputImage.at<Vec3b>(r, c)[0];

			if (inputImage.at<Vec3b>(r, c)[1] >minThresholdGreen && inputImage.at<Vec3b>(r, c)[1] < maxThresholdGreen)
				outputImage.at<Vec3b>(r, c)[1] = newValueGreen;
			else
				outputImage.at<Vec3b>(r, c)[1] = inputImage.at<Vec3b>(r, c)[1];

			if (inputImage.at<Vec3b>(r, c)[2] > minThresholdRed && inputImage.at<Vec3b>(r, c)[2] < maxThresholdRed)
				outputImage.at<Vec3b>(r, c)[2] = newValueRed;
			else
				outputImage.at<Vec3b>(r, c)[2] = inputImage.at<Vec3b>(r, c)[2];
		}
	}
}

Mat CameraFeed::negateChannel(int channelNegate1, Mat frame)
{
	Mat newFrame = frame;
	Mat channel[3];
	split(newFrame, channel);
	channel[channelNegate1] = setZeroesInChannel(newFrame);
	merge(channel, 3, newFrame);
	return newFrame;
}

Mat CameraFeed::setZeroesInChannel(Mat inputFrame){
	Mat newFrame;
	inputFrame.copyTo(newFrame);
	return Mat::zeros(newFrame.rows, newFrame.cols, CV_8UC1);
}

//Function converting hue
double CameraFeed::getHue(double R, double G, double B) {
	double H = 0;
	double maximum = MAX(R, MAX(G, B)); //calculate the maximum of r, g and b.

	//formula to converting hue
	H = acos((0.5*((R - G) + (R - B)) /
		(sqrt((R - G)*(R - G) + (R - B)*(G - B)))));

	if (R == maximum) { //if the red value is equal to the maximum value of R, G and B,
		H = H;          //set H equal to the formula.
	}
	else if (G == maximum){ //if the green value is equal to the maximum of R, G and B,
		H = H;                //set H equal to the formula.
	}
	else{          //otherwise (if B is equal to the maximum),
		H = H;      //set H equal to the formula.
	}
	H = H * 60;

	if (B >= G) //if G is smaller than B,
		H = 360 - H;

	return H;
}

//Function converting saturation
double CameraFeed::getSaturation(double R, double G, double B) {
	double S = 0;
	if ((R + B + G) == 765) {     //if the summation of R, G and B is equal to 765,
		return 0;               //the saturation is set equal to 0.
	}
	else {
		double minimum = min(R, min(G, B));       //we find the minimum value of R, G and B.
		S = (1. - (3.*(minimum) / (R + G + B)));    //Formula used to calculate the saturation.

		if (S < 0) {  //if the saturation is less than 0.5,
			return 0.;   //the saturation is equal to 0.
		}
		else if (S >= 1) {    //if the saturation is larger or equal to 0.5,
			return 1.;           //the saturation is equal to 1.
		}
	}

	return S;
}

//Function converting intensity
int CameraFeed::getIntensity(int R, int G, int B) {
	int I = ((R + G + B) / 3.0); //the formula used to calculate the intensity.

	return I;
}

void CameraFeed::converRGBToHSV(Mat inputImage, Mat output) {
	Mat image, result;
	result = Mat::zeros(inputImage.rows, inputImage.cols, inputImage.type());
	image = inputImage; //Function that loads the image
	output.zeros(inputImage.rows, inputImage.cols, inputImage.type()); 

	if (inputImage.data && !inputImage.empty()){ //if there is some data to be loaded and the inputImage is not empty,
		for (int y = 0; y < inputImage.rows; y++){ //y starts at 0. When y is smaller than the inputImage rows, the loop keeps running.
			for (int x = 0; x < inputImage.cols; x++){ //x starts a 0. When x is smaller than the inputImage columns, the loop keeps running.
				result.at<Vec3b>(y, x)[0] = getHue(inputImage.at<Vec3b>(y, x)[2], //we have three channels at a RGB inputImage. Channel 2 is the red channel.
													inputImage.at<Vec3b>(y, x)[1], //channel 1 is the green channel
													inputImage.at<Vec3b>(y, x)[0]);//getHue also needs to know about getSaturation, therefore this function is included.;
				result.at<Vec3b>(y, x)[1] = getSaturation(inputImage.at<Vec3b>(y, x)[2], //convert the getSaturation output to a double, in order for the inputImage to be gray-scaled.
					inputImage.at<Vec3b>(y, x)[1],
					inputImage.at<Vec3b>(y, x)[0])*255.;
				result.at<Vec3b>(y, x)[2] = getIntensity(inputImage.at<Vec3b>(y, x)[2], //Vec3b gives 3 pixel values. This one gives the pixel values of the red pixel
					inputImage.at<Vec3b>(y, x)[1],
					inputImage.at<Vec3b>(y, x)[0]);
			}
		}
		output = result;
	}
}



