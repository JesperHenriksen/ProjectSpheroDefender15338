#pragma once
class Sphero
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
		Returns the Movement Speed Scalar value of the Sphero.
	!*/
	double getMovementSpeed();
	/*!
		Sets the Movement Speed Scalar value of the Sphero
	!*/
	void setMovementSpeed(double newMovementSpeed);
	/*!
		Start tracking of sphero on the Battlefield. This starts a thread that continues sends Sphero coordinates.
	!*/
	void startSpheroTracking();
	/*!
		Turn the Sphero left.
	!*/
	void turnLeft();
	/*!
		Turn the Sphero right.
	!*/
	void turnRight();
private:
	int health; //health is the health of the sphero. At 0 the sphero looses the game
	int test; //DONT USE THIS  
	double movementSpeed; //A scalar for the movement speed. 1 is full speed and -1

};

