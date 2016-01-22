#include "CameraFeed.h"
#include "Points.h"
#include "opencv2/opencv.hpp"
#include "math.h"

using namespace cv;
using namespace std;
double PI = 3.14159;

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

void CameraFeed::thresholdGrassfireID(Mat inputGrassfire, Mat &output){

	int maxCount = 0, maxCountID = 0;
	int currentCount = 0;
	Mat bob = Mat::zeros(inputGrassfire.rows, inputGrassfire.cols, inputGrassfire.type());
	for (int ID = 0; ID < 30; ID++) {
		for (int y = 1; y < inputGrassfire.rows; y++) { //runs through the pixels
			for (int x = 1; x < inputGrassfire.cols; x++) {
				if (ID == inputGrassfire.at<uchar>(y, x)){
					currentCount++;
					if (currentCount > maxCount){
						maxCount = currentCount;
						maxCountID = ID;
					}
				}
			}
		}
	}
	for (int y = 1; y < inputGrassfire.rows; y++) { //runs through the pixels
		for (int x = 1; x < inputGrassfire.cols; x++) {
			if (maxCountID == inputGrassfire.at<uchar>(y, x)){
				bob.at<uchar>(y, x) = 1;
			}
		}
	}
	output = output.mul(bob);
}

void CameraFeed::subtractImage(Mat inputImage, Mat background, Mat output){
	int value = 0;
	for (int y = 0; y < inputImage.rows; y++) { 
		for (int x = 0; x < inputImage.cols; x++) {
			output.at<Vec3b>(y, x)[0] = abs(inputImage.at<Vec3b>(y, x)[0] - background.at<Vec3b>(y, x)[0]);
			output.at<Vec3b>(y, x)[1] = abs(inputImage.at<Vec3b>(y, x)[1] - background.at<Vec3b>(y, x)[1]);
			output.at<Vec3b>(y, x)[2] = abs(inputImage.at<Vec3b>(y, x)[2] - background.at<Vec3b>(y, x)[2]);
		}
	}
}

