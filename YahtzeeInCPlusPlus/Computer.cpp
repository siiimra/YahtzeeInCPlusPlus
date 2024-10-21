#include "Computer.h"
#include <iostream>

/* *********************************************************************
Function Name: Computer (Constructor)
Purpose: To initialize a new Computer player object.
Parameters:
	- name1 (string): The name of the player being created. It is passed by value.
Return Value: None (constructor)
Algorithm:
	1) Call the base class constructor to initialize the player.
Reference: None
**********************************************************************/

Computer::Computer(string name1) : Player(name1) {}

/* *********************************************************************
Function Name: turn
Purpose: To handle the computer player's turn, including rolling and re-rolling dice, and choosing a category to maximize points.
Parameters:
	- scorecard (Scorecard&): A reference to the scorecard object. It is modified to update scores and categories filled during the computer's turn.
	- roundNum (int): The current round number.
	- round (Round&): A reference to the round object that manages dice rolls and re-rolls.
Return Value: None
Algorithm:
	1) Roll all 5 dice and determine which ones should be re-rolled to maximize points.
	2) Re-roll dice as suggested by the shouldReroll function up to two times if beneficial.
	3) Display the available categories and determine which category yields the highest points.
	4) Update the scorecard with the chosen category and set the computer's running score.
	5) Display the updated scorecard.
Reference: None
**********************************************************************/

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
		// Annonunce which dice numbers are going to be re-rolled
		cout << "Rerolling dice(s) ";
		for (int i = 0; i < 5; i++) {
			if (diceToReroll[i] == true) {
				cout << i + 1 << " ";
			}
		}
		cout << endl;

		// Generate random numbers for dice that need to be rerolled
		for (int i = 0; i < 5; i++) {
			if (diceToReroll[i] == true) {
				round.setDice(rand() % 6 + 1, i);
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
					round.setDice(rand() % 6 + 1, i);
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


	// Announce the possible points each available category will give
	int highestPoints = scorecard.getPotentialPoints(round.getDice(), displayGood);

	// Context specific explanation of the computers course of action
	cout << "Based on the final roll, the computer will fill " 
		<< scorecard.getCategory(highestPoints) 
		<< " because it will earn it the highest number of points. (" 
		<< scorecard.calcRunningScore(round.getDice(), highestPoints) 
		<< ")" << endl;

	// Variable that holds which category computer will pick
	int chosenCategory = -1;


	if (displayGood.empty()) {
		cout << "No categories can be filled. " << endl;
	}

	else {
		// Go through available categories and pick the one giving the highest points
		for (int i = 0; i < displayGood.size(); i++) {
			int score = 0;
			score = scorecard.calcRunningScore(round.getDice(), displayGood[i]);
			if (score >= computerScore) {
				computerScore = score;
				chosenCategory = displayGood[i];
			}
		}
		// Update scorecard with computers chosen category
		scorecard.updateScorecard(chosenCategory, name, computerScore, roundNum);
	}
	// Set computers running score
	setScore(scorecard.calcFinalScore(name));

	// Display scorecard again
	scorecard.displayAll();
}
