#include "Computer.h"
#include <iostream>

Computer::Computer(string name1) : Player(name1) {}

void Computer::turn(Scorecard& scorecard, int roundNum, Round& round) {

	// Initialize computer score to 0
	int computerScore = 0;

	// Computer rolls 5 dice
	round.rollDice(name);

	// Vector that stores the dice that should be re-rolled
	vector<bool> diceToReroll = round.shouldReroll(round.getDice(), scorecard, false);

	// Bool variable that checks if there are ANY dice to reroll
	bool checkToReroll = false;

	// Set checkToReroll to true if diceToReroll has any true values
	for (int i = 0; i < 5; i++) {
		if (diceToReroll[i] == true) {
			checkToReroll = true;
			break;
		}
	}

	// If checkToReroll stays false, no need to reroll
	if (!(checkToReroll)) {
		cout << "No need to reroll. " << endl;
	}

	// Otherwise, announce & re-roll the dice that diceToReroll set to true
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
		// Announce new dice
		cout << "Dice rolled: ";
		for (int i = 0; i < 5; ++i) {
			cout << round.getDice()[i] << " ";
		}
		cout << endl;

		// Same logic as above to determine if second re-roll is needed

		// Set both variables to their default states
		diceToReroll = round.shouldReroll(round.getDice(), scorecard, false);
		checkToReroll = false;

		// Set checkToReroll to true if diceToReroll has any true values
		for (int i = 0; i < 5; i++) {
			if (diceToReroll[i] == true) {
				checkToReroll = true;
				break;
			}
		}

		// If checkToReroll stays false, no need to reroll
		if (!(checkToReroll)) {
			cout << "No need for second reroll. " << endl;
		}

		// Otherwise, announce & re-roll the dice that diceToReroll set to true
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
		}
		cout << "Dice rolled: ";
		for (int i = 0; i < 5; ++i) {
			cout << round.getDice()[i] << " ";
		}
		cout << endl;
	}


	// Displays categories tht can be filled
	vector<int> displayGood;
	displayGood = scorecard.displayAvailable(round.getDice());

	int highestPoints = scorecard.potentialPoints(round.getDice(), displayGood); 
	cout << "Based on the final roll, the computer will fill " << scorecard.getCategory(highestPoints) << " because it will earn it the highest number of points. (" << scorecard.calcRunningScore(round.getDice(), highestPoints) << ")" << endl;

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