void CameraFeed::grassFire(Mat inputImage, Mat output){
	int currentID = 1;
	for (int y = 1; y < inputImage.rows; y++) { //runs through the pixels
		for (int x = 1; x < inputImage.cols; x++) {
			//if there is informations in the input pixel and
			if (inputImage.at<uchar>(y, x) > 60) {
				if (output.at<uchar>(y - 1, x) != 0){
					output.at<uchar>(y, x) = output.at<uchar>(y - 1, x); // set the current pixel value to the north pixel value
				}
				if (output.at<uchar>(y, x - 1) != 0) {
					output.at<uchar>(y, x) = output.at<uchar>(y, x - 1); // set the current pixel value to the value of the x
				}
				if (output.at<uchar>(y, x) == 0) { //if there is no information in the north pixel or the east pixel 
					output.at<uchar>(y, x) = currentID; //otherwise set the pixel to the current id
					currentID ++;//increase id
				}
			}
		}
	}

	//give the same ID in the connected blobs with forward loop followed by a backwards loop
	//forward loop
	for (int y = 1; y < inputImage.rows - 2 ; y++) { //runs through the pixels
		for (int x = 1; x < inputImage.cols - 2; x++) {
			//if there is informations in the input pixel
			if (output.at<uchar>(y, x) != 0) {
				//west
				if (output.at<uchar>(y, x - 1) != 0) { // if west pixel value is NOT equal to 0
					if (output.at<uchar>(y, x - 1) < output.at<uchar>(y, x)){ // if west pixel value is smaller than current pixel value
						output.at<uchar>(y, x) = output.at<uchar>(y, x - 1); // set the current pixel value to the value of West
					}
					else{
						output.at<uchar>(y, x - 1) = output.at<uchar>(y, x); // set west pixel value to the value of current pixel
					}
				}
				//north west
				if (output.at<uchar>(y - 1, x - 1) != 0) {// if north west pixel value is NOT equal to 0
					if (output.at<uchar>(y - 1, x - 1) < output.at<uchar>(y, x)) { // if north west pixel value is smaller than current pixel value
						output.at<uchar>(y, x) = output.at<uchar>(y - 1, x - 1); // set the current pixel value to the value of north west
					}
					else{
						output.at<uchar>(y - 1, x - 1) = output.at<uchar>(y, x); //set north west pixel value to the value of current pixel
					}
				}
				//north
				if (output.at<uchar>(y - 1, x) != 0) { // if north pixel value is NOT equal to 0
					if (output.at<uchar>(y - 1, x) < output.at<uchar>(y, x)) { // if north pixel value is smaller than current pixel value
						output.at<uchar>(y, x) = output.at<uchar>(y - 1, x); // set the current pixel value to the value of north
					}
					else{
						output.at<uchar>(y - 1, x) = output.at<uchar>(y, x); // set north pixel value to the value of current pixel
					}
				}
				//north east
				if (output.at<uchar>(y - 1, x + 1) != 0) { // if north east pixel value is NOT equal to 0
					if (output.at<uchar>(y - 1, x + 1) < output.at<uchar>(y, x)) { // if north east pixel value is smaller than current pixel value
						output.at<uchar>(y, x) = output.at<uchar>(y - 1, x + 1); // set the current pixel value to the value of north east
					}
					else{
						output.at<uchar>(y - 1, x + 1) = output.at<uchar>(y, x); //set north east value to current pixel value
					}
				}
			}
		}
	}
	//backwards loop
	for (int y = output.rows - 2; y > 1; y--) { //runs through the pixels backwards
		for (int x = output.cols - 2; x > 1; x--) {
			if (output.at<uchar>(y, x) != 0){
				//east
				if (output.at<uchar>(y, x + 1) != 0){ // if east pixel value is NOT equal to 0
					if (output.at<uchar>(y, x + 1) < output.at<uchar>(y, x)) // if east pixel value is smaller than current pixel value
						output.at<uchar>(y, x) = output.at<uchar>(y, x + 1); // set the current pixel value to the value of east
					else
						output.at<uchar>(y, x + 1) = output.at<uchar>(y, x); // set value of east to the current pixel value
				}
				//south east
				if (output.at<uchar>(y + 1, x + 1) != 0) { // if south east pixel value is NOT equal to 0
					if (output.at<uchar>(y + 1, x + 1) < output.at<uchar>(y, x)) // if south east pixel value is smaller than current pixel value
						output.at<uchar>(y, x) = output.at<uchar>(y + 1, x + 1); // set the current pixel value to the value of south east
					else
						output.at<uchar>(y + 1, x + 1) = output.at<uchar>(y, x); // set value of south east to the current pixel value
				}
				//south
				if (output.at<uchar>(y + 1, x) != 0) { // if south pixel value is NOT equal to 0
					if (output.at<uchar>(y + 1, x) < output.at<uchar>(y, x)) // if south pixel value is smaller than current pixel value
						output.at<uchar>(y, x) = output.at<uchar>(y + 1, x); // set the current pixel value to the value of south 
					else
						output.at<uchar>(y + 1, x) = output.at<uchar>(y, x); // set value of south to the current pixel value
				}
				//south west
				if (output.at<uchar>(y + 1, x - 1) != 0) { // if south west pixel value is NOT equal to 0
					if (output.at<uchar>(y + 1, x - 1) < output.at<uchar>(y, x)) // if south west pixel value is smaller than current pixel value
						output.at<uchar>(y, x) = output.at<uchar>(y + 1, x - 1); // set the current pixel value to the value of south west
					else
						output.at<uchar>(y + 1, x - 1) = output.at<uchar>(y, x); // set value of south west to the current pixel value
				}
			}
		}
	}
}


void CameraFeed::getHeightAndWidth(Mat inputImage, double &height, double &width){
	int maxRow = 0, minRow = 0;
	int maxCol = 0, minCol = 0;
	bool firstEncounter = true;
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<uchar>(r,c) > 60){
				if (firstEncounter){
					minRow = r;
					maxRow = r;
					minCol = c;
					maxCol = c;
					firstEncounter = false;
				}
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
	width = maxCol - minCol;
	height = maxRow - minRow;
}

