#include "Round.h"
#include <vector>
#include <iostream>
#include <cstdlib>


using namespace std;


/* *********************************************************************
Function Name: Round (Constructor)
Purpose: To initialize a Round object, including allocating memory for five dice and setting their initial values.
Parameters: None
Return Value: None (Constructor)
Algorithm:
	1) Allocate memory for an array of five dice.
	2) Initialize each dice value to -1, indicating no value has been set yet.
Reference: None
********************************************************************* */

Round::Round() {
	
	diceRoll = new int[5];

	//For loop for 5 dice, initializing them with no value
	for (int i = 0; i < 5; i++) {
		diceRoll[i] = -1;
	}
}


/* *********************************************************************
Function Name: checkIsNumberInVector
Purpose: To check if a given number is present in a vector.
Parameters:
	- vec (const vector<int>&): A reference to a vector of integers that we need to search in.
	- number (int): The number to be searched within the vector.
Return Value: A boolean value indicating whether the number is present in the vector.
Algorithm:
	1) Use the find function to search for the number in the vector.
	2) Return true if the number is found, otherwise return false.
Reference: Tutor
********************************************************************* */

bool Round::checkIsNumberInVector(const vector<int>& vec, int number) {
	// Check if the number given is in the evctore, insuring its not at the end 
	return find(vec.begin(), vec.end(), number) != vec.end();
}
 
/* *********************************************************************
Function Name: checkNotConsecutive
Purpose: To determine which numbers in a given dice roll are not part of a consecutive sequence.
Parameters:
    - diceRoll (int*): A pointer to an array of integers representing the dice roll values.
    - countConsec (int): The number of consecutive values to check for.
Return Value: A vector of integers representing the numbers in the dice roll that are not part of a consecutive sequence.
Algorithm:
    1) Create a boolean array to track which numbers (1-6) exist in the dice roll.
    2) Mark the existing numbers in the boolean array.
    3) Iterate through possible starting points to check for consecutive sequences.
    4) If a consecutive sequence is found, identify the non-consecutive numbers in the dice roll.
    5) Return a vector of non-consecutive numbers.
    6) If no consecutive sequence is found, return an empty vector.
Reference: Tutor
********************************************************************* */

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

/* *********************************************************************
Function Name: checkIfFullHouse
Purpose: To determine if the current set of dice constitutes a Full House.
Parameters:
	- dice (int*): A pointer to the array representing the dice values.
Return Value: A boolean value indicating whether the dice form a Full House (true) or not (false).
Algorithm:
	1) Loop through possible dice values to check if there is a set of three of a kind.
	2) If found, check for the presence of a pair with a different value.
	3) Return true if both a three of a kind and a pair are present, otherwise return false.
Reference: Tutor
********************************************************************* */

bool Round::checkIfFullHouse(int* dice) {
	// Flag that checks if there are 3 of a kind
	bool hasThreeOfAKind = 0;

	// Flag that checks if there are 2 of a kind as well
	bool hasPair = 0;

	// int value that stores 3 of a kind value
	int threeOfAKindValue = -1;

	// Loop through possible dice values
	for (int j = 1; j <= 6; j++) {
		// Count variable that holds number of times a value occurs
		int count = 0;

		//Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				// Increase count everytime a value has repeated
				count++;
			}
		}
		// If a value repeats 3 times...
		if (count == 3) {
			// Set hasThreeOfAKind value to true
			hasThreeOfAKind = 1;
			// Set threeOfAKindValue variable to number that repeats thrice
			threeOfAKindValue = j;
			break;
		}
	}

	// If no three of a kind is found, skip to the next category
	if (threeOfAKindValue == -1) {
		return false;
	}

	// Loop through possible dice values
	for (int j = 1; j <= 6; j++) {
		// Check if there is a pair of a different value
		if (j == threeOfAKindValue) {
			// If the three of a kind value occurs more than once, try and recc another category
			continue;

		}

		// Count variable checks if dice roll has multiple of the same number
		int count = 0;

		//Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				count++;
			}
		}
		// If a pair has been detected
		if (count == 2) {
			// hasPair flag set to true
			hasPair = 1;
			break;
		}
	}
	// return true for Full House category
	return hasThreeOfAKind && hasPair;
}

/* *********************************************************************
Function Name: checkIfAlmostFullHouse
Purpose: To determine if the current set of dice is close to forming a Full House (i.e., if there is a three of a kind).
Parameters:
	- dice (int*): A pointer to the array representing the dice values.
Return Value: The value of the dice that appears three times if a three of a kind is found; otherwise, -1.
Algorithm:
	1) Loop through possible dice values.
	2) Count the occurrences of each value and return the value if it appears three times.
	3) If no three of a kind is found, return -1.
Reference: Tutor
********************************************************************* */

