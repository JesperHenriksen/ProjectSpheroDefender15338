#pragma once
class Sphero
{
public:
	
	Sphero(){
		health = 100;
		movementSpeed = 1;
	};
	
	~Sphero();

	int getHealth(){
		return health;
	}
	void setHealth(int newHealth){
		health = newHealth;
	}
	double getMovementSpeed(){
		return movementSpeed;
	}
	void setMovementSpeed(double newMovementSpeed){
		if (newMovementSpeed <= 1 || newMovementSpeed >= -1)
			movementSpeed = newMovementSpeed;
	}

	void startSpheroTracking(){}
	void turnLeft(){}
	void turnRight(){}
private:
	int health; //health is the health of the sphero. At 0 the sphero looses the game
	double movementSpeed; //A scalar for the movement speed. 1 is full speed and -1

};

