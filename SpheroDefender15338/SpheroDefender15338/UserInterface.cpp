#include "UserInterface.h"
#include "opencv2\opencv.hpp"
#include "Minimap.h"
#include <math.h>

using namespace std;
using namespace cv;

Mat menuLeft, menuLeftText, menuLeftTextMask, inverseMenuLeftTextMask, menuTop, menu, menu2, topMenuMask, topMenuInverseMask, boomerang, stone, sentry, wall, battlefield, leftMenuMask, inverseLeftMenuMask; //Global variables for the spell images

UserInterface::UserInterface()
{

	boomerang = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/Obstacles/BoomerangHObstacle.png", 1);
	stone = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/Obstacles/StoneHObstacle.png", 1);
	sentry = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/Obstacles/ArcaneHObstacle.png", 1);
	wall = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/Obstacles/WallHObstacle.png", 1);
	menuLeft = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/ProgramLayers/MenuLeft.png", 1);
	menuTop = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/ProgramLayers/MenuTop.png", 1);
	battlefield = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/ProgramLayers/Battlefield.png", 1);
	leftMenuMask = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/LeftMenuMask.png", 1);
	cvtColor(leftMenuMask, leftMenuMask, CV_RGB2GRAY);
	inverseLeftMenuMask = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/LeftMenuInverseMask.png", 1);
	cvtColor(inverseLeftMenuMask, inverseLeftMenuMask, CV_RGB2GRAY);
	topMenuMask = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/TopMenuMask.png", 1);
	cvtColor(topMenuMask, topMenuMask, CV_RGB2GRAY);
	topMenuInverseMask = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/TopMenuInverseMask.png", 1);
	cvtColor(topMenuInverseMask, topMenuInverseMask, CV_RGB2GRAY);
	menuLeftText = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/ProgramLayers/MenuLeftText.png", 1);
	menuLeftTextMask = imread("../../../../../Google Drev/MTA15338/Project(1)/Design/TextMenuMask.png", 0);
	//cvtColor(menuLeftTextMask, menuLeftTextMask, CV_RGB2GRAY);
	inverseMenuLeftTextMask = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/TextMenuMaskInverse.png", 1);
	cvtColor(inverseMenuLeftTextMask, inverseMenuLeftTextMask, CV_RGB2GRAY);
}

Mat UserInterface::getBoomerang(){
	return boomerang;
}

Mat UserInterface::getStone(){
	return stone;
}

Mat UserInterface::getSentry(){
	return sentry;
}

Mat UserInterface::getWall(){
	return wall;
}

Mat UserInterface::getMenu(){
	return menu2;
}

UserInterface::~UserInterface()
{
}

