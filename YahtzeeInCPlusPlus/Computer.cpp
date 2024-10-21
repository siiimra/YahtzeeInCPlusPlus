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
	bool manualInput = false;

	char choice;
	cout << "Would you like to roll your own dice? (y/n) ";

	cin >> choice;
	while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
		cout << "Invalid choice, input Y or N: ";
		cin >> choice;
	}
	if (choice == 'Y' || choice == 'y') {
		manualInput = true;
		// Variable that holds custom dice value
		int diceChoice;

		// Move through five dice
		for (int i = 0; i < 5; i++) {

			// Prompt user to enter values of the five die
			cout << "Enter dice " << i + 1 << ": ";

			// Recieve custom dice input
			cin >> diceChoice;

			// Input validation
			// Prompt for valid input if user attempts to populate diceChoice with values 
			// less than 1 or greather than 6
			while (diceChoice < 1 || diceChoice > 6) {
				cout << "Invalid dice input. Dice can only be in range 1-6. ";
				cin >> diceChoice;
			}

			// Populate the dice roll array with the custom values
			(round.setDice(diceChoice, i));
		}


	}

	// If user opts out of inputting custom dice..
	else if (choice == 'N' || choice == 'n') {
		// Randomly generate and display 5 dice
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
	}


	// Displays categories tht can be filled
	vector<int> displayGood;
	displayGood = scorecard.displayAvailable(round.getDice());

	cout << "Do you want to re-roll your dice? (y/n): ";
	cin >> choice;
	while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
		cout << "Invalid choice, input Y or N: ";
		cin >> choice;
	}
	if (choice == 'Y' || choice == 'y') {

		round.reRoll(name); // Assuming this calls your dice re-roll logic
		// After reroll, display updated categories
		displayGood = scorecard.displayAvailable(round.getDice());

		cout << "Do you want to re-roll your dice? (y/n): ";
		cin >> choice;
		while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
			cout << "Invalid choice, input Y or N: ";
			cin >> choice;

		}
		if (choice == 'Y' || choice == 'y') {

			round.reRoll(name); // Assuming this calls your dice re-roll logic
			// After reroll, display updated categories
			displayGood = scorecard.displayAvailable(round.getDice());
		}

	}

		// Announce the possible points each available category will give
		// Announce the possible points each available category will give
		int highestPoints = 0;
		int bestCategory = -1;

		// Iterate over available categories to find the best one based on points
		for (int category : displayGood) {
			int potentialPoints = scorecard.calcRunningScore(round.getDice(), category);
			if (potentialPoints > highestPoints) {
				highestPoints = potentialPoints;
				bestCategory = category;
			}
		}

		// Context-specific explanation of the computer's course of action
		if (bestCategory != -1) {
			cout << "Based on the final roll, the computer will fill "
				<< scorecard.getCategory(bestCategory)
				<< " because it will earn the highest number of points ("
				<< highestPoints << ")." << endl;

			// Update scorecard with the computer's chosen category
			scorecard.updateScorecard(bestCategory, name, highestPoints, roundNum);
		}
		else {
			cout << "No category can be filled" << endl;
		}

		// Set computers running score
		setScore(scorecard.calcFinalScore(name));

		// Display scorecard again
		scorecard.displayAll();
	}

