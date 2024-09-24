#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

//Human class inherits Player class.
//Player will recieve a name and given score

class Human:public Player {

public:

	//Default constructor
	Human(string name1 = "Human");


	//Function for dice rolling, where values are stored in vector
	void rollDice(vector<int>& dice);

	//Allows human to choose scoreboard category
	void chooseCategory();

};