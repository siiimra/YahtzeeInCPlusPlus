#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include "Scorecard.h"
#include <vector>
#include <iomanip>
//checks if number is in vector or not
#include <algorithm>

using namespace std;

/**********************************************************************
Function Name: Scorecard (Constructor)
Purpose: To initialize a new Scorecard object with default values for categories, scores, and winners.
Parameters: None
Return Value: None (constructor)
Algorithm:
	1) Initialize the scoreboard2 array with zeros for scores and categories.
	2) Initialize the scoreboard1 array with empty strings to represent unfilled categories.
	3) Set the names, descriptions, and score calculations for each category.
Reference: None
**********************************************************************/

Scorecard::Scorecard()
{
	// Initialize scoreboard2 with zeros for all categories and scores
	for (int i = 0; i < 12; i++) {

		for (int j = 0; j < 2; j++) {
			scoreboard2[i][j] = 0;
		}
	}

	// Initialize scoreboard1 with empty strings to represent unfilled categories/no winners
	for (int i = 0; i < 12; i++) {
		scoreboard1[i][3] = " ";
	}

	// scoreboard1[i][0] outputs category name
	// scoreboard1[i][1] outputs category description
	// scoreboard1[i][2] outputs category score calculation
	// scoreboard1[i][3] outputs category winner


	scoreboard1[0][0] = "Aces";
	scoreboard1[0][1] = "Any combination";
	scoreboard1[0][2] = "Sum of dice with the number 1";
	scoreboard1[0][3] = " ";


	scoreboard1[1][0] = "Twos";
	scoreboard1[1][1] = "Any combination";
	scoreboard1[1][2] = "Sum of dice with the number 2";
	scoreboard1[1][3] = " ";

	scoreboard1[2][0] = "Threes";
	scoreboard1[2][1] = "Any combination";
	scoreboard1[2][2] = "Sum of dice with the number 3";
	scoreboard1[2][3] = " ";

	scoreboard1[3][0] = "Fours";
	scoreboard1[3][1] = "Any combination";
	scoreboard1[3][2] = "Sum of dice with the number 4";
	scoreboard1[3][3] = " ";

	scoreboard1[4][0] = "Fives";
	scoreboard1[4][1] = "Any combination";
	scoreboard1[4][2] = "Sum of dice with the number 5";
	scoreboard1[4][3] = " ";

	scoreboard1[5][0] = "Sixes";
	scoreboard1[5][1] = "Any combination";
	scoreboard1[5][2] = "Sum of dice with the number 6";
	scoreboard1[5][3] = " ";

	scoreboard1[6][0] = "Three of a Kind";
	scoreboard1[6][1] = "At least three dice the same";
	scoreboard1[6][2] = "Sum of all dices";
	scoreboard1[6][3] = " ";

	scoreboard1[7][0] = "Four of a Kind";
	scoreboard1[7][1] = "At least four dice the same";
	scoreboard1[7][2] = "Sum of all dices";
	scoreboard1[7][3] = " ";

	scoreboard1[8][0] = "Full House";
	scoreboard1[8][1] = "Three of one number and two of another";
	scoreboard1[8][2] = "25";
	scoreboard1[8][3] = " ";

	scoreboard1[9][0] = "Four Straight";
	scoreboard1[9][1] = "Four sequential dice";
	scoreboard1[9][2] = "30";
	scoreboard1[9][3] = " ";

	scoreboard1[10][0] = "Five Straight";
	scoreboard1[10][1] = "Five sequential dice";
	scoreboard1[10][2] = "40";
	scoreboard1[10][3] = " ";

	scoreboard1[11][0] = "Yahtzee";
	scoreboard1[11][1] = "All five dice the same";
	scoreboard1[11][2] = "50";
	scoreboard1[11][3] = " ";

}

/**********************************************************************
Function Name: calcFinalScore
Purpose: To calculate the final score for a player by summing up the scores of all filled categories.
Parameters:
	- name (string): The name of the player whose final score is being calculated.
Return Value: The final score of the player (int).
Algorithm:
	1) Loop through all 12 categories.
	2) Add the score of each category filled by the given player.
	3) Return the calculated score.
Reference: None
**********************************************************************/

