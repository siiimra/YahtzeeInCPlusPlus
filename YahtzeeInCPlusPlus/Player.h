#pragma once
#include <iostream>
#include <string>

using namespace std;

class Player {

protected:

	//Member variables that grab users name and score
	string name;
	int score;

public:
	//Default constructor for Player 
	Player(string name1 = "Computer");

	// Selecter Functions
	string getName() const;

	int getScore() const;

	//Mutator functions
	void setName(string name);

	void setScore(int score);

};
