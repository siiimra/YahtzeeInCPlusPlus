#pragma once
#include <iostream>
#include "Scorecard.h"
#include <vector>
#include "Human.h"
#include "Computer.h"

using namespace std;


class Round {

	int* diceRoll;

public:
	Round();


	void rollDice(string name);
	void reRoll(string name, vector<bool>& rerolled);
	void displayDice();

	bool checkIsNumberInVector(const vector<int>& vec, int number);

	//computer logic functions
	vector<int> checkNotConsecutive(int* diceRoll, int countConsec);

	bool checkIfFullHouse(int* dice);

	//checks if there are 3 of the same numbers
	int checkIfAlmostFullHouse(int* dice);

	//checks if there are 2 pairs of number appearing twice
	vector<int> findAlmostFullHousePairs(int* dice);


	int checkIfAlmostThreeOfaKind(int* dice);

	vector<bool> shouldReroll(int* diceRoll, Scorecard& scorecard, bool human);

	int* getDice();
	void setDice(int dice, int diceNumber);

	~Round();


};