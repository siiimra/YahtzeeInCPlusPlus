#include "Human.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Human::Human(string name1) : Player(name1) {
    //Welcomes human player to Yahtzee
    cout << "Welcome to Yahtzee, " << name1 << "!" << endl;



}


void Human::turn(Scorecard& scorecard, int roundNum, Round& round) {

	cout << "\nRoll 1\n";
	cout << "Would you like to input your own dice? (y/n) ";
	char choice;
	cin >> choice;
	while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
		cout << "Invalid choice, input Y or N: ";
		cin >> choice;
	}

	if (choice == 'Y' || choice == 'y') {
		int diceChoice;
		for (int i = 0; i < 5; i++) {
			cout << "Enter dice " << i + 1 << ": ";
			cin >> diceChoice;
			(round.getDice())[i] = diceChoice;
		}

	}
	else if (choice == 'N' || choice == 'n') {
		round.rollDice(name);
	}

	//Asks user if they would like to reroll dice after initial roll

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



	while (!(round.isNumberInVector(displayGood, chooseCategory)) && chooseCategory != -1 && chooseCategory != -2) {
		cout << "Please input a valid input. ";
		cin >> chooseCategory;
	}
	if (chooseCategory == -2) {
		cout << "\nHELP MODE\n";
		int highestPoints = scorecard.potentialPoints(round.getDice());
		cout << "\nBased on your current roll, you should fill " << scorecard.getCategory(highestPoints) << " because it will earn you the highest number of points. (" << scorecard.calcRunningScore(round.getDice(), highestPoints) << ")" << endl;
		cout << "\nChoose a category to fill (-1 if no category can be filled): ";
		cin >> chooseCategory;
		while (!(round.isNumberInVector(displayGood, chooseCategory)) && chooseCategory != -1) { 
			cout << "Please input a valid input. ";
			cin >> chooseCategory;
		}
	}
	chooseCategory--;
	//Running scores of both players
	int humanScore = 0;
	if (round.isNumberInVector(displayGood, chooseCategory)) {
		humanScore = scorecard.calcRunningScore(round.getDice(), chooseCategory);
		scorecard.updateScorecard(chooseCategory, name, humanScore, roundNum); 
	}

	setScore(scorecard.calcFinalScore(name));

	scorecard.displayAll();
}