void UserInterface::getStartEndPoint(Mat input, double &startX, double &startY, double &endX, double &endY){

	double slope = 0;
	double b = 0;
	double x1 = 0;
	double y1 = 0;
	double x2 = 0;
	double y2 = 0;
	double x3 = 0;
	double y3 = 0;
	double x4 = 0;
	double y4 = 0;
	int triX = 7; //DE HER SKAL SKIFTES UD, JESPER!
	int triY = 8;
	int recX = 6;
	int recY = 6;

	//Finding the slope(a) of the vector between two points
	if ((triX - recX) != 0){
		slope = (triY - recY) / (triX - recX);
	}
	else {
		slope = 0;
	}

	//Finding the intersection point(b) of the vector
	b = triY - (slope*triX);

	if (slope != 0){
		//We want to find when the lines intersect with the fourth axis
		if (b >= 0 && b < input.rows){
			x4 = 0;
			y4 = b;
			//We want to find the intersection between the fourth axis and the first
			if (slope < 0 && ((0 - b) / slope > 0 && (0 - b) / slope < input.cols)) {
				y1 = 0;
				x1 = (y1 - b) / slope;
			}
			//We want to find the intersection between the fourth axis and the third
			else if (slope < 0 && ((0 - b) / slope > 0 && (input.rows - b) / slope < input.cols)) {
				y3 = input.rows;
				x3 = (input.rows - b) / slope;
			}
			//We want to find the intersection between the fourth axis and the second
			else if ((0 - b) / slope == input.cols && (slope*input.cols + b) < input.rows){
				x2 = input.cols;
				y2 = slope*input.cols + b;
			}
		}//If it does not intersect with the fourth axis we want to find when the lines intersect with the third axis
		else if ((input.rows - b) / slope > 0 && (input.rows - b) / slope < input.cols) {
			y3 = input.rows;
			x3 = (y3 - b) / slope;
			//We want to find the intersection between the third axis and the first
			if ((0 - b) / slope > 0 && (0 - b) / slope < input.cols){
				y1 = 0;
				x1 = (y1 - b) / slope;
			}
			//We want to find the intersection between the third axis and the second
			else if ((0 - b) / slope == input.cols && (slope*input.cols + b) < input.rows){
				x2 = input.cols;
				y2 = slope*input.cols + b;
			}
		}
		//If it does not intersect with the two previous axises, then it must intersect with the second axis
		else if ((0 - b) / slope == input.cols && (slope*input.cols + b) < input.rows){
			x2 = input.cols;
			y2 = slope*input.cols + b;
			//We want to find the intersection between the second axis and the first
			if ((0 - b) / slope > 0 && (0 - b) / slope < input.cols){
				y1 = 0;
				x1 = (y1 - b) / slope;
			}
		}
	}
	else
	{
		//All point have slope = 0.
		//We start by checking if there are vertical lines
		if (triX == recX){
			if (triY < recY){
				x3 = triX;
				y3 = input.rows;
			}
			else if (triY > recY){
				x1 = triX;
				y1 = 0;
			}
		}
		//Otherwise we find horizontal lines
		else {
			if (triY == recY){
				if (triX < recX){
					x2 = input.cols;
					y2 = b;
				}
				else if (triX > recX){
					x4 = 0;
					y4 = b;
				}
			}
		}
	}

	//We want to find the start points
	if (slope < 0){
		if (triY < recY && (0 - b) / slope > 0 && (0 - b) / slope < input.cols && b >= 0 && b < input.rows){  //Start point 4, end point 1
			startX = x4;
			startY = y4;
			endX = x1;
			endY = y1;
		}
		else if (triY > recY && (0 - b) / slope > 0 && (0 - b) / slope < input.cols && b >= 0 && b < input.rows){  //Start point 1, end point 4
			startX = x1;
			startY = y1;
			endX = x4;
			endY = y4;
		}
		else if (triY < recY && ((0 - b) / slope > 0 && (input.rows - b) / slope < input.cols) && ((0 - b) / slope == input.cols && (slope*input.cols + b) < input.rows)){  //Start point 3, end point 2
			startX = x3;
			startY = y3;
			endX = x2;
			endY = y2;
		}
		else if (triY > recY && ((0 - b) / slope > 0 && (input.rows - b) / slope < input.cols) && ((0 - b) / slope == input.cols && (slope*input.cols + b) < input.rows)){ //Startpoint 2, end point 3
			startX = x2;
			startY = y2;
			endX = x3;
			endY = y3;
		}
		else if (triY < recY && (input.rows - b) / slope > 0 && (input.rows - b) / slope < input.cols && (0 - b) / slope > 0 && (0 - b) / slope < input.cols){ //StartPoint 3, end point 1
			startX = x3;
			startY = y3;
			endX = x1;
			endY = y1;
		}
		else if (triY > recY && (input.rows - b) / slope > 0 && (input.rows - b) / slope < input.cols && (0 - b) / slope > 0 && (0 - b) / slope < input.cols){ //StartPoint 1, end point 3
			startX = x1;
			startY = y1;
			endX = x3;
			endY = y3;
		}
		else if (triY < recY && b >= 0 && b < input.rows && ((0 - b) / slope == input.cols || (slope*input.cols + b) < input.rows)){//Startpoint 4, end point 2
			startX = x4;
			startY = y4;
			endX = x2;
			endY = y2;
		}
		else if (triY > recY && b >= 0 && b < input.rows && ((0 - b) / slope == input.cols || (slope*input.cols + b) < input.rows)){//Startpoint 2, end point 4
			startX = x2;
			startY = y2;
			endX = x4;
			endY = y4;
		}
		else if (slope > 0){
			if (triY < recY && ((input.rows - b) / slope > 0 && (input.rows - b) / slope < input.cols) && (b >= 0 && b < input.rows)) {  //Startpoint 3, end point 4
				startX = x3;
				startY = y3;
				endX = x4;
				endY = y4;
			}
			else if (triY > recY && ((input.rows - b) / slope > 0 && (input.rows - b) / slope < input.cols) && (b >= 0 && b < input.rows)) {  //Startpoint 4, end point 3
				startX = x4;
				startY = y4;
				endX = x3;
				endY = y3;
			}
			else if (triY < recY && ((0 - b) / slope == input.cols && (slope*input.cols + b) < input.rows) && (slope < 0 && ((0 - b) / slope > 0 && (0 - b) / slope < input.cols))){ //StartPoint 2, end pint 1
				startX = x2;
				startY = y2;
				endX = x1;
				endY = y1;
			}
			else if (triY > recY && ((0 - b) / slope == input.cols && (slope*input.cols + b) < input.rows) && (slope < 0 && ((0 - b) / slope > 0 && (0 - b) / slope < input.cols))){ //StartPoint 1, end point 2
				startX = x1;
				startY = y1;
				endX = x2;
				endY = y2;
			}
			else if (triY < recY && (input.rows - b) / slope > 0 && (input.rows - b) / slope < input.cols && (0 - b) / slope > 0 && (0 - b) / slope < input.cols){ //StartPoint 3, end point 1
				startX = x3;
				startY = y3;
				endX = x1;
				endY = y1;
			}
			else if (triY > recY && (input.rows - b) / slope > 0 && (input.rows - b) / slope < input.cols && (0 - b) / slope > 0 && (0 - b) / slope < input.cols){ //StartPoint 1, end point 3
				startX = x1;
				startY = y1;
				endX = x3;
				endY = y3;
			}
			else  if (triY < recY && b >= 0 && b < input.rows && ((0 - b) / slope == input.cols || (slope*input.cols + b) < input.rows)){//Startpoint 4, end point 2
				startX = x4;
				startY = y4;
				endX = x2;
				endY = y2;
			}
			else if (triY > recY && b >= 0 && b < input.rows && ((0 - b) / slope == input.cols || (slope*input.cols + b) < input.rows)){//Startpoint 2, end point 4
				startX = x2;
				startY = y2;
				endX = x4;
				endY = y4;
			}
			else {
				if (triX > recX){
					startX = x4;
					startY = y4;
					endX = x2;
					endY = y2;
				}
				else if (triX < recX){
					startX = x2;
					startY = y2;
					endX = x4;
					endY = y4;
				}
				else if (triY > recY){
					startX = x1;
					startY = y1;
					endX = x3;
					endY = y3;
				}
				else if (triY < recY){
					startX = x3;
					startY = y3;
					endX = x1;
					endY = y1;
				}
			}
		}
	}
	cout << startX << "," << startY;
	cout << endX << "," << endY;
}

