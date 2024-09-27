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
	Player(string name1 = "Human");

	// Selecter Functions to get name and score
	string getName() const;

	int getScore() const;

	//Mutator functions to set name and score
	void setName(string name);

	void setScore(int score);

};
