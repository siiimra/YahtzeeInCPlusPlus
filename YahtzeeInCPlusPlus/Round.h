#pragma once
#include <iostream>
#include "Scorecard.h"
#include <vector>
#include "Human.h"
#include "Computer.h"

using namespace std;


class Round {

	int diceRoll[5];

public:
	Round();
	string toss(string name1, string name2);
	void playRound(Human& human, Computer& computer, Scorecard& scorecard, int round);
	void rollDice(string name);
	void reRoll(string name);
	void displayDice();
	int humanTurn(Human& human, Scorecard& scorecard,int round);
	vector<bool> shouldReroll(int* diceRoll);
	int computerTurn(Computer& computer, Scorecard& scorecard, int round);
	
};