#include "SpheroControls.h"


SpheroControls::SpheroControls()
{
	movementSpeed = 1;
}


SpheroControls::~SpheroControls()
{
}

double SpheroControls::getMovementSpeed(){
	return movementSpeed;
}

void SpheroControls::setMovementSpeed(double newMovementSpeed){
	if (newMovementSpeed <= 1 || newMovementSpeed >= -1)
		movementSpeed = newMovementSpeed;
}

void SpheroControls::turnLeft(){}
void SpheroControls::turnRight(){}