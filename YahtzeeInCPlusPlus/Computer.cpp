#include "Computer.h"
#include <iostream>

Computer::Computer(string name1) : Player(name1) {}

void Computer::turn(Scorecard& scorecard, int roundNum, Round& round) {
	int computerScore = 0;
	round.rollDice(name);
	//cin >> diceRoll[0] >> diceRoll[1] >> diceRoll[2] >> diceRoll[3] >> diceRoll[4];

	vector<bool> diceToReroll = round.shouldReroll(round.getDice(), scorecard, false);

	// Check if there are dice to reroll
	bool checkToReroll = false;

	for (int i = 0; i < 5; i++) {
		if (diceToReroll[i] == true) {
			checkToReroll = true;
			break;
		}
	}

	if (!(checkToReroll)) {
		cout << "No need to reroll. ";
	}
	else {
		cout << "Rerolling dice(s) ";
		for (int i = 0; i < 5; i++) {
			if (diceToReroll[i] == true) {
				cout << i + 1 << " ";
			}
		}
		cout << endl;

		for (int i = 0; i < 5; i++) {
			if (diceToReroll[i] == true) {
				round.getDice()[i] = rand() % 6 + 1;
			}
		}

		cout << "Dice rolled: ";
		for (int i = 0; i < 5; ++i) {
			cout << round.getDice()[i] << " ";
		}
		cout << endl;
		//starting second reroll

		diceToReroll = round.shouldReroll(round.getDice(), scorecard, false);
		checkToReroll = false;

		for (int i = 0; i < 5; i++) {
			if (diceToReroll[i] == true) {
				checkToReroll = true;
				break;
			}
		}
		if (!(checkToReroll)) {
			cout << "No need for second reroll. ";
		}
		else {
			cout << "Rerolling dice(s0 ";
			for (int i = 0; i < 5; i++) {
				if (diceToReroll[i] == true) {
					cout << i + 1 << " ";
				}
			}
			cout << endl;

			for (int i = 0; i < 5; i++) {
				if (diceToReroll[i] == true) {
					round.getDice()[i] = rand() % 6 + 1;
				}
			}
		}
		cout << "Dice rolled: ";
		for (int i = 0; i < 5; ++i) {
			cout << round.getDice()[i] << " ";
		}
		cout << endl;
	}

	scorecard.displayAll();

	cout << endl;


	//displays categories tht can be filled
	vector<int> displayGood;
	displayGood = scorecard.displayAvailable(round.getDice());

	int chosenCategory = -1;

	if (displayGood.empty()) {
		cout << "No categories can be filled. " << endl;
	}
	else {

		for (int i = 0; i < displayGood.size(); i++) {
			int score = 0;
			score = scorecard.calcRunningScore(round.getDice(), displayGood[i]);
			if (score >= computerScore) {
				computerScore = score;
				chosenCategory = displayGood[i];
			}
		}
		scorecard.updateScorecard(chosenCategory, name, computerScore, roundNum);
	}
	setScore(scorecard.calcFinalScore(name));
	scorecard.displayAll();
}
