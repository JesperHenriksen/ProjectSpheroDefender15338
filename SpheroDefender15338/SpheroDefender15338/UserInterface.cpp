#include "UserInterface.h"
#include "opencv2\opencv.hpp"
#include "Minimap.h"

using namespace std;
using namespace cv;

Mat boomerang, icePatch, stone, sentry, wall; //Global variables for the spell images

UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}


void UserInterface::loadSpells() //Loads the images of the different spells
{
	boomerang = imread("BoomerangHObstacle.png", 1);
	icePatch = imread("IceHObstacle.png", 1);
	stone = imread("StoneHObstacle.png", 1);
	sentry = imread("ArcaneHObsracle.png", 1);
	wall = imread("WallHObstacle.png", 1);
}

Mat UserInterface::boomerangSpell(double xCoord, double yCoord, int angle)
{
	int direction = 0;
	direction = tan(angle -180); //opposite direction of the direction of the arrow
	
}
//
//Mat UserInterface::icePatchSpell()
//{
//
//}
//
//Mat UserInterface::stoneSpell()
//{
//
//}
//
//Mat UserInterface::sentrySpell()
//{
//
//}
//
Mat UserInterface::wallSpell(double xCoord, double yCoord, int angle)
{
	int direction = 0;
	direction = angle;


}