int CameraFeed::getPixelAmountAndGravity(Mat inputImage, double &gravityX, double &gravityY){
	int pixelAmount = 0, tempX = 0, tempY = 0;
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<uchar>(r, c) == 255){
				tempX += c;
				tempY += r;
				pixelAmount++;
			}
		}
	} 
	if (pixelAmount != 0){
		gravityX = tempX / pixelAmount;
		gravityY = tempY / pixelAmount;
	}
	return pixelAmount;
}

double CameraFeed::getCircularity(Mat inputImage) {
	int numberOfPixels = 0, numberOfPixelsInEdge = 0;
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (r - 1 >= 0 && c - 1 >= 0 && r + 1 <= 480 && c <= 640){
				if (inputImage.at<uchar>(r, c) == 255) {
					numberOfPixels++;
					if (inputImage.at<uchar>(r - 1, c) != 255){
						numberOfPixelsInEdge++;
						continue;
					}
					if (inputImage.at<uchar>(r + 1, c) != 255){
						numberOfPixelsInEdge++;
						continue;
					}
					if (inputImage.at<uchar>(r, c - 1) != 255){
						numberOfPixelsInEdge++;
						continue;
					}
					if (inputImage.at<uchar>(r, c + 1) != 255){
						numberOfPixelsInEdge++;
						continue;
					}
				}
			}
		}
	}
	double result = 0;
	if (numberOfPixels != 0){
		result = numberOfPixelsInEdge / (2 * sqrt(PI*numberOfPixels));
	}
	result *= 50;
	return result;
}

