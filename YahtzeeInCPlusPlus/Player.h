#pragma once
#include <iostream>
#include <string>

// delcaring the two classes a player uses
class Scorecard;
class Round;

using namespace std;

class Player {

protected:

	// Member variables that grab users name and score
	string name;
	int score;


public:
	// Default constructor for Player 
	Player(string name1 = "Human");

	// Selecter Function to get name
	string getName() const;

	// Mutator functions to set name  
	void setName(string name);

	// Selecter Function to get score
	int getScore() const;

	//Mutator functions to set score
	void setScore(int score);

	// Each child class has its own implementation of turn
	virtual void turn(Scorecard& scorecard, int roundNum, Round& round) = 0;
};
