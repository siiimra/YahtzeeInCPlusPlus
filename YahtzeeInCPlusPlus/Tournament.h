#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Scorecard.h"
#include "Human.h"
#include "Computer.h"
using namespace std;

// aggregation and composition


class Tournament {
	// Composition - scorecard can not exist without a tournament
	Scorecard scorecard;

	// Aggregation - Human and computer can exist without a tournament
	Human* human;
	Computer* computer;

public:
	Tournament(Human& human, Computer& computer);
	void startGame();
	string toss();

};