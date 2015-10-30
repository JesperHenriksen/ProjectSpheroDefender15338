#include "opencv2\opencv.hpp"
#pragma once
class UserInterface
{
public:
	UserInterface();
	~UserInterface();
	void loadSpells();
	void boomerangSpell(double xCoord, double yCoord, int angle);
	//Mat icePatchSpell();
	//Mat stoneSpell();
	//Mat sentrySpell();
	void wallSpell(double xCoord, double yCoord, int angle);
};

