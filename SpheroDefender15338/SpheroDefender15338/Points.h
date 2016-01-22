#pragma once
class Points
{
public:
	Points(int xIn, int yIn, int zIn);
	~Points();
	int distanceToPoint(Points a);
	int x = 0, y = 0, z = 0;
};

