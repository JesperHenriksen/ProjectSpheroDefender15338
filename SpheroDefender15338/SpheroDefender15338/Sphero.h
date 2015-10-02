#pragma once
#include "SpheroCoordinate.h"
class Sphero : public SpheroCoordinate
{
public:
	Sphero();
	~Sphero();
	
	/*!
		Returns Health value of the Sphero
	!*/
	int getHealth();
	/*!
		Sets the Health value of the Sphero
	!*/
	void setHealth(int newHealth);
	/*!
		Kill of the sphero.
	!*/
	void death();
	/*!
		Checks if the sphero is dead
	!*/
	bool isDead();

private:
	int startingHealth; //The health of the sphero at the beginning.
	int currentHealth; //The health of the sphero during the game.
};

