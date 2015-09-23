#pragma once
#include <string>
#include <ctime>

class Utility{
private:
	int score;
	clock_t timer;
	static struct leaderboard {
		int score = 0;
		char name = ' ';
		char playerType = ' ';
	};
public:
	/*!
		Returns the leaderboard.
	!*/
	void getLeaderboard(struct leaderboard);
	/*!
		Returns the score value
	!*/
	int getScore();
	/*!
		Returns the timer object
	!*/
	clock_t getTimer();
	/*!
		Resets the leaderboard.
	!*/
	void resetLeaderboard();
	/*!
		Resets the game.
	!*/
	virtual void resetGame() = 0;
	virtual void startGame() = 0;
	virtual void gameOver() = 0;


};