int Scorecard::calcFinalScore(string name)
{
	// Variable that holds final score initialized to 0
	int score = 0;

	// Go through 12 categories
	for (int i = 0; i < 12; i++)
	{
		// Add up points scored by players for each category they have fufilled
		if (scoreboard1[i][3] == name)
		{
			score += scoreboard2[i][0];
		}
	}
	// Return final score
	return score;
}

/* *********************************************************************
Function Name: updateScorecard
Purpose: To update a specific category in the scorecard with the player's name, score, and round number.
Parameters:
	- index (int): The index of the category to be updated.
	- name (string): The name of the player who fills the category.
	- score (int): The score to be assigned to the category.
	- round (int): The round number when the category was filled.
Return Value: None
Algorithm:
	1) Check if the category is unfilled.
	2) Update the category with the player's name, score, and round number.
Reference: None
********************************************************************* */

void Scorecard::updateScorecard(int index, string name, int score, int round)
{
	// update and insert category information if it is empty and available
	if (scoreboard1[index][3] == " ") {
		scoreboard1[index][3] = name;
		scoreboard2[index][0] = score;
		scoreboard2[index][1] = round;
	}

}

/**********************************************************************
Function Name: displayAll
Purpose: To display the complete scorecard, including all categories, descriptions, scores, winners, and points.
Parameters: None
Return Value: None
Algorithm:
	1) Display the header.
	2) Loop through all 12 categories and display the relevant details.
Reference: None
**********************************************************************/

void Scorecard::displayAll() {


	cout << endl;

	// Output header
	cout << setw(16) << "Category" << setw(40) << "Description" << setw(30) << "Score" << setw(25) << "Winner" << setw(10) << "Points" << setw(7) << "Round" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;

	// Loop that outputs information for each category
	for (int i = 0; i < 12; i++) {
		
		// Formatting purposes, leave speace between number 1-9
		if (i < 9) {
			cout << " " << i + 1;
		}
		else {
			cout << i + 1;
		}
		// Output category number and name
		cout << setw(16) << scoreboard1[i][0] << setw(40)
			// Output category description
			<< scoreboard1[i][1] << setw(40)
			// Output category Score classification
			<< scoreboard1[i][2] << setw(15)
			// Output Winner
			<< scoreboard1[i][3] << setw(10)
			// Output Points earned from category
			<< scoreboard2[i][0] << setw(7)
			// Output round which category was fufilled
			<< scoreboard2[i][1] << endl;

	}
}

/* *********************************************************************
Function Name: checkConsecutive
Purpose: To determine if the dice contain a sequence of consecutive numbers of a given length.
Parameters:
	- dice (int*): A pointer to the array representing the dice values.
	- count1 (int): The length of the consecutive sequence to check for.
Return Value: A boolean indicating whether the dice contain a consecutive sequence of the given length.
Algorithm:
	1) Create a boolean array to track which dice values are present.
	2) Mark the values present in the dice.
	3) Check if there is a sequence of consecutive numbers of the given length.
Reference: Tutor
********************************************************************* */

bool Scorecard::checkConsecutive(int* dice, int count1) {
	// Bool flag to keep track of which values exist  (indices 1 to 6)
	bool exists[7] = { false }; 

	// Mark exists variable as true if dice value is present
	for (int i = 0; i < 5; i++) {
		exists[dice[i]] = true;
	}
	
	// Now check for consecutive sequences of specified length
	for (int i = 1; i <= 6 - count1 + 1; i++) {
		// Flag that assumes numbers are already consecutive
		bool isConsecutive = true;
		// Check each number in the sequence from i to i + count1 - 1
		for (int j = i; j < i + count1; j++) {
			// If the current number is not present, mark the sequence as not consecutive
			if (!exists[j]) {
				isConsecutive = false;
				break;
			}
		}

		// If consecutive sequence is found, return true
		if (isConsecutive) {
			return true;
		}
	}
	// No consecutive sequence found, return false
	return false;
}

