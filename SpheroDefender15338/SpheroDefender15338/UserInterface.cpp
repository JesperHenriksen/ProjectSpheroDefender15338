#include "UserInterface.h"
#include "opencv2\opencv.hpp"
#include "Minimap.h"
#include <math.h>

using namespace std;
using namespace cv;



Mat menuLeft, menuTop, menu, menu2, boomerang, icePatch, stone, sentry, wall, battlefield; //Global variables for the spell images

UserInterface::UserInterface()
{

	boomerang = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/Obstacles/BoomerangHObstacle.png", 1);
	icePatch = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/Obstacles/IceHObstacle.png", 1);
	stone = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/Obstacles/StoneHObstacle.png", 1);
	sentry = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/Obstacles/ArcaneHObstacle.png", 1);
	wall = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/Obstacles/WallHObstacle.png", 1);
	menuLeft = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/ProgramLayers/MenuLeft.png", 1);
	menuTop = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/ProgramLayers/MenuTop.png", 1);
	battlefield = imread("../../../../../Google Drev/MTA15338/Project (1)/Design/ProgramLayers/Battlefield.png", 1);
}

Mat UserInterface::getBoomerang(){
	return boomerang;
}


Mat UserInterface::getIcePatch(){
	return icePatch;
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
	return menu;
}

UserInterface::~UserInterface()
{
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
    
	addLayer(menuTop, battlefield, menu);
	addLayer(menuLeft, menu, menu);
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


//void UserInterface::boomerangSpell(double xCoord, double yCoord, int angle)
//{
//	int direction = 0;
//	direction = tan(angle -180); //opposite direction of the direction of the arrow
//	
//}

//Mat UserInterface::icePatchSpell(double xCoord, double yCoord, int angle)
//{
//	int direction = 0;
//	direction = angle;
//
//	rotation(icePatch, angle, 0, 0);
//}

//void UserInterface::stoneSpell(double xCoord, double yCoord, int angle)
//{
//	int direction = 0;
//	direction = tan(angle -180); //opposite direction of the direction of the arrow
//}

//Mat UserInterface::sentrySpell()
//{
//
//}
//

//void UserInterface::wallSpell(double xCoord, double yCoord, int angle)
//{
//	int direction = 0;
//	direction = angle;
//
//	rotation(wall, angle, 0, 0);
//}
