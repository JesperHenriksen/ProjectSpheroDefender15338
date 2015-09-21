#include <string>
#include <ctime>
using namespace std;
class Utility{
public:
	/*!
		Returns the leaderboard.
	!*/
	void getLeaderboad(){};
	/*!
		Returns the score value
	!*/
	int getScore(){
		return score;
	}
	/*!
		Returns the timer object
	!*/
	clock_t getTimer(){
		return timer;
	}
	/*!
		Resets the leaderboard.
	!*/
	void resetLeaderboard(){
		leaderboard lb;
		lb.score = 0;
		lb.name = "";
		lb.playerType = "";
	}
	/*!
		Resets the game.
	!*/
	virtual void resetGame(){}
	virtual void startGame(){}
	virtual void gameOver(){}

private:
	static struct leaderboard{
		int score;
		string name;
		string playerType;
	};
	int score;
	clock_t timer;
};