/**********************************************************************
Function Name: displayAvailable
Purpose: To display the available categories that the player can fill based on the current dice roll.
Parameters:
	- dice (int*): A pointer to the array representing the dice values.
Return Value: A vector of integers representing the available categories.
Algorithm:
	1) Loop through all 12 categories.
	2) Check if the category is unfilled and can be filled based on the current dice.
	3) Display the available categories and add them to the vector.
	4) Return the vector of available categories.
Reference: Tutor
**********************************************************************/

vector<int> Scorecard::displayAvailable(int* dice) {

	// Vector to store available categories
	vector<int> availableCategories;

	cout << "\nThe following categories can be filled: " << endl;

	// Loop through all 12 categories
	for (int i = 0; i < 12; i++) {
		// Check if the category has not been filled yet
		if (scoreboard1[i][3] == " ") {
			// Categories Aces to Sixes
			if (i < 6) {
				// Push categories into vector if not filled
				availableCategories.push_back(i);
				// Display category and description
				cout << i + 1 << ' ' << scoreboard1[i][0] << " - " << scoreboard1[i][1] << endl;
			}

			// Category Three of a Kind
			else if (i == 6) {
				// Bool variable/flag to determine if 3 of a kind can be filled
				bool check3OfKind = 0;

				// For loop to Check if there are 3 same dice values
				// Loop goes through all possible dice fave values
				for (int j = 1; j <= 6; j++) {

					// Count variable holds how many times a value has occurred
					int count = 0;

					// Loop through dice array, if current dice is the same as the face value in i
					// Increase count
					for (int k = 0; k < 5; k++) {
						if (dice[k] == j) {
							count++;
						}
					}
					// Check if dice value has occurred 3 or more times
					if (count >= 3) {
						// Set flag to true
						check3OfKind = 1;
						break;
					}
				}
				if (check3OfKind == 1){
					// Push category into vector if check3OfKind has been verified
					availableCategories.push_back(i);

					// Display category and description
					cout << i + 1 << ' ' << scoreboard1[i][0] << " - " << scoreboard1[i][1] << endl;
				}
			}
			// Category Four of a Kind
			else if (i == 7) {
				// Bool variable/flag to determine if 4 of a kind can be filled
				bool check4OfKind = 0;

				// For loop to Check if there are 4 same dice values
				// Loop goes through all possible dice fave values
				for (int j = 1; j <= 6; j++) {

					// Count variable holds how many times a value has occurred
					int count = 0;

					// Loop through dice array, if current dice is the same as the face value in i
					// Increase count
					for (int k = 0; k < 5; k++) {
						if (dice[k] == j) {
							count++;
						}
					}
					// Check if dice value has occurred 4 or more times
					if (count >= 4) {
						check4OfKind = 1;
						break;
					}
				}
				// Check if dice value has occurred 4 or more times
				if (check4OfKind == 1) {
					// Push category into vector if check4OfKind has been verified
					availableCategories.push_back(i);
					cout << i + 1 << ' ' << scoreboard1[i][0] << " - " << scoreboard1[i][1] << endl;

				}
			}
			// Category Full House
			else if (i == 8) {
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
					continue;
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
							// Increase count everytime a value has repeated
							count++;
						}
					}
					// If a pair has been found..
					if (count == 2) {
						// hasPair flag set to true
						hasPair = 1;
						break;
					}
				}

				// If there are three of one number and two of another
				if (hasThreeOfAKind == 1 && hasPair == 1) {
					// Push Full House into vector
					availableCategories.push_back(i);
					cout << i + 1 << ' ' << scoreboard1[i][0] << " - " << scoreboard1[i][1] << endl;

				}
			}
			// Four Straight and Five Straight
			else if (i == 9 || i == 10) {
				// Check if the dice contain a consecutive sequence of numbers
				if (checkConsecutive(dice, i-5)) {
					// Push Four Straight and/or Five straight into vector if numbers are consecutive
					availableCategories.push_back(i);
					cout << i + 1 << ' ' << scoreboard1[i][0] << " - " << scoreboard1[i][1] << endl;
				}
			}
			// Check Yahtzee
			else if (i == 11) {
				// Flag used to check if all dice are the same
				bool allSame = true;
				// Loop through five dice
				for (int j = 1; j < 5; j++) {
					// If any of the dice are not the same as the first dice..
					if (dice[j] != dice[0]) {
						// allSame flag set to false, there is not Yahtzee
						allSame = false;
						break;
					}
				}
				// If allSame variable is true, we have a Yahtzee
				if (allSame) {
					// Push Yahtzee category into vector 
					availableCategories.push_back(i);
					cout << i + 1 << ' ' << scoreboard1[i][0] << " - " << scoreboard1[i][1] << endl; 
				
				}
			}
			
		}
	}


	// Return the categories pushed into the vector
	return availableCategories;
}

/* *********************************************************************
Function Name: calcRunningScore
Purpose: To calculate the score for a specific category based on the current dice roll.
Parameters:
	- dice (int*): A pointer to the array representing the dice values.
	- category (int): The index of the category for which to calculate the score.
Return Value: The score for the chosen category (int).
Algorithm:
	1) Check the category and calculate the score accordingly (e.g., sum of specific values, fixed points).
	2) Return the calculated score.
Reference: None
********************************************************************* */

int Scorecard::calcRunningScore(int* dice, int category) {
	// Initialize score to 0
	int score = 0;
	// If the category referred to is
	// Aces, Twos, Threes, Fours, Fives, or Sixes
	// The score is the sum of dice with the number associated
	if (category < 6) {
		int count = 0;

		// Count the number of dice matching the category number (category + 1)
		for (int i = 0; i < 5; i++) {
			if (dice[i] == (category+1)) { 
				// Increase the count for every instance of a number
				count++;
			}
		}

		// Calculate the score as the amount of times a dice value showed up
		// by the corresponding category number
		score = count * (category + 1);
	}

	// If the category is for Three of a Kind or Four of a Kind, score is sum all dice
	else if (category == 6 || category == 7) {
		
		for (int i = 0; i < 5; i++) {
			// Score is the sum of all dice
			score += dice[i];
		}
	}

	// If the category is Full House, score is 25 points
	else if (category == 8) {
		score = 25;
	}

	// If the category is Four Straight, score is 30 points
	else if (category == 9) {
		score = 30;
	}

	// If the category is Five Straight, score is 40 points
	else if (category == 10) {
		score = 40;
	}

	// If the category is Yahtzee, score is 50 points
	else if (category == 11) {
		score = 50;
	}

	// Return score of the category thats chosen
	return score;
}

/* *********************************************************************
Function Name: gameOver
Purpose: To determine if the game is over by checking if all categories have been filled.
Parameters: None
Return Value: A boolean indicating whether all categories are filled.
Algorithm:
	1) Loop through all 12 categories.
	2) Check if any category is still unfilled.
	3) Return true if all categories are filled, otherwise return false.
Reference: None
********************************************************************* */


bool Scorecard::gameOver() {

	// Loops through 12 categories to check if they have been satisfied
	for (int i = 0; i < 12; i++) {
		if (scoreboard1[i][3] == " ") {
			// If an empty category remains, gameOver returns false
			return false;
		}
	}
	// If all 12 categories have been filled, return true
	return true;
}

/* *********************************************************************
Function Name: getPotentialPoints
Purpose: To calculate and display the potential points that can be earned for each available category.
Parameters:
	- dice (int*): A pointer to the array representing the dice values.
	- availCategories (vector<int>): A vector of available categories.
Return Value: The index of the category that yields the highest potential points (int).
Algorithm:
	1) Calculate the score for each available category based on the current dice roll.
	2) Display the potential points for each category.
	3) Return the index of the category with the highest points.
Reference: Tutor
********************************************************************* */

int Scorecard::getPotentialPoints(int* dice, vector<int> availCategories) {
	
	// If available categories have not been listed yet, display them
	if (availCategories.empty()) {
		availCategories = displayAvailable(dice); 
	}

	// Variables to store the score, chosen category to return, and the highest score
	int score = 0;
	int chosenCategory = -1;
	int highestScoreCat = -1;

	cout << "\nPotential points earned from each available category: " << endl;

	// Loop through each available category to calculate and compare potential points
	for (int i = 0; i < availCategories.size(); i++) {
		// Calculate possible score for the current category
		score = calcRunningScore(dice, availCategories[i]);

		// Display the category number, name, and possible points earned
		cout << availCategories[i]+1 << " " << scoreboard1[availCategories[i]][0] << " " << score << endl;

		// Update highest scoring category if the current score is greater
		if (score > highestScoreCat) {
			highestScoreCat = score;
			chosenCategory = availCategories[i];
			
		}
	}

	// Return the chosen category with the highest score
	return chosenCategory;
}

/* *********************************************************************
Function Name: getCategory
Purpose: To retrieve the name of a specific category.
Parameters:
	- category (int): The index of the category.
Return Value: The name of the category (string).
Algorithm:
	1) Return the name of the category based on the given index.
Reference: None
********************************************************************* */

string Scorecard::getCategory(int category) const {
	// Return catgory name
	return scoreboard1[category][0];
}

/* *********************************************************************
Function Name: getWinner
Purpose: To retrieve the name of the winner for a specific category.
Parameters:
	- category (int): The index of the category.
Return Value: The name of the winner for the category (string).
Algorithm:
	1) Return the winner's name for the given category.
Reference: None
********************************************************************* */


string Scorecard::getWinner(int category) const {
	// Return winner of category
	return scoreboard1[category][3];
}

/* *********************************************************************
Function Name: setWinner
Purpose: To set or update the winner of a specific category.
Parameters:
	- category (int): The index of the category.
	- winner (string): The name of the player to be set as the winner.
Return Value: None
Algorithm:
	1) Set the winner for the given category if it is unfilled.
Reference: None
********************************************************************* */

void Scorecard::setWinner(int category, string winner) {
	// Set winner of category if not already filled
	if (winner != " ")
		scoreboard1[category][3] = winner; 
}

/**********************************************************************
Function Name: getScore
Purpose: To retrieve the score for a specific category.
Parameters:
	- category (int): The index of the category.
Return Value: The score for the category (int).
Algorithm:
	1) Return the score for the given category.
Reference: None
**********************************************************************/

int Scorecard::getScore(int category) const  {
	// Return score earned in category
	return scoreboard2[category][0];
}

/**********************************************************************
Function Name: setScore
Purpose: To set or update the score for a specific category.
Parameters:
	- category (int): The index of the category.
	- score (int): The score to be assigned to the category.
Return Value: None
Algorithm:
	1) Set the score for the given category if it is non-negative.
Reference: None
**********************************************************************/

void Scorecard::setScore(int category, int score)  {
	// Set score earned in category
	if (score >= 0)
		scoreboard2[category][0] = score;
}

/* *********************************************************************
Function Name: getRound
Purpose: To retrieve the round number in which a specific category was filled.
Parameters:
	- category (int): The index of the category.
Return Value: The round number for the category (int).
Algorithm:
	1) Return the round number for the given category.
Reference: None
********************************************************************* */

int Scorecard::getRound(int category) const {
	// Return round number of chosen category
	return scoreboard2[category][1];
}

/* *********************************************************************
Function Name: setRound
Purpose: To set or update the round number for a specific category.
Parameters:
	- category (int): The index of the category.
	- round (int): The round number to be assigned to the category.
Return Value: None
Algorithm:
	1) Set the round number for the given category if it is non-negative.
Reference: None
********************************************************************* */

void Scorecard::setRound(int category, int round) {
	// Set round in given category is greater than 0
	if (round >= 0)
		scoreboard2[category][1] = round;
}