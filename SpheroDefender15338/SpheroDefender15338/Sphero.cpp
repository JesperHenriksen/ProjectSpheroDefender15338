#include "Sphero.h"


Sphero::Sphero()
{
	startingHealth = 100;
	currentHealth = startingHealth;
}

Sphero::~Sphero()
{
}

//Returns the current health of the sphero
int Sphero::getHealth(){
	return currentHealth;
}

//Checks if the sphero is dead
bool Sphero::isDead(){
	if (currentHealth <= 0)
		return true;
	else
		return false;
}

//Set the health of the sphero to the new health
void Sphero::setHealth(int newHealth){
	currentHealth = newHealth; //Assign the new health to the sphero's current health
}

//Kills of the sphero
void Sphero::death() {
	isDead();

	//Set movement speed and controls to 0 and lots of other stuff
	//movementSpeed = 0;
}

//Move these functions to SpheroControls and SpheroTracker (currently SpheroCoordinate)
