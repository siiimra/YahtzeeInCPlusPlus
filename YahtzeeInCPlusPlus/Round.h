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
	int humanTurn(Human& human, Scorecard& scorecard, int round);

	//computer logic functions
	vector<int> checkNotConsecutive(int* diceRoll, int countConsec);

	bool isFullHouse(int* dice);

	//checks if there are 3 of the same numbers
	int almostFullHouse(int* dice);

	//checks if there are 2 pairs of number appearing twice
	vector<int> almostFullHouse2(int* dice);


	int almostThreeOfaKind(int* dice);

	vector<bool> shouldReroll(int* diceRoll, Scorecard& scorecard);
	int computerTurn(Computer& computer, Scorecard& scorecard, int round);

};