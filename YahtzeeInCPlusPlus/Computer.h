#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "Player.h"

using namespace std;

//Computer class inherits Player class.
//Player will recieve name of computer and default score 0

class Computer :public Player {

public:

	//Default constructor
	Computer(string name1 = "Computer");


	//Function for dice rolling, where values are stored in vector
	void rollDice(vector<int>& dice);

	//Allows human to choose scoreboard category
	void chooseCategory();

}; 
