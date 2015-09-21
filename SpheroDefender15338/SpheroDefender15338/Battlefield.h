#pragma once
#pragma once
#include "Utility.h"
#include "SpheroCoordinate.h"
class Battlefield : public Utility
{
public:
	Battlefield();
	~Battlefield();

private:
	/*!
	Projects battlefield 
	!*/
	void projectBattlefield();
	/*!
	Detects if sphero gets hit
	!*/
	void doesSheroGetHit();
	/*!
	send continues sphero position
	!*/
	SpheroCoordinate sendContinuesSpheroPosition();
	/*!
	checks if shero is out of bounds
	!*/
	void spheroOutOfBounds(SpheroCoordinate);
};

