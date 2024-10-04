#include "Round.h"
#include <vector>
#include <iostream>
#include <cstdlib>


using namespace std;

Round::Round() {
	
	//For loop for 5 dice, initializing them with no value
	for (int i = 0; i < 5; i++) {
		diceRoll[i] = -1;
	}
}

string Round::toss(string name1, string name2) {
    
	//Dice For Human
	int dice1 = -1;

	//Dice for Computer
    int dice2 = -1;

	//Dice roll that determines the next player
	//Re-rolls if tied
	while (dice1 == dice2) {
		cout << name1 << " is rolling the dice...\n";
		dice1 = rand() % 6 + 1;
		cout << name1 << " rolled: " << dice1;
		cout << endl;

		//Dice roll for computer
		cout << name2 << " is rolling the dice...\n";
		dice2 = rand() % 6 + 1;
		cout << name2 << " rolled: " << dice2;
		cout << endl;
		if (dice1 == dice2) {
			cout << "It's a tie! Re-rolling...\n";
		}
	}
	

	if (dice1 > dice2) {
		cout << name1 << " won the toss.\n";
		return name1;
	}
	else {
		cout << name2 << " won the toss.\n";
		return name2;
	}
}

//check if given input is in the vector
bool isNumberInVector(const vector<int>& vec, int number) {
	return find(vec.begin(), vec.end(), number) != vec.end();
}

int Round::humanTurn(Human& human, Scorecard& scorecard, int round) {
	
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
			diceRoll[i] = diceChoice;
		}

	}
	else if (choice == 'N' || choice == 'n') {
		rollDice(human.getName());
	}

	//Asks user if they would like to reroll dice after initial roll
	cout << "Would you like to change any of your dice? (y/n): ";
	//char inputDice;
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		cout << "\nRoll 2\n";
		reRoll(human.getName());
		//Implementing third roll
		cout << "Would you like to change any of your dice? (y/n): ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			cout << "\nRoll 3\n";
			reRoll(human.getName());
		}
	}

	//Display scorecard after each player finishes rolling dice

	scorecard.displayAll();

	cout << endl;

	vector<int> displayGood;
	displayGood = scorecard.displayAvailable(diceRoll);



	//Ask which category the player would like to pursue
	int chooseCategory;
	cout << "\nChoose a category to fill: ";
	cin >> chooseCategory;

	chooseCategory--;

	while (!(isNumberInVector(displayGood, chooseCategory)) && chooseCategory != -1) {
		cout << "Please input a valid input. ";
		cin >> chooseCategory;
	}
	//Running scores of both players
	int humanScore;
	if (isNumberInVector(displayGood, chooseCategory)) {
		humanScore = scorecard.calcRunningScore(diceRoll, chooseCategory);
		scorecard.updateScorecard(chooseCategory, human.getName(), humanScore, round);
	}
	scorecard.displayAll();

	return humanScore;
}

vector<bool> Round::shouldReroll(int* diceRoll) {
	int storeDice[6];
	vector<bool> rerollOrNot{ 5, false };

	for (int i = 0; i < 5; i++) {
		//stores the amount of each dice number we have
		storeDice[diceRoll[i - 1]]++;
	}
	for (int i = 0; i < 6; i++) {
		//checks if we can get yahtzee or similar winning categories
		if (storeDice[i] == 5) {
			return rerollOrNot;
		}

	}
	for(int i = 0; i < 6; i++) {
		//trying to get a yahtzee
		if (storeDice[i] == 4) {
			for (int j = 0; j < 5; j++) {
				//checks if we can get yahtzee or similar winning categories
				if (diceRoll[j] != i+1) {
					//tells computer to reroll the different dice/odd one out
					rerollOrNot[i] = true;
				}
			}
			return rerollOrNot;
		}

	}

	return rerollOrNot;
}

int Round::computerTurn(Computer& computer, Scorecard& scorecard, int round) {
	int computerScore;
	rollDice(computer.getName());



	return computerScore;
}

void Round::playRound(Human& human, Computer& computer, Scorecard& scorecard, int round) {

	cout << "\nToss\n";
	string tossWinner = toss(human.getName(), computer.getName());
	
	if (tossWinner == human.getName()) {
		humanTurn(human, scorecard, round);
		computerTurn(computer, scorecard, round);

	}
	
	else {
		computerTurn(computer, scorecard, round);
		humanTurn(human, scorecard, round);

	}

	

}

void Round::rollDice(string name) {

	// Roll the dice using a regular for-loop
	for (int i = 0; i < 5; ++i) {
		diceRoll[i] = rand() % 6 + 1;
	}

	// Display the dice values using a regular for-loop
	displayDice();
	

}

void Round::reRoll(string name) {
	
	char choice;
	for (int i = 0; i < 5; i++) {
		cout << "\nWould you like to change dice " << i+1 << "(" << diceRoll[i] << ")? (y/n): ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			diceRoll[i] = rand() % 6 + 1;
			cout << "You rolled a " << diceRoll[i] << endl;
		}
	}
	displayDice();

}

void Round::displayDice() {
	
	cout << "Your dice rolled: ";
	for (int i = 0; i < 5; ++i) {
		cout << diceRoll[i] << " ";
	}
	cout << endl;
}

