#include "SpheroCoordinate.h"


SpheroCoordinate::SpheroCoordinate(int xCoord, int yCoord)
{
	setXCoord(xCoord);
	setYCoord(yCoord);
}


SpheroCoordinate::~SpheroCoordinate()
{
}

void SpheroCoordinate::setXCoord(int xCoord){
	this->xCoord = xCoord;
}

void SpheroCoordinate::setYCoord(int yCoord){
	this->yCoord = yCoord;
}

int SpheroCoordinate::getXCoord(){
	return this->xCoord;
}

int SpheroCoordinate::getYCoord(){
	return this->yCoord;
}