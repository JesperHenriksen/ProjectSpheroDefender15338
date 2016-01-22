#include "Points.h"
#include "math.h"


Points::Points(int xIn, int yIn, int zIn)
{
	x = xIn;
	y = yIn;
	z = zIn;
}


Points::~Points()
{
}

int Points::distanceToPoint(Points a){
	return sqrt(pow((double)x - a.x, 2) + pow((double)y - a.y, 2) + pow((double)z - a.z, 2));
}