int Round::checkIfAlmostFullHouse(int* dice) {
	// Loop through all dice face values
	for (int j = 1; j <= 6; j++) {
		
		// Count variable to determine how many times a dice value appears
		int count = 0;

		// Move through 5 dice
		for (int k = 0; k < 5; k++) {
			// If any of the dice have the same value as the current number, increase count
			if (dice[k] == j) {
				count++;
			}
		}
		// If count is equal to 3..
		if (count == 3) {
			// Return number that has 3 of the same number
			return j;
		}
	}
	// If there is not 3 straight, theres nothing to return
	return -1;
}

/* *********************************************************************
Function Name: findAlmostFullHousePairs
Purpose: To determine if the current set of dice contains two pairs, which could be used to form a Full House.
Parameters:
	- dice (int*): A pointer to the array representing the dice values.
Return Value: A vector containing the values of the pairs if found; otherwise, an empty vector.
Algorithm:
	1) Loop through all possible dice values to find a value that appears exactly twice.
	2) If a pair is found, continue searching for another pair.
	3) Return the values of the two pairs if found, otherwise return an empty vector.
Reference: Tutor
********************************************************************* */

vector<int> Round::findAlmostFullHousePairs(int* dice) {

	// Variable to store the value that appears exactly twice
	int num2 = -1;

	// Loop through all possible dice values
	for (int j = 1; j <= 6; j++) {
		int count = 0;

		//Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				count++;
			}
		}
		// If the value appears exactly twice, store it in num2 and break out of the loop
		if (count == 2) {
			num2 = j; 
			break;
		}
	}
	// If no value appears exactly twice, return an empty vector
	if (num2 == -1) { 
		return vector<int>();
	}

	// Loop through all possible dice values (1 to 6) to find another pair
	for (int j = 1; j <= 6; j++) {

		// Skip the value already stored in num2
		if (j == num2) { 
			continue;

		}
		int count = 0;

		// Count the occurrences of value j in the dice array
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				count++;
			}
		}
		// If another value also appears exactly twice, store both pairs and return
		if (count == 2) {
			// int vector that stores value of dice that occur twice
			vector <int> storePairs;
			// Store first pair value
			storePairs.push_back(num2);
			// Store second pair value
			storePairs.push_back(j);
			return storePairs;
		}
	}
	// If no other pair is found, return an empty vector
	return vector<int>();
}

/**********************************************************************
Function Name: checkIfAlmostThreeOfaKind
Purpose: To determine if the current set of dice contains a pair, indicating that it is close to forming a three of a kind.
Parameters:
	- dice (int*): A pointer to the array representing the dice values.
Return Value: The value of the dice that appears twice if found; otherwise, -1.
Algorithm:
	1) Loop through all possible dice values.
	2) Count the occurrences of each value and return the value if it appears twice.
	3) If no pair is found, return -1.
Reference: Tutor
**********************************************************************/

int Round::checkIfAlmostThreeOfaKind(int* dice) {
	
	// Move through 6 dice values
	for (int j = 1; j <= 6; j++) {
		
		// Count variable to tally the occurrences of a number
		int count = 0;

		// Move through 5 dice
		for (int k = 0; k < 5; k++) {
			if (dice[k] == j) {
				// Increase count any time the same number has been detected
				count++;
			}
		}
		// If only two numbers are the same
		if (count == 2) {
			// Return number that has 2 of the same number
			return j;
		}
	}
	//if there arent any, theres nothing to return
	return -1;
}

