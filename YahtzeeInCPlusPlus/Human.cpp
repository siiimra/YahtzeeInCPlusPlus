#include "Human.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Human::Human(string name1) : Player(name1) {
    //Welcomes human player to Yahtzee
    cout << "Welcome to Yahtzee, " << name1 << "!" << endl;



}


void Human::turn(Scorecard& scorecard, int roundNum, Round& round) {

	// Indicate that it is the human players first roll
	cout << "\nRoll 1\n";
	// Ask user if they would like to input their own dice
	cout << "Would you like to input your own dice? (y/n) ";
	// Char variable that holds user choice to input own dice or not
	char choice;
	// Get user input to see if they want intentional or random dice
	cin >> choice;

	// Input validation -- prompt for a valid choice if input is not y/Y or n/N
	while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
		cout << "Invalid choice, input Y or N: ";
		cin >> choice;
	}

	// If user chooses to input their own dice, move into this
	if (choice == 'Y' || choice == 'y') {
		// Variable that will hold custom dice value
		int diceChoice;
		// Move through five dice
		for (int i = 0; i < 5; i++) {
			// Prompt user to enter values of the five die
			cout << "Enter dice " << i + 1 << ": ";
			// Recieve custom dice input
			cin >> diceChoice;
			// Input validation -- prompt for valid input if user attempts to populate diceChoice with values less than 1
			// or greather than 6
			while (diceChoice < 1 || diceChoice > 6) {
				cout << "Invalid dice input. Dice can only be in range 1-6. ";
				cin >> diceChoice;
			}
			// populate the dice roll array with the custom values
			(round.getDice())[i] = diceChoice;
		}

	}
	else if (choice == 'N' || choice == 'n') {
		// Randomly generate and display 5 dice if user decides to not manually input die
		round.rollDice(name);
	}

	//Asks user if they would like to reroll dice after initial roll
	cout << "Would you like to change any of your dice? (y/n/? for help): ";
	// get input from user if they would like to keep or reroll dice
	cin >> choice;
	// input validation, prompt for valid input if the input is not y/Y, n/N, or ?
	while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' && choice != '?') {
		cout << "Incorrect input. Try again." << endl;
		cin >> choice;
	}

	//HELP MODE
	// If user inputs ?, enter help mode
	if (choice == '?') {
		cout << "\nHELP MODE" << endl << endl;
		// Display current dice user has
		round.displayDice(); 
		cout << endl;

		int highestPoints = scorecard.potentialPoints(round.getDice());
		cout << "Based on your current roll, you should fill " << scorecard.getCategory(highestPoints) << " because it will earn you the highest number of points. (" << scorecard.calcRunningScore(round.getDice(), highestPoints) << ")" << endl;
		round.shouldReroll(round.getDice(), scorecard, true);
		cout << "\nWould you like to change any of your dice? (y/n): ";
		cin >> choice;
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
			cout << "Incorrect input. Try again." << endl;
			cin >> choice;
		}
	}
	if (choice == 'y' || choice == 'Y') {
		cout << "\nRoll 2\n";
		round.reRoll(name);
		//Implementing third roll
		cout << "Would you like to change any of your dice? (y/n/? for help): ";
		//char inputDice;
		cin >> choice;
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' && choice != '?') {
			cout << "Incorrect input. Try again." << endl;
			cin >> choice;
		}

		//HELP MODE
		if (choice == '?') {
			cout << "\nHELP MODE" << endl << endl;
			round.displayDice();
			cout << endl;
			int highestPoints = scorecard.potentialPoints(round.getDice());
			if (highestPoints != -1 ){
				cout << "Based on your current roll, you should fill " << scorecard.getCategory(highestPoints) << " because it will earn you the highest number of points. (" << scorecard.calcRunningScore(round.getDice(), highestPoints) << ")" << endl;
			}
			round.shouldReroll(round.getDice(), scorecard, true);
			cout << "\nWould you like to change any of your dice? (y/n): ";
			cin >> choice;
			while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
				cout << "Incorrect input. Try again." << endl;
				cin >> choice;
			}
		}

		if (choice == 'y' || choice == 'Y') {
			cout << "\nRoll 3\n";
			round.reRoll(name);
		}
	}

	//Display scorecard after each player finishes rolling dice

	scorecard.displayAll();

	cout << endl;

	vector<int> displayGood;
	displayGood = scorecard.displayAvailable(round.getDice());



	//Ask which category the player would like to pursue
	int chooseCategory;
	cout << "\nChoose a category to fill (-2 for help, -1 if no category can be filled): ";
	cin >> chooseCategory;


	chooseCategory--;

	while (!(round.isNumberInVector(displayGood, chooseCategory)) && chooseCategory != -3 && chooseCategory != -2) {
		cout << "Please input a valid input. ";
		cin >> chooseCategory;
	}
	if (chooseCategory == -2) {
		cout << "\nHELP MODE\n";
		int highestPoints = scorecard.potentialPoints(round.getDice());
		cout << "\nBased on your current roll, you should fill " << scorecard.getCategory(highestPoints) << " because it will earn you the highest number of points. (" << scorecard.calcRunningScore(round.getDice(), highestPoints) << ")" << endl;
		cout << "\nChoose a category to fill (-3 if no category can be filled): ";
		cin >> chooseCategory;
		while (!(round.isNumberInVector(displayGood, chooseCategory)) && chooseCategory != -1) { 
			cout << "Please input a valid input. ";
			cin >> chooseCategory;
		}
	}
	//Running scores of both players
	int humanScore = 0;
	if (round.isNumberInVector(displayGood, chooseCategory)) {
		humanScore = scorecard.calcRunningScore(round.getDice(), chooseCategory);
		scorecard.updateScorecard(chooseCategory, name, humanScore, roundNum); 
	}

	setScore(scorecard.calcFinalScore(name));

	scorecard.displayAll();
}
