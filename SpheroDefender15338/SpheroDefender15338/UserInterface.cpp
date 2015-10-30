//#include "UserInterface.h"
//#include "opencv2\opencv.hpp"
//#include "Minimap.h"
//#include <math.h>
//
//using namespace std;
//using namespace cv;
//
//
//Mat menuLeft, menuTop, boomerang, icePatch, stone, sentry, wall; //Global variables for the spell images
//
//UserInterface::UserInterface()
//{
//
//	boomerang = imread("BoomerangHObstacle.png", 1);
//	icePatch = imread("IceHObstacle.png", 1);
//	stone = imread("StoneHObstacle.png", 1);
//	sentry = imread("ArcaneHObsracle.png", 1);
//	wall = imread("WallHObstacle.png", 1);
//}
//
//
//UserInterface::~UserInterface()
//{
//}
//
//
//void UserInterface::rotation(Mat input, int degrees, int xOffset, int yOffset){
//	Mat rotatedImage(input.rows, input.cols, input.type());
//	double s = sin(degrees), c = cos(degrees);
//	int r0 = rotatedImage.rows / 2, c0 = rotatedImage.cols / 2;
//	for (int x = 0; x < rotatedImage.cols; x++){
//		for (int y = 0; y < rotatedImage.rows; y++){
//			int newYPixel = (int)r0 + yOffset - ((x - c0)*s) + ((y - r0)*c);
//			int newXPixel = (int)c0 + xOffset + ((x - c0)*c) + ((y - r0)*s);
//			if (newXPixel < 0 || newYPixel < 0 || newXPixel >= rotatedImage.cols || newYPixel >= rotatedImage.rows)
//				continue;
//			rotatedImage.at<uchar>(y, x) = input.at<uchar>(newYPixel, newXPixel);
//		}
//	}
//}
//
//
//void UserInterface::interfaceLayers()
//{
//	Mat dst;
//	double  alpha = 0.5, beta = 0;
//	//menuLeft = imread("MenuLeft.png", 1);//Loads the images of the different spells
//	menuTop = imread("MenuTop.png", 1);
//	//namedWindow("Wizard", 1);
//	//beta = (1.0 - alpha);
//	//addWeighted(menuTop, alpha, menuLeft, beta, 0.0, dst);
//	imshow("Wizard", menuTop);
//}
//
//
//void UserInterface::boomerangSpell(double xCoord, double yCoord, int angle)
//{
//	int direction = 0;
//	direction = tan(angle -180); //opposite direction of the direction of the arrow
//	
//}
////
////Mat UserInterface::icePatchSpell()
////{
////
////}
////
////Mat UserInterface::stoneSpell()
////{
////
////}
////
////Mat UserInterface::sentrySpell()
////{
////
////}
////
//void UserInterface::wallSpell(double xCoord, double yCoord, int angle)
//{
//	int direction = 0;
//	direction = angle;
//
//	rotation(wall, angle, 0, 0);
//}
