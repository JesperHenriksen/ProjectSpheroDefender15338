#include "Sphero.h"


Sphero::Sphero()
{
	health = 100;
	movementSpeed = 1;
}

Sphero::~Sphero()
{
}

int Sphero::getHealth(){
	return health;
}
void Sphero::setHealth(int newHealth){
	health = newHealth;
}
double Sphero::getMovementSpeed(){
	return movementSpeed;
}
void Sphero::setMovementSpeed(double newMovementSpeed){
	if (newMovementSpeed <= 1 || newMovementSpeed >= -1)
		movementSpeed = newMovementSpeed;
}

void Sphero::startSpheroTracking(){}
void Sphero::turnLeft(){}
void Sphero::turnRight(){}