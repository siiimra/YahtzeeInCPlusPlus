#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Player.h"
#include "Round.h"


using namespace std;

//Computer class inherits Player class.
//Player will recieve name of computer and default score 0

class Computer :public Player {

public:

	//Default constructor
	Computer(string name1 = "Computer");

	void turn(Scorecard& scorecard, int roundNum, Round& round);


}; 
