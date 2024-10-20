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
			(round.setDice(diceChoice, i));
		}

	}
	else if (choice == 'N' || choice == 'n') {
		// Randomly generate and display 5 dice if user decides to not manually input die
		round.rollDice(name);
	}

	//Asks user if they would like to reroll dice after initial roll
	cout << "Would you like to change any of your dice? (y/n/? for help): ";
	// Get input from user if they would like to keep or reroll dice
	cin >> choice;
	// Input validation, prompt for valid input if the input is not y/Y, n/N, or ?
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

		// Variable that holds the category highest potential points earned, returned by potential points function
		int highestPoints = scorecard.potentialPoints(round.getDice());
		// Suggests user which category to fill based on current roll based on the highest points variable and output the potential points
		cout << "Based on your current roll, you should fill " << scorecard.getCategory(highestPoints) << " because it will earn you the highest number of points. (" << scorecard.calcRunningScore(round.getDice(), highestPoints) << ")" << endl;
		
		// If more points can potentially be earned, use shouldReroll human functionalities to suggest which dice to re-roll and which category
		// to aim for
		round.shouldReroll(round.getDice(), scorecard, true);

		// Ask the user if they would like to change any dice
		cout << "\nWould you like to change any of your dice? (y/n): ";
		// Recieve user input -- see if human wants to re-roll or stand
		cin >> choice;
		// Input validation if human inputs anything other than y/Y, n/N
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
			cout << "Incorrect input. Try again." << endl;
			cin >> choice;
		}
	}

	// Go in for second roll if human decides to re-roll
	if (choice == 'y' || choice == 'Y') {
		cout << "\nRoll 2\n";
		// Display dice after asking user for intentional or random regeneration of dice for each dice
		round.reRoll(name);
		// Asks user if they would like to try for a third re roll
		cout << "Would you like to change any of your dice? (y/n/? for help): ";
		//char inputDice;
		cin >> choice;
		// Input validation, prompt for valid input if the input is not y/Y, n/N, or ?
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' && choice != '?') {
			cout << "Incorrect input. Try again." << endl;
			cin >> choice;
		}

		//HELP MODE
		if (choice == '?') {
			cout << "\nHELP MODE" << endl << endl;
			// Display current dice user has
			round.displayDice();
			cout << endl;
			// Variable that holds the category highest potential points earned, returned by potential points function
			int highestPoints = scorecard.potentialPoints(round.getDice());
			if (highestPoints != -1 ){
				// Suggests user which category to fill based on current roll based on the highest points variable and output the potential points
				cout << "Based on your current roll, you should fill " << scorecard.getCategory(highestPoints) << " because it will earn you the highest number of points. (" << scorecard.calcRunningScore(round.getDice(), highestPoints) << ")" << endl;
			}

			// If more points can potentially be earned, use shouldReroll human functionalities to suggest which dice to re-roll and which category
			// to aim for
			round.shouldReroll(round.getDice(), scorecard, true);

			// Ask the user if they would like to change any dice
			cout << "\nWould you like to change any of your dice? (y/n): ";
			// Get input from user if they would like to keep or reroll dice
			cin >> choice;
			// Input validation, prompt for valid input if the input is not y/Y, n/N
			while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
				cout << "Incorrect input. Try again." << endl;
				cin >> choice;
			}
		}
		// If user decides to re roll again, display dice after asking user for intentional or random regeneration of dice for each dice
		if (choice == 'y' || choice == 'Y') {
			cout << "\nRoll 3\n";
			round.reRoll(name);
		}
	}

	//Display scorecard after each player finishes rolling dice
	scorecard.displayAll();

	cout << endl;

	// int vector that holds the current available categories
	vector<int> displayGood;
	// vector assigned to displayAvailable function for current categories
	displayGood = scorecard.displayAvailable(round.getDice());


	// variable that takes input for which category the player would like to pursue
	int chooseCategory;
	// Prompt user to choose a category to fill
	// They can also enter -2 to enter help mode
	// If no category can be filled, -1 can be entered to move on to next player/round/turn
	cout << "\nChoose a category to fill (-2 for help, -1 if no category can be filled): ";
	// take input for desired category that human wants to fill
	cin >> chooseCategory;

	chooseCategory--;


	// 
	while (!(round.isNumberInVector(displayGood, chooseCategory)) && chooseCategory != -3 && chooseCategory != -2) {
		cout << "Please input a valid input. ";
		cin >> chooseCategory;
	}
	if (chooseCategory == -3) {
		cout << "\nHELP MODE\n";
		int highestPoints = scorecard.potentialPoints(round.getDice());
		cout << "\nBased on your current roll, you should fill " << scorecard.getCategory(highestPoints) << " because it will earn you the highest number of points. (" << scorecard.calcRunningScore(round.getDice(), highestPoints) << ")" << endl;
		cout << "\nChoose a category to fill (-1 if no category can be filled): ";
		cin >> chooseCategory;
		chooseCategory--;
		while (!(round.isNumberInVector(displayGood, chooseCategory)) && chooseCategory != -2) { 
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
