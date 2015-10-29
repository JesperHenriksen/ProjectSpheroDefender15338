#include "opencv2\opencv.hpp"
#pragma once
class UserInterface
{
public:
	UserInterface();
	~UserInterface();
	void loadSpells();
	Mat boomerangSpell(double xCoord, double yCoord, int angle);
	//Mat icePatchSpell();
	//Mat stoneSpell();
	//Mat sentrySpell();
	Mat wallSpell(double xCoord, double yCoord, int angle);
};

