#pragma once
class SpheroControls
{
public:
	SpheroControls();
	~SpheroControls();

	/*!
	Returns the Movement Speed Scalar value of the Sphero.
	!*/
	double getMovementSpeed();
	/*!
	Sets the Movement Speed Scalar value of the Sphero
	!*/
	void setMovementSpeed(double newMovementSpeed);
	/*!
	Turn the Sphero left.
	!*/
	void turnLeft();
	/*!
	Turn the Sphero right.
	!*/
	void turnRight();

private:
	double movementSpeed; //A scalar for the movement speed. 1 is full speed and -1
};