/* *********************************************************************
Function Name: shouldReroll
Purpose: To determine which dice should be re-rolled to maximize points during a round.
Parameters:
	- diceRoll (int*): A pointer to the array representing the dice values.
	- scorecard (Scorecard&): A reference to the scorecard object to access available categories.
	- human (bool): Indicates whether the player is a human or a computer, affecting suggestion outputs.
Return Value: A vector of boolean values indicating which dice should be re-rolled.
Algorithm:
	1) Analyze the current set of dice and check which categories are available to determine optimal re-rolls.
	2) Suggest re-rolls based on maximizing scoring potential (e.g., aiming for a Full House, Straight, or Yahtzee).
	3) Return a vector of boolean values indicating which dice should be re-rolled.
Reference: Tutor
********************************************************************* */

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

		// Loop through our five die
		for (int i = 0; i < 5; i++) {
			// Checks if the current dice is one of the values stored in roundConsecutiveNums
			if (checkIsNumberInVector(roundConsecutiveNums, diceRoll[i])) {
				// if the current dice is one of the non consecutive numbers, set rerollOrNot as true for that dice
				rerollOrNot[i] = true;
			}
		}

		// Account for the dice that appear more than once so that we have a higher chance of consec numbers
		for (int i = 0; i < 6; i++) {
			// Going through how many times each dice face value occurs..
			// If a number repeats more than once
			if (storeDice[i] > 1) {

				// Variable that tracks whether the first occurrence of a value
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


	// Aiming for Four straight if we only have Three of a kind
	// Check if we have Three straight and if Four Straight category is empty
	else if (scorecard.checkConsecutive(diceRoll, 3) == true && scorecard.getWinner(9) == " ") {
		// int vector that stores the value of the non consecutive dice values returned by checkNotConsecutive
		vector<int> roundConsecutiveNums = checkNotConsecutive(diceRoll, 3);

		// Check if any of the non consec values are in our diceroll
		for (int i = 0; i < 5; i++) {
			if (checkIsNumberInVector(roundConsecutiveNums, diceRoll[i])) {
				// If our dice has any of the non consecutive values, set rerollOrNot flag to true
				rerollOrNot[i] = true;
			}
		}

		// Reroll additional repeating numbers
		for (int i = 0; i < 6; i++) {
			// Going through how many times each dice face value occurs..
			// If a number repeats more than once
			if (storeDice[i] > 1) {
				// Variable that tracks whether the first occurrence of a value
				// has been encountered, set to false
				bool firstAppearance = false;

				// Move through 5 dice
				for (int j = 0; j < 5; j++) {
					// If the dice values match the current dice values
					if (diceRoll[j] == i + 1) {
						// If first appearance was previously false, set to true
						// since it has now been detected
						if (!firstAppearance) {
							// If this is the first time a number has appeared, set to true
							firstAppearance = true;
							continue;
						}
						// For all other appearances, set rerollOrNot to true for that dice
						rerollOrNot[j] = true;
					}
				}
			}
		}
		// If player is human, suggest to re-roll non consecutive value
		// As well as dices that occur more than once
		if (human) {
			cout << "We suggest you reroll Dice ";
			for (int i = 0; i < 5; i++) {
				if (rerollOrNot[i] == true) {
					cout << i+1 << " ";
				}
			}

			cout << " to get a Four Straight" << endl;
		}

		// Return reroll recommendations
		return rerollOrNot;
	}

	// Check if roll is a full house
	else if (checkIfFullHouse(diceRoll) && scorecard.getWinner(8) == " ") {
		// If there is a full house, do not reccommend a re-roll
		if (human) {
			cout << "We suggest you do not reroll since you are eligible for a Full House. " << endl;
		}
		return rerollOrNot;
	}


	// If dice is close to fufilling a Full House and the category is empty..
	else if (checkIfAlmostFullHouse(diceRoll) != -1 && scorecard.getWinner(8) == " ") {
		
		// Assign the number that repeats thrics to int variable num3
		int num3 = checkIfAlmostFullHouse(diceRoll);
		for (int i = 0; i < 5; i++) {
			if (diceRoll[i] != num3) {
				// Set rerollOrNot flag to true for numbers that are not the ones that repeat thrice
				rerollOrNot[i] = true;
				// Suggest to re-roll the two dice that are not in num3 if human player 
				if (human) {
					cout << "We suggest you reroll dice " << i+1 << " to aim for a Full House" << endl;
				}
				return rerollOrNot;
			}
		}
	}

	// If dice is close to fufilling a Full House and the category is empty.. 
	// Checks if there are 2 pairs of the same number
	else if (!(findAlmostFullHousePairs(diceRoll).empty()) && scorecard.getWinner(8) == " ") {
		
		// Int vector that stores values of the two pairs
		vector<int> storePairs = findAlmostFullHousePairs(diceRoll);

		// Loop thruogh 5 dice
		for (int i = 0; i < 5; i++) {
			// If the number currently inspected isnt one of the pairs
			if (!(checkIsNumberInVector(storePairs, diceRoll[i]))) {
				// Set rerollOrNot to true for dice that is the odd one out
				rerollOrNot[i] = true;

				// Suggest human to reroll outcast dice
				if (human) {
					cout << "We suggest you reroll dice " << i+1 << " to aim for a full house" << endl;
				}
				return rerollOrNot;
			}
		}
	}

	// Skipping three of a kind because we would want to get a full house (more points)
	// Skipping four of a kind because we would want yahtzee (more points)

	// Aim for Three of a kind
	else if (checkIfAlmostThreeOfaKind(diceRoll) != -1 && scorecard.getWinner(7) == " ") {
		
		// Variable that stores value of dice that appear twice
		int num2 = checkIfAlmostThreeOfaKind(diceRoll);

		// Loop through 5 dice values
		for (int i = 0; i < 5; i++) {
			if (diceRoll[i] != num2) { 
				// Reroll all the dice that are not the same as the pair
				rerollOrNot[i] = true; 
			}
		}
		// Suggest human to re-roll values so progam can get 3+ of the same dice
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

		// Count the number of 1s-6s in arrays
		for (int i = 0; i < 5; i++) {
			diceNum[diceRoll[i] - 1]++;
		}

		
		// Variable that stores dice number with highest points
		int highestRoll = -1; 

		// Variable that stores face value with highest roll value
		int highestValue = -1;

		// Go through categories 1-6
		for (int i = 0; i < 6; i++) {
			// If there is no winner for the category, continue
			if (scorecard.getWinner(i) != " ") {
				continue;
			}

			// Variable that holds the amount of points the current category will give
			int tempValue = 0;

			// Calculate how many points the current category will give
			tempValue = diceNum[i] * (i + 1);

			// If the current category gives more potential points than the category already giving the highest points
			if (tempValue >= highestValue) {
				// Make the new highest achieveable value the current tempValue
				highestValue = tempValue;

				// Update highestRoll to the current dice face value
				highestRoll = i+1;
			}
		}

		// Mark the dice that are not the highestRoll value for reroll
		for (int i = 0; i < 5; i++) {
			if (diceRoll[i] != highestRoll) {
				rerollOrNot[i] = true;
			}
		}
		// Suggest reroll to human if applicable
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

/* *********************************************************************
Function Name: rollDice
Purpose: To randomly generate and display values for all five dice in the current round.
Parameters:
	- name (string): The name of the player rolling the dice.
Return Value: None
Algorithm:
	1) Generate a random value between 1 and 6 for each of the five dice.
	2) Display the generated values.
Reference: None
********************************************************************* */

void Round::rollDice(string name) {

	// Generate 5 dice randomly using a regular for-loop and rand() function
	for (int i = 0; i < 5; ++i) {
		diceRoll[i] = rand() % 6 + 1;
	}

	// Display the dice 5 values using a regular for-loop
	displayDice();
	

}

/* *********************************************************************
Function Name: reRoll
Purpose: To allow the player to re-roll some or all of the five dice in the current round.
Parameters:
	- name (string): The name of the player rolling the dice.
Return Value: None
Algorithm:
	1) Prompt the player to decide which dice to re-roll.
	2) Allow the player to input custom values or generate new random values for each selected die.
	3) Display the updated set of dice.
Reference: None
********************************************************************* */

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

/* *********************************************************************
Function Name: displayDice
Purpose: To display the current values of the five dice in the round.
Parameters: None
Return Value: None
Algorithm:
	1) Loop through the five dice and output their values.
Reference: None
********************************************************************* */

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

/* *********************************************************************
Function Name: getDice
Purpose: To retrieve the current values of the five dice in the round.
Parameters: None
Return Value: A pointer to the array representing the dice values.
Algorithm:
	1) Return the pointer to the array holding the current dice values.
Reference: None
********************************************************************* */

int* Round::getDice() {
	// Return rolled dice
	return diceRoll;
}

/* *********************************************************************
Function Name: setDice
Purpose: To set or update the value of a specific die.
Parameters:
	- dice (int): The value to set for the die.
	- diceNumber (int): The index of the die to be updated.
Return Value: None
Algorithm:
	1) Validate the input value to ensure it is between 1 and 6.
	2) Update the value of the specified die.
Reference: None
********************************************************************* */

void Round::setDice(int dice, int diceNumber) {
	// Validating input when mutator function for setting dice is used
	if (dice > 0 && dice < 7) {
		diceRoll[diceNumber] = dice;
	}
}

/* *********************************************************************
Function Name: ~Round (Destructor)
Purpose: To release resources allocated during the round.
Parameters: None
Return Value: None
Algorithm:
	1) Delete the allocated memory for the diceRoll array.
Reference: None
********************************************************************* */

// Destructor releases resources
Round::~Round() {
	delete diceRoll;
}