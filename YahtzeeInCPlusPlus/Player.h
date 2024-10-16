#pragma once
#include <iostream>
#include <string>
#include "Scorecard.h"
#include "Round.h"

using namespace std;

class Player {

protected:

	//Member variables that grab users name and score
	string name;
	int score;


public:
	//Default constructor for Player 
	Player(string name1 = "Human");

	// Selecter Functions to get name and score
	string getName() const;

	int getScore() const;

	//Mutator functions to set name and score
	void setName(string name);

	void setScore(int score);

	//each child class has its own implementation of turn
	virtual void turn(Scorecard& scorecard, int roundNum, Round& round) = 0;
};