int CameraFeed::chooseHandsign(Mat inputImage){

	double height = 0, width = 0;
	int blobPixelAmount = 0;
	double gravityX = 0, gravityY = 0;
	blobPixelAmount = getPixelAmountAndGravity(inputImage, gravityX, gravityY);
	getHeightAndWidth(inputImage, height, width);
	double filledPercentage = blobPixelAmount / (height*width);
	double circularity = 0;
	circularity = getCircularity(inputImage);
	//gravityX = gravityX / width;
	//gravityY = gravityY / height;
	double HW = width / height;
	filledPercentage = filledPercentage * 100;
	HW = HW * 70;
	int currentX = filledPercentage, currentY = HW, currentZ = circularity;
	//static values for different handsigns
	Points wall(74, 47, 55), stone(70, 70, 52), boomerang(44, 65, 66), sentry(60, 27, 68);
	Points currentPoint(currentX, currentY, currentZ);
	int distanceWall = abs(wall.distanceToPoint(currentPoint));
	int distanceStone = abs(stone.distanceToPoint(currentPoint));
	int distanceSentry = abs(sentry.distanceToPoint(currentPoint));
	int distanceBoomerang = abs(boomerang.distanceToPoint(currentPoint));
	
	int shortestDistance[4] = {
		distanceStone,
		distanceWall,
		distanceBoomerang,
		distanceSentry
	};
	int handsignArray[4] = {1,2,3,4};
	for (int j = 0; j < 3; j++){
		for (int i = 0; i < 3; i++){
			if (shortestDistance[i] > shortestDistance[i + 1]) {
				int temp = shortestDistance[i];
				shortestDistance[i] = shortestDistance[i + 1];
				shortestDistance[i + 1] = temp;
				int temp2 = handsignArray[i];
				handsignArray[i] = handsignArray[i + 1];
				handsignArray[i + 1] = temp2;
			}
		}
	}
	cout << /*distanceWall << " " << distanceStone << " " << distanceSentry << " " << distanceBoomerang << "\n" <<
		shortestDistance[0] << " " << shortestDistance[1] << " " << shortestDistance[2] << " " << shortestDistance[3] << "\n" <<
		handsignArray[0] << " " << handsignArray[1] << " " << handsignArray[2] << " " << handsignArray[3] << "\n" <<*/
		"\nFilledPercent " << filledPercentage << "\nHW " << HW << "\n" <<
		"circularity " << circularity << "\n";
	if (shortestDistance[0] < 15 && shortestDistance[0] >= 0){
		return handsignArray[0];
	} else
		return 0;
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

void CameraFeed::thresholdImage(Mat inputImage, Mat outputImage, 
	int minThreshold, int maxThreshold, int newValue){
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
	int minThresholdThree, int maxThresholdThree, int newValueThree){
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

void CameraFeed::thresholdImageColor(Mat inputImage, Mat outputImage, 
	int minThresholdRed, int maxThresholdRed, int newValueRed, 
	int minThresholdGreen, int maxThresholdGreen, int newValueGreen,
	int minThresholdBlue, int maxThresholdBlue, int newValueBlue) 
{
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

void CameraFeed::thresholdHand(Mat inputImage, Mat outputImage,
	int minThresholdHue, int maxThresholdHue, int newValueHue)
{
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<Vec3b>(r, c)[0] >= minThresholdHue && 
				inputImage.at<Vec3b>(r, c)[0] < maxThresholdHue &&
				inputImage.at<Vec3b>(r, c)[1] > 30 &&
				inputImage.at<Vec3b>(r, c)[2] > 30 && inputImage.at<Vec3b>(r, c)[2] < 230)
			{
				outputImage.at<Vec3b>(r, c)[0] = newValueHue;
				outputImage.at<Vec3b>(r, c)[1] = newValueHue;
				outputImage.at<Vec3b>(r, c)[2] = newValueHue;

			}
			else{
				outputImage.at<Vec3b>(r, c)[0] = 0; //inputImage.at<Vec3b>(r, c)[0];
				outputImage.at<Vec3b>(r, c)[1] = 0; // inputImage.at<Vec3b>(r, c)[1];
				outputImage.at<Vec3b>(r, c)[2] = 0; //inputImage.at<Vec3b>(r, c)[2];			
			}
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
	int i = getIntensity(R,G,B);
	//formula to converting hue
	H = acos((0.5*((R - G) + (R - B)) /
		(sqrt((R - G)*(R - G) + (R - B)*(G - B)))));

	if (R == i) { //if the red value is equal to the maximum value of R, G and B,
		H = H;          //set H equal to the formula.
	}
	else if (G == i){ //if the green value is equal to the maximum of R, G and B,
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

void CameraFeed::converRGBToHSV(Mat inputImage, Mat imageHue, Mat imageSat, Mat imageInt) {
	Mat image, result;
	result = Mat::zeros(inputImage.rows, inputImage.cols, inputImage.type());
	image = inputImage; //Function that loads the image

	if (image.data && !image.empty()){ //if there is some data to be loaded and the image is not empty,
		for (int y = 0; y < image.rows; ++y){ //y starts at 0. When y is smaller than the image rows, the loop keeps running.
			for (int x = 0; x < image.cols; ++x){ //x starts a 0. When x is smaller than the image columns, the loop keeps running.
				double satVal = getSaturation(image.at<Vec3b>(y, x)[2], //convert the getSaturation output to a double, in order for the image to be gray-scaled.
					image.at<Vec3b>(y, x)[1],
					image.at<Vec3b>(y, x)[0])*255.;

				double satHue = getHue(image.at<Vec3b>(y, x)[2], //we have three channels at a RGB image. Channel 2 is the red channel.
					image.at<Vec3b>(y, x)[1], //channel 1 is the green channel
					image.at<Vec3b>(y, x)[0]//channel 0 is the blue channel
					);//getHue also needs to know about getSaturation, therefore this function is included.

				imageHue.at<uchar>(y, x) = satHue;
				imageSat.at<uchar>(y, x) = satVal;
				imageInt.at<uchar>(y, x) = getIntensity(image.at<Vec3b>(y, x)[2], //Vec3b gives 3 pixel values. This one gives the pixel values of the red pixel
					image.at<Vec3b>(y, x)[1],
					image.at<Vec3b>(y, x)[0]);
			}
		}
	}
}