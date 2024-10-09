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

vector<int> Round::checkNotConsecutive(int* diceRoll, int countConsec) {
	// Track which numbers exist
	bool exists[6] = { false };

	//Goes through diceRoll array, checks which of the 6 numbers exist
	for (int i = 0; i < 5; i++) {
		//Marks true if dice exists
		exists[diceRoll[i]-1] = true;
	}

	// Now check for consecutive sequences
	// Checks lowest number out of the dice, marks true if sequence is consecutive
	for (int i = 1; i <= 6 - countConsec + 1; i++) {
		bool isConsecutive = true;
		// Checks if numbers from i to i+countConsec -1 to check if theres a sequence
		for (int j = i; j < i + countConsec; j++) {
			if (!exists[j]) {
				isConsecutive = false;
				break;
			}
		}
		if (isConsecutive) {
			vector<int> nonConsecutiveNum;
			for (int k = 0; k < 5; k++) {
				// Checks if number is smaller than smallest consec number
				// Checks if number is larger than larger consec number
				if (diceRoll[k] - 1 < i || diceRoll[k]-1 >= i+countConsec) {
					//push nonconsecutive value onto vector
					nonConsecutiveNum.push_back(diceRoll[k]);
				}
			}
			return nonConsecutiveNum;
		}
	}
	//returns empty vector
	return vector<int>();
	
}

bool Round::isFullHouse(int* dice) {
	bool check = 0;
	bool check2 = 0;
	int num3 = -1;

	for (int j = 1; j <= 6; j++) {
		int count = 0;

		//Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				count++;
			}
		}
		if (count == 3) {
			check = 1;
			num3 = j;
			break;
		}
	}
	if (num3 == -1) {
		return false;
	}
	for (int j = 1; j <= 6; j++) {
		if (j == num3) {
			continue;

		}
		int count = 0;

		//Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				count++;
			}
		}
		if (count == 2) {
			check2 = 1;
			break;
		}
	}
	return check && check2;
}

int Round::almostFullHouse(int* dice) {
	for (int j = 1; j <= 6; j++) {
		int count = 0;

		//Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				count++;
			}
		}
		if (count == 3) {
			//return number that has 3 of the same number
			return j;
		}
	}
	//if there arent any, theres nothing to return
	return -1;
}

vector<int> Round::almostFullHouse2(int* dice) {
	int num2 = -1;

	for (int j = 1; j <= 6; j++) {
		int count = 0;

		//Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				count++;
			}
		}
		if (count == 2) {
			num2 = j; 
			break;
		}
	}
	if (num2 == -1) { 
		return vector<int>();
	}
	for (int j = 1; j <= 6; j++) {
		if (j == num2) { 
			continue;

		}
		int count = 0;

		//Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				count++;
			}
		}
		if (count == 2) {
			vector <int> storePairs;
			storePairs.push_back(num2);
			storePairs.push_back(j);
			return storePairs;
		}
	}
	return vector<int>();
}


vector<bool> Round::shouldReroll(int* diceRoll, Scorecard& scorecard) {
	int storeDice[6] = {0};
	vector<bool> rerollOrNot(5, false);

	for (int i = 0; i < 5; i++) {
		//stores the amount of each dice number we have
		storeDice[diceRoll[i]-1]++;
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
					rerollOrNot[j] = true;
					break;
				}
			}
			return rerollOrNot;
		}

	}
	// Checks if we have 5 straight
	if (scorecard.checkConsecutive(diceRoll, 5) == true) {
		return rerollOrNot;
	}
	// Aiming for 5 straight if we only have 4 straight
	else if (scorecard.checkConsecutive(diceRoll, 4) == true) {
		vector<int> roundConsecutiveNums = checkNotConsecutive(diceRoll, 4);
		// Check if any of the non consec values are in our diceroll
		for (int i = 0; i < 5; i++) {
			if (isNumberInVector(roundConsecutiveNums, diceRoll[i])) {
				rerollOrNot[i] = true;
			}
		}
		return rerollOrNot;
	}
	// Aiming for 4 straight if we only have 3 straight
	else if (scorecard.checkConsecutive(diceRoll, 3) == true) {
		vector<int> roundConsecutiveNums = checkNotConsecutive(diceRoll, 3);
		// Check if any of the non consec values are in our diceroll
		for (int i = 0; i < 5; i++) {
			if (isNumberInVector(roundConsecutiveNums, diceRoll[i])) {
				rerollOrNot[i] = true;
			}
		}
		return rerollOrNot;
	}

	// Check if roll is a full house
	else if (isFullHouse(diceRoll)) {
		return rerollOrNot;
	}

	// If theres 3 of one number and 1 of another OR theres two of one number and two of another
	// Aim for full house
	// 5, 5, 5, 4, 2
	// We want to keep 5, reroll 4 or reroll 2
	// reroll first index that is not that is kept (5)

	else if (almostFullHouse(diceRoll) != -1) {
		int num3 = almostFullHouse(diceRoll);
		for (int i = 0; i < 5; i++) {
			if (diceRoll[i] != num3) {
				rerollOrNot[i] = true;
				return rerollOrNot;
			}
		}
	}
	// checks if there are 2 pairs of the same number
	else if (!((almostFullHouse2(diceRoll)).empty)) {

	}

	
	return rerollOrNot;
}

int Round::computerTurn(Computer& computer, Scorecard& scorecard, int round) {
	int computerScore = 1;
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

