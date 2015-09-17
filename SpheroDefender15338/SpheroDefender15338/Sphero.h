#pragma once
class Sphero
{
public:
	
	Sphero();
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
		movementSpeed = newMovementSpeed;
	}
private:
	int health = 0;
	double movementSpeed = 1;

};

