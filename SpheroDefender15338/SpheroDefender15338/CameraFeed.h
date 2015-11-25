#include "opencv2\opencv.hpp"
#pragma once
using namespace cv;
class CameraFeed
{
public:
	CameraFeed(int capture);
	~CameraFeed();
	VideoCapture cap;
	/**
	@brief
		Converts RGB Mat into a greyscale Mat
	@param inputFrame
		The Mat that should be converted to greyscale
	@return
		Returns the greyscale Mat
	*/
	Mat convertRGBtoGS(Mat inputFrame);
	void converRGBToHSV(Mat inputImage, Mat imageHue, Mat imageSat, Mat imageInt);
	Mat segmentImage(Mat inputFrame);
	Mat equalizeHistogram(Mat inputImage, Mat dst);
	void inputImageFixing(Mat inputImage, Mat dst, int minThreshold, int maxThreshold);
	/**
	@brief 
		Blob analysis using grassfire algorithm based on a x-1 and y-1 kernel and saves this new blob analysed in output.
	@param inputImage
		The input Mat matrix
	@param output
		The output Mat matrix
	*/
	void grassFire(Mat inputImage, Mat output);
	/**
	@brief
		Thresholds an Mat image based on a min value, max value with a new value.
	@param inputImage
		This is the input Mat image.
	@param outputImage
		This is the output Mat image.
	@param minThreshold
		Minimum value which the threshold should evaluate.
	@param maxThreshold
		Maximum value which the threshold should evaluate.
	@param newValue
		If pixel matches the threshold then replace the pixel value with the new value.		
	*/
	void thresholdImage(Mat inputImage, Mat outputImage, int minThreshold, int maxThreshold, int newValue);

	void thresholdImage(Mat inputImage, Mat outputImage, int minThresholdOne, int maxThresholdOne, int newValueOne,
														 int minThresholdTwo, int maxThresholdTwo, int newValueTwo);

	void thresholdImage(Mat inputImage, Mat outputImage, int minThresholdOne, int maxThresholdOne, int newValueOne,
														 int minThresholdTwo, int maxThresholdTwo, int newValueTwo,
														 int minThresholdThree, int maxThresholdThree, int newValueThree);
	/**
	 @brief 
		Returns an image from the webcam.
	 @param capture
		The webcam you want a picture from.
	 @return
		An image taken with the webcam.
	*/
	Mat getImageFromWebcam();
	/**
	 @brief
		Negates a given channel of a Mat
	 @param channelNegate
		The channel which should be negated
	 @param frame
		The input Mat frame.
	 @return
		Returns an image with a given channel negated 
	*/
	Mat negateChannel(int channelNegate, Mat frame);

	void thresholdHand(Mat inputImage, Mat outputImage, int minThresholdHue, int maxThresholdHue, int newHueValue);

	void thresholdImageColor(Mat inputImage, Mat outputImage, 
		int minThresholdRed, int maxThresholdRed, int newValueRed,
		int minThresholdGreen, int maxThresholdGreen, int newValueGreen,
		int minThresholdBlue, int maxThresholdBlue, int newValueBlue);



	/**
	@brief 
		Returns the most probable handsign.
	@param inputImage
		The input Mat variable.
	@return
		Returns 1 if sentry is the most probable, 
		Returns 2 if boulder is the most probable,
		Returns 3 if boomerang is the most probable,
		Returns 4 if wall is the most probable.
	*/
	int CameraFeed::chooseHandsign(Mat inputImage);
private:
	/**
	@brief
		Used by negateChannel to set zeroes in the given channel
	@param inputFrame
		Input Mat frame which the channel is negated.
	*/
	Mat setZeroesInChannel(Mat inputFrame);
	/**
	@brief
		Takes an inputImage checks if the blobs are connected
	@param inputImage
		inputImage is the image you want to change to be the connected blobs
	*/
	void grassfireSecondRunthrough(Mat inputImage);
	double getHue(double R, double G, double B); //Declare the functions
	double getSaturation(double R, double G, double B);
	int getIntensity(int R, int G, int B);
	int CameraFeed::getSentryProbability(Mat inputImage, int r, int c);
	int CameraFeed::getBoulderProbability(Mat inputImage, int r, int c);
	int CameraFeed::getWallProbability(Mat inputImage, int r, int c);
	int CameraFeed::getBoomerangProbability(Mat inputImage, int r, int c);

	int CameraFeed::getSentryProbability(Mat inputImage);
	int CameraFeed::getBoulderProbability(Mat inputImage);
	int CameraFeed::getWallProbability(Mat inputImage);
	int CameraFeed::getBoomerangProbability(Mat inputImage);
};

