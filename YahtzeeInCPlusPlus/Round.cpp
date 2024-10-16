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
	
	cout << "Would you like to change any of your dice? (y/n/? for help): "; //help
	//char inputDice;
	cin >> choice;
	while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' && choice != '?') {
		cout << "Incorrect input. Try again." << endl;
		cin >> choice;
	}

	//Help mode begins
	if (choice == '?') {
		cout << "\nHELP MODE" << endl << endl;
		displayDice();
		cout << endl;
		int highestPoints = scorecard.potentialPoints(diceRoll);
		cout << "Based on your current roll, you should fill " << scorecard.getCategory(highestPoints) << " because it will earn you the highest number of points. (" << scorecard.calcRunningScore(diceRoll, highestPoints) << ")" << endl;
		shouldReroll(diceRoll, scorecard, true);
		cout << "\nWould you like to change any of your dice? (y/n/?): ";
		cin >> choice;
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
			cout << "Incorrect input. Try again." << endl;
			cin >> choice;
		}
	}
	if (choice == 'y' || choice == 'Y') {
		cout << "\nRoll 2\n";
		reRoll(human.getName());
		//Implementing third roll
		cout << "Would you like to change any of your dice? (y/n): "; //help
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
	cout << "\nChoose a category to fill: "; //help
	cin >> chooseCategory;

	chooseCategory--;

	while (!(isNumberInVector(displayGood, chooseCategory)) && chooseCategory != -1) {
		cout << "Please input a valid input. ";
		cin >> chooseCategory;
	}
	//Running scores of both players
	int humanScore = 0;
	if (isNumberInVector(displayGood, chooseCategory)) {
		humanScore = scorecard.calcRunningScore(diceRoll, chooseCategory);
		scorecard.updateScorecard(chooseCategory, human.getName(), humanScore, round);
	}
	
	human.setScore(scorecard.calcFinalScore(human.getName()));

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
	int storeDice[6] = {0};
	vector<bool> rerollOrNot(5, false);

	for (int i = 0; i < 5; i++) {
		//stores the amount of each dice number we have
		storeDice[diceRoll[i]-1]++;
	}
	for (int i = 0; i < 6; i++) {
		//checks if we can get yahtzee or similar winning categories
		if (storeDice[i] == 5) {
			if (human) {
				cout << "We suggest to not reroll as you are eligible for a Yahtzee. " << endl;
			}
			return rerollOrNot;
		}
	}
	for(int i = 0; i < 6; i++) {
		//trying to get a yahtzee
		if (storeDice[i] == 4) {
			int oddOneOut = -1;
			for (int j = 0; j < 5; j++) {
				//checks if we can get yahtzee or similar winning categories
				if (diceRoll[j] != i+1) {
					//tells computer to reroll the different dice/odd one out
					rerollOrNot[j] = true;
					oddOneOut = j;
					break;
				}
			}
			if (human) {
				cout << "We suggest that you reroll dice " << oddOneOut+1 << " in order to get a Yahtzee." << endl;
			}
			return rerollOrNot;
		}

	}
	// Checks if we have 5 straight
	if (scorecard.checkConsecutive(diceRoll, 5) == true) {
		if (human) {
			cout << "We suggest you not reroll because you are eligible for Five Straight" << endl;
		}
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
		
			cout << " to get a Five Straight" << endl;
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
	else if (isFullHouse(diceRoll)) {
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

	else if (almostFullHouse(diceRoll) != -1) {
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
	else if (!(almostFullHouse2(diceRoll).empty())) {
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

	else if (almostThreeOfaKind(diceRoll) != -1) {
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

		if (human) {
			cout << "We suggest you reroll ";
			for (int i = 0; i < 5; i++) {
				if (rerollOrNot[i] == true) {
					cout << i+1 << " ";
				}
			}

			cout << " to get " << highestRoll << "s " << endl;
		}
		return rerollOrNot;
	}

	
}

int Round::computerTurn(Computer& computer, Scorecard& scorecard, int round)  {
	int computerScore = 0;
	rollDice(computer.getName());
	//cin >> diceRoll[0] >> diceRoll[1] >> diceRoll[2] >> diceRoll[3] >> diceRoll[4];

	vector<bool> diceToReroll = shouldReroll(diceRoll, scorecard, false);

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
				cout << i+1 << " ";
			}
		}
		cout << endl;

		for (int i = 0; i < 5; i++) {
			if (diceToReroll[i] == true) {
				diceRoll[i] = rand() % 6 + 1;
			}
		}

		cout << "Dice rolled: ";
		for (int i = 0; i < 5; ++i) {
			cout << diceRoll[i] << " ";
		}
		cout << endl;
		//starting second reroll

		diceToReroll = shouldReroll(diceRoll, scorecard, false); 
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
					cout << i+1 << " ";
				}
			}
			cout << endl;

			for (int i = 0; i < 5; i++) {
				if (diceToReroll[i] == true) {
					diceRoll[i] = rand() % 6 + 1;
				}
			}
		}
		cout << "Dice rolled: ";
		for (int i = 0; i < 5; ++i) {
			cout << diceRoll[i] << " ";
		}
		cout << endl;
	}

	scorecard.displayAll();

	cout << endl;


	//displays categories tht can be filled
	vector<int> displayGood;
	displayGood = scorecard.displayAvailable(diceRoll);

	int chosenCategory = -1;

	if (displayGood.empty()) {
		cout << "No categories can be filled. " << endl;
	}
	else {
		
		for (int i = 0; i < displayGood.size(); i++) {
			int score = 0;
			score = scorecard.calcRunningScore(diceRoll, displayGood[i]);
			if (score >= computerScore) {
				computerScore = score;
				chosenCategory = displayGood[i];
			}
		}
		scorecard.updateScorecard(chosenCategory, computer.getName(), computerScore, round);
	}
	computer.setScore(scorecard.calcFinalScore(computer.getName()));
	scorecard.displayAll(); 

	return computerScore;
}

void Round::playRound(Human& human, Computer& computer, Scorecard& scorecard, int round, string tossWinner) {


	int humanScore, computerScore;
	
	if (tossWinner == human.getName()) {
		cout << "\n\nHuman Turn\n\n";
		humanScore = humanTurn(human, scorecard, round);
		if (!scorecard.gameOver()) {
			cout << "\n\nComputer Turn\n\n";
			computerScore = computerTurn(computer, scorecard, round);
		}

	}
	
	else {
		cout << "\n\nComputer Turn\n\n";
		computerScore = computerTurn(computer, scorecard, round);
		if (!scorecard.gameOver()) {
			cout << "\n\nHuman Turn\n\n";
			humanScore = humanTurn(human, scorecard, round);
		}
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
	
	cout << "Dice rolled: ";
	for (int i = 0; i < 5; ++i) {
		cout << diceRoll[i] << " ";
	}
	cout << endl;
}

