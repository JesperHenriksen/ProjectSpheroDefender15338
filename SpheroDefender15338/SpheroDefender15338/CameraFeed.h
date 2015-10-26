#include "opencv2/opencv.hpp"
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
		Returns the angle value in degrees of the Arrow on the Minimap
	@param inputImage
		The input Mat image
	@param thresholdMin
		The pixel value of the back of the arrow.
	@param thresholdMax
		The pixel value of the front of the arrow.
	@return
		Returns the value of the angle in a double variable
	*/
	double getAngleOfArrow(Mat inputImage, int thresholdMin, int thresholdMax);
	void placeSpell(Mat inputFrame, int thresholdMin, int thresholdMax);
	/**
	@brief
		Converts RGB Mat into a greyscale Mat
	@param inputFrame
		The Mat that should be converted to greyscale
	@return
		Returns the greyscale Mat
	*/
	Mat convertRGBtoGS(Mat inputFrame);
	Mat segmentImage(Mat inputFrame);
	/**
	@brief 
		Blob analysis using grassfire algorithm based on a x-1 and y-1 kernel and saves this new blob analysed in output.
	@param inputImage
		The input Mat matrix
	@param output
		The output Mat matrix
	*/
	Mat grassFire(Mat inputImage);
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
	void CameraFeed::thresholdImageColor(Mat inputImage, Mat outputImage, int minThresholdRed, int maxThresholdRed, int newValueRed,
		int minThresholdGreen, int maxThresholdGreen, int newValueGreen,
		int minThresholdBlue, int maxThresholdBlue, int newValueBlue);
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
	Mat CameraFeed::grassfireSecondRunthrough(Mat inputImage);
};