void UserInterface::rotation(Mat input, int degrees, int xOffset, int yOffset){
			Mat rotatedImage(input.rows, input.cols, input.type());
			double s = sin(degrees), c = cos(degrees);
			int r0 = rotatedImage.rows / 2, c0 = rotatedImage.cols / 2;
			for (int x = 0; x < rotatedImage.cols; x++){
				for (int y = 0; y < rotatedImage.rows; y++){
					int newYPixel = (int)r0 + yOffset - ((x - c0)*s) + ((y - r0)*c);
					int newXPixel = (int)c0 + xOffset + ((x - c0)*c) + ((y - r0)*s);
					if (newXPixel < 0 || newYPixel < 0 || newXPixel >= rotatedImage.cols || newYPixel >= rotatedImage.rows)
						continue;
					rotatedImage.at<uchar>(y, x) = input.at<uchar>(newYPixel, newXPixel);
				}
			}
		}


void UserInterface::interfaceLayers()
		{
			menuTop.copyTo(menu);
			add(battlefield, menuLeft, menuLeft, inverseLeftMenuMask, -1);
			add(menuLeft, menuLeft, menuLeft, leftMenuMask, -1);
			add(battlefield, menuTop, menuTop, topMenuInverseMask, -1);
			add(menuTop, menuTop, menuTop, topMenuMask, -1);
			//imshow("topmenu", menuTop);
			//imshow("leftmenu", menuLeft);
			addWeighted(menuTop, 0.85, menuLeft, 0.85, -120, menu);
			add(menu, menuLeftText, menuLeftText, inverseMenuLeftTextMask, -1);
			add(menuLeftText, menuLeftText, menu2, menuLeftTextMask, -1);
			addWeighted(menuLeftText, 1, menu, 0, -30, menu2);


		}

void UserInterface::addLayer(Mat input1, Mat input2, Mat output) { //Input images
			if (input1.data && !input1.empty()){ //if there is some data to be loaded and the image is not empty,
				for (int y = 0; y < input1.rows; ++y){ //y starts at 0. When y is smaller than the image rows, the loop keeps running.
					for (int x = 0; x < input1.cols; ++x){ //x starts a 0. When x is smaller than the image columns, the loop keeps running.

						if (input1.at<Vec3b>(y, x)[0] == 0){ //show Battlefield image
							output.at<Vec3b>(y, x)[0] = input2.at<Vec3b>(y, x)[0];
							output.at<Vec3b>(y, x)[1] = input2.at<Vec3b>(y, x)[1];
							output.at<Vec3b>(y, x)[2] = input2.at<Vec3b>(y, x)[2];
						}
						else { //show menus
							output.at<Vec3b>(y, x)[0] = input1.at<Vec3b>(y, x)[0];
							output.at<Vec3b>(y, x)[1] = input1.at<Vec3b>(y, x)[1];
							output.at<Vec3b>(y, x)[2] = input1.at<Vec3b>(y, x)[2];
						}
					}
				}
			}
		}



//void UserInterface::boomerangSpell(Mat boomerang, double xCoord, double yCoord, int angle)
//{
//	int direction = 0;
//	direction = tan(angle - 180); //opposite direction of the direction of the arrow
//}

//void UserInterface::stoneSpell(Mat input, double xCoord, double yCoord, int angle)
//{
//	int speed = 4;
//	double direction = angle;
//	getStartEndPoint(input, xCoord, yCoord);
//
//}

//void UserInterface::sentrySpell(Mat input, double xCoord, double yCoord, int angle)
//{
//	int direction = 0;
//}

//void UserInterface::wallSpell(Mat wall, double xCoord, double yCoord, int angle)
//{
//	int direction = 0;
//	direction = angle;
//	rotation(wall, angle, xCoord, yCoord);
//}
