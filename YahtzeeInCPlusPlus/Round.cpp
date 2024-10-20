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


//check if given input is in the vector
bool Round::isNumberInVector(const vector<int>& vec, int number) {
	return find(vec.begin(), vec.end(), number) != vec.end();
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
			if (!exists[j-1]) {
				isConsecutive = false;
				break;
			}
		}
		if (isConsecutive) {
			vector<int> nonConsecutiveNum;
			for (int k = 0; k < 5; k++) {
				// Checks if number is smaller than smallest consec number
				// Checks if number is larger than larger consec number
				if (diceRoll[k] < i || diceRoll[k] >= i+countConsec) {
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

int Round::almostThreeOfaKind(int* dice) {
	
	for (int j = 1; j <= 6; j++) {
		

		int count = 0;

		//Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				count++;
			}
		}
		if (count == 2) {
			//return number that has 2 of the same number
			return j;
		}
	}
	//if there arent any, theres nothing to return
	return -1;
}


vector<bool> Round::shouldReroll(int* diceRoll, Scorecard& scorecard, bool human) {
	// Keeps track of how many times each dice value appears in a roll, initializes all values to zero
	int storeDice[6] = {0};

	// Bool vector that has 5 slots initialized to false, will determine which of the dice should be
	// rerolled by making it equal true
	vector<bool> rerollOrNot(5, false);

	// Checks if Yahtzee category is free
	if (scorecard.getWinner(11) == " ") {

		// For loop goes through each five dice
		for (int i = 0; i < 5; i++) {
			// stores and increments the amount of each dice number we have once found
			storeDice[diceRoll[i] - 1]++;
		}

		// For loop to go through storeDice array 
		for (int i = 0; i < 6; i++) {
			// Checks if any dice value repeats 5 times -- aka if we have a Yahtzeee
			if (storeDice[i] == 5) {
				// For help mode-- suggests human to not reroll
				if (human) {
					cout << "We suggest to not reroll as you are eligible for a Yahtzee. " << endl;
				}
				// returns that there is no need to reroll, all five categories are still false
				return rerollOrNot;
			}
		}

		for (int i = 0; i < 6; i++) {
			// If there are only 4 of the same value, try and figure out which dice doesnt align
			if (storeDice[i] == 4) {
				// Variable that will store the one dice that is not one of the 4 repeating numbers
				int oddOneOut = -1;
				// For loop goes through five dice
				for (int j = 0; j < 5; j++) {
					// Checks which one of the five dice is the odd one out
					if (diceRoll[j] != i + 1) {
						// sets rerollOrNot for current dice to true-- indicating that a re roll needs to be done
						rerollOrNot[j] = true;
						// store odd one out value
						oddOneOut = j;
						break;
					}
				}
				// Help mode -- If player is human, suggest to reroll the dice stored in oddOneOut
				if (human) {
					cout << "We suggest that you reroll dice " << oddOneOut + 1 << " in order to get a Yahtzee." << endl;
				}
				// Returns that the odd one out dice needs to be re-rolled
				return rerollOrNot;
			}

		}
	}
	// Uses checkConsecutive function to check if we have 5 consecutive dice, indicating that we have 5 straight
	// Checks if five straight is available
	if (scorecard.checkConsecutive(diceRoll, 5) == true && scorecard.getWinner(10) == " ") {
		// If there are five consecutive dice, suggest human not to re roll
		if (human) {
			cout << "We suggest you not reroll because you are eligible for Five Straight" << endl;
		}
		// will return false for all values -- no need to reroll
		return rerollOrNot;
	}

	// Aiming for 5 straight if we only have 4 straight
	// Checks if we have four straight and if the five straight category is available
	else if (scorecard.checkConsecutive(diceRoll, 4) == true && scorecard.getWinner(10) == " ") {
		// int vector that stores the value of the non consecutive dice values returned by checkNotConsecutive
		vector<int> roundConsecutiveNums = checkNotConsecutive(diceRoll, 4);

		// Loop through our fice die
		for (int i = 0; i < 5; i++) {
			// Checks if the current dice is one of the values stored in roundConsecutiveNums
			if (isNumberInVector(roundConsecutiveNums, diceRoll[i])) {
				// if the current dice is one of the non consecutive numbers, set rerollOrNot as true for that dice
				rerollOrNot[i] = true;
			}
		}

		// Account for the dice that appear more than once so that we have a higher chance of consec numbers
		for (int i = 0; i < 6; i++) {
			// Going through how many each dice face value occurs..
			// If a number repeats more than once
			if (storeDice[i] > 1) {

				// Variable that tracks whether the first occurance of a value
				// has been encountered, set to false
				bool firstAppearance = false;

				// Loop through diceRoll array
				for (int j = 0; j < 5; j++) {
					// Checks if the current diceRoll value matches the current dice face value
					if (diceRoll[j] == i + 1) {
						// If first appearance was previously false, set to true
						// since it has now been detected
						if (!firstAppearance) {
							firstAppearance = true;
							continue;
						}
						// For all other instances other than the first appearance, attempt to reroll
						rerollOrNot[j] = true;		
					}
				}
			}
		}
		// Help mode - if player is human and asks for help...
		// Suggest human to reroll non consecutive and repeating numbers
		if (human) {
			cout << "We suggest you reroll Dice ";
			for (int i = 0; i < 5; i++) {
				if (rerollOrNot[i] == true) {
					cout << i+1 << " ";
				}
			}
		
			cout << " to get a Five Straight" << endl;
		}

		// return the die to reroll
		return rerollOrNot;
	}


	// Aiming for 4 straight if we only have 3 of a kind
	else if (scorecard.checkConsecutive(diceRoll, 3) == true && scorecard.getWinner(9) == " ") {
		vector<int> roundConsecutiveNums = checkNotConsecutive(diceRoll, 3);
		// Check if any of the non consec values are in our diceroll
		for (int i = 0; i < 5; i++) {
			if (isNumberInVector(roundConsecutiveNums, diceRoll[i])) {
				rerollOrNot[i] = true;
			}
		}
		for (int i = 0; i < 6; i++) {
			// reroll number appearing more than once
			if (storeDice[i] > 1) {
				bool firstAppearance = false;
				for (int j = 0; j < 5; j++) {
					if (diceRoll[j] == i + 1) {
						if (!firstAppearance) {
							firstAppearance = true;
							continue;
						}
						rerollOrNot[j] = true;
					}
				}
			}
		}
		if (human) {
			cout << "We suggest you reroll Dice ";
			for (int i = 0; i < 5; i++) {
				if (rerollOrNot[i] == true) {
					cout << i+1 << " ";
				}
			}

			cout << " to get a Four Straight" << endl;
		}

		return rerollOrNot;
	}

	// Check if roll is a full house
	else if (isFullHouse(diceRoll) && scorecard.getWinner(8) == " ") {
		if (human) {
			cout << "We suggest you do not reroll since you are eligible for a Full House. " << endl;
		}
		return rerollOrNot;
	}

	// If theres 3 of one number and 1 of another OR theres two of one number and two of another
	// Aim for full house
	// 5, 5, 5, 4, 2
	// We want to keep 5, reroll 4 or reroll 2
	// reroll first index that is not that is kept (5)

	else if (almostFullHouse(diceRoll) != -1 && scorecard.getWinner(8) == " ") {
		int num3 = almostFullHouse(diceRoll);
		for (int i = 0; i < 5; i++) {
			if (diceRoll[i] != num3) {
				rerollOrNot[i] = true;
				if (human) {
					cout << "We suggest you reroll dice " << i+1 << " to aim for a Full House" << endl;
				}
				return rerollOrNot;
			}
		}
	}
	// checks if there are 2 pairs of the same number
	else if (!(almostFullHouse2(diceRoll).empty()) && scorecard.getWinner(8) == " ") {
		vector<int> storePairs = almostFullHouse2(diceRoll);
		for (int i = 0; i < 5; i++) {
			// reroll specific diceroll that isnt in the pair
			// Finds odd one out
			if (!(isNumberInVector(storePairs, diceRoll[i]))) {
				rerollOrNot[i] = true;
				if (human) {
					cout << "We suggest you reroll dice " << i+1 << " to aim for a full house" << endl;
				}
				return rerollOrNot;
			}
		}
	}

	// skipping three of a kind because we would want to get a full house
	// skipping four of a kind because we would want yahtzee

	else if (almostThreeOfaKind(diceRoll) != -1 && scorecard.getWinner(7) == " ") {
		int num2 = almostThreeOfaKind(diceRoll);
		for (int i = 0; i < 5; i++) {
			if (diceRoll[i] != num2) { 
				// reroll all the dice that are not the same as the pair
				rerollOrNot[i] = true; 
			}
		}
		if (human) {
			cout << "We suggest you reroll ";
			for (int i = 0; i < 5; i++) {
				if (rerollOrNot[i] == true) {
					cout << i+1 << " ";
				} 
			}
			 
			cout << " to get Three of a Kind" << endl;
		}
		return rerollOrNot; 
	}

	else {
		// store numbers of 1s, 2s ... 6s in array
		int diceNum[6] = { 0 };

		for (int i = 0; i < 5; i++) {
			diceNum[diceRoll[i] - 1]++;
		}

		// Store number with highest toss value
		// 4, 4, 6, 6, 4
		// Reroll until we can get as many 6's
		int highestRoll = -1; 
		int highestValue = -1;

		for (int i = 0; i < 6; i++) {
			if (scorecard.getWinner(i) != " ") {
				continue;
			}
			int tempValue = 0;
			tempValue = diceNum[i] * (i + 1);
			if (tempValue >= highestValue) {
				highestValue = tempValue;
				highestRoll = i+1;
			}
		}
		for (int i = 0; i < 5; i++) {
			if (diceRoll[i] != highestRoll) {
				rerollOrNot[i] = true;
			}
		}

		if (human && highestRoll != -1) {
			cout << "We suggest you reroll Dice ";
			for (int i = 0; i < 5; i++) {
				if (rerollOrNot[i] == true) {
					cout << i+1 << " ";
				}
			}

			cout << " to get " << highestRoll << "s " << endl;
		}
		if (human && highestRoll == -1) {
			cout << "No suggestions" << endl;
		}
		return rerollOrNot;
	}

	
}


void Round::rollDice(string name) {

	// Generate 5 dice randomly using a regular for-loop and rand() function
	for (int i = 0; i < 5; ++i) {
		diceRoll[i] = rand() % 6 + 1;
	}

	// Display the dice 5 values using a regular for-loop
	displayDice();
	

}

void Round::reRoll(string name) {
	
	// variable that holds the human players choice -- y: to roll the specific dice again, n: keep the dice 
	char choice;
	// For loop to run through our 5 dice
	for (int i = 0; i < 5; i++) {
		// Ask user it they would like to change the current dice
		cout << "\nWould you like to change dice " << i+1 << "(" << diceRoll[i] << ")? (y/n): ";
		// Get user input 
		cin >> choice;

		// Input validation
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
			cout << "Incorrect input. Try again." << endl;
			cin >> choice; 
		}

		// If user would like to change dice, ask if they would like to choose their own or generate randomly
		if (choice == 'y' || choice == 'Y') {
			// Ask user if they would like to input their own dice
			cout << "\nWould you like to input your own dice? (y/n): ";
			// Get user input. y: to input specific dice, n: generate random dice
			cin >> choice;
			// input validation
			while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
				cout << "Incorrect input. Try again." << endl;
				cin >> choice; 
			}
			// Get user input for the dice they decided to reroll+input on their own
			if (choice == 'y' || choice == 'Y') {
				// Variable that holds custon dice value from human input
				int customDice;
				// Prompts user to enter custom dice value for specific dice
				cout << "Enter custom dice value for dice " << i + 1 << "(" << diceRoll[i] << "): ";
				// User input for dice
				cin >> customDice;

				// Input validation if dice is less than one or greather than 6
				while (customDice < 1 || customDice > 6) {
					cout << "Dice values can only rance from 1-6. Try again." << endl;
					cin >> customDice;

				}

				// Set old dice to new custom value
				diceRoll[i] = customDice;
			}
			// If user chooses for random reroll generation
			else {
				// Random generation of dice chosen to reroll
				diceRoll[i] = rand() % 6 + 1;
				//Outputs new dice value
				cout << "You rolled a " << diceRoll[i] << endl;
			}
		}
	}
	// Display updated set of dice after rerolls
	displayDice();

}

void Round::displayDice() {
	
	// displays all die and their values
	cout << "Dice rolled: ";
	// Loops though 5 dice
	for (int i = 0; i < 5; ++i) {
		// outputs value of each dice
		cout << diceRoll[i] << " ";
	}
	cout << endl;
}

int* Round::getDice() {

	return diceRoll;
}