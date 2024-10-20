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


Scorecard::Scorecard()
{

	for (int i = 0; i < 12; i++) {

		for (int j = 0; j < 2; j++) {
			scoreboard2[i][j] = 0;
		}
	}

	for (int i = 0; i < 12; i++) {
		scoreboard1[i][3] = " ";
	}

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



int Scorecard::calcFinalScore(string name)
{
	int score = 0;
	for (int i = 0; i < 12; i++)
	{
		if (scoreboard1[i][3] == name)
		{
			score += scoreboard2[i][0];
		}
	}
	return score;
}

void Scorecard::updateScorecard(int index, string name, int score, int round)
{
	if (scoreboard1[index][3] == " ") {
		scoreboard1[index][3] = name;
		scoreboard2[index][0] = score;
		scoreboard2[index][1] = round;
	}

}

void Scorecard::displayAll() {


	cout << endl;
	cout << setw(16) << "Category" << setw(40) << "Description" << setw(30) << "Score" << setw(25) << "Winner" << setw(10) << "Points" << setw(7) << "Round" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < 12; i++) {
		
		if (i < 9) {
			cout << " " << i + 1;
		}
		else {
			cout << i + 1;
		}
		cout << setw(16) << scoreboard1[i][0] << setw(40)
			<< scoreboard1[i][1] << setw(40)
			<< scoreboard1[i][2] << setw(15)
			<< scoreboard1[i][3] << setw(10)
			<< scoreboard2[i][0] << setw(7)
			<< scoreboard2[i][1] << endl;

	}
}


bool Scorecard::checkConsecutive(int* dice, int count1) {
	bool exists[7] = { false }; // Track which numbers exist

	for (int i = 0; i < 5; i++) {
		exists[dice[i]] = true;
	}

	// Now check for consecutive sequences
	for (int i = 1; i <= 6 - count1 + 1; i++) {
		bool isConsecutive = true;
		for (int j = i; j < i + count1; j++) {
			if (!exists[j]) {
				isConsecutive = false;
				break;
			}
		}
		if (isConsecutive) {
			return true;
		}
	}

	return false;
}


vector<int> Scorecard::displayAvailable(int* dice) {

	vector<int> availableCategories;

	cout << "The following categories can be filled: " << endl;

	for (int i = 0; i < 12; i++) {
		if (scoreboard1[i][3] == " ") {
			if (i < 6) {
				availableCategories.push_back(i);
				cout << i + 1 << ' ' << scoreboard1[i][0] << ' ' << scoreboard1[i][1] << ' ' << scoreboard1[i][2] << ' ' << endl;
			}
			else if (i == 6) {
				//Check if there are 3 same dice
				bool check = 0;
				for (int j = 1; j <= 6; j++) {
					int count = 0;

					for (int k = 0; k < 5; k++) {
						if (dice[k] == j) {
							count++;
						}
					}
					if (count >= 3) {
						check = 1;
						break;
					}
				}
				if (check == 1){
					availableCategories.push_back(i);
					cout << i + 1 << ' ' << scoreboard1[i][0] << ' ' << scoreboard1[i][1] << ' ' << scoreboard1[i][2] << ' ' << endl;
				}
			}
			else if (i == 7) {
				bool check = 0;

				for (int j = 1; j <= 6; j++) {
					int count = 0;

					//Move through 5 dice
					for (int k = 0; k < 5; k++) {
						if (dice[k] == j) {
							count++;
						}
					}
					if (count >= 4) {
						check = 1;
						break;
					}
				}
				if (check == 1) {
					availableCategories.push_back(i);
					cout << i + 1 << ' ' << scoreboard1[i][0] << ' ' << scoreboard1[i][1] << ' ' << scoreboard1[i][2] << ' ' << endl;

				}
			}
			else if (i == 8) {
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
					continue;
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


				if (check == 1 && check2 == 1) {
					availableCategories.push_back(i);
					cout << i + 1 << ' ' << scoreboard1[i][0] << ' ' << scoreboard1[i][1] << ' ' << scoreboard1[i][2] << ' ' << endl;

				}
			}
			else if (i == 9 || i == 10) {
				if (checkConsecutive(dice, i-5)) {
					availableCategories.push_back(i);
					cout << i + 1 << ' ' << scoreboard1[i][0] << ' ' << scoreboard1[i][1] << ' ' << scoreboard1[i][2] << ' ' << endl;
				}
			}
			else if (i == 11) {
				bool allSame = true;
				for (int j = 1; j < 5; j++) {
					if (dice[j] != dice[0]) {
						allSame = false;
						break;
					}
				}
				if (allSame) {
					availableCategories.push_back(i);
					cout << i + 1 << ' ' << scoreboard1[i][0] << ' ' << scoreboard1[i][1] << ' ' << scoreboard1[i][2] << ' ' << scoreboard1[i][3] << ' ' << scoreboard2[i][0] << ' ' << scoreboard2[i][1] << ' ' << endl;
				
				}
			}
		}
	}

	return availableCategories;
}

int Scorecard::calcRunningScore(int* dice, int category) {
	int score = 0;
	if (category < 6) {
		int count = 0;
		for (int j = 0; j < 5; j++) {
			if (dice[j] == (category+1)) {
				count++;
			}
		}
		score = count * (category + 1);
	}
	else if (category == 6 || category == 7) {
		
		for (int i = 0; i < 5; i++) {
			score += dice[i];
		}
	}
	else if (category == 8) {
		score = 25;
	}
	else if (category == 9) {
		score = 30;
	}
	else if (category == 10) {
		score = 40;
	}
	else if (category == 11) {
		score = 50;
	}
	return score;
}

bool Scorecard::gameOver() {

	for (int i = 0; i < 12; i++) {
		if (scoreboard1[i][3] == " ") {
			return false;
		}
	}
	return true;
}

int Scorecard::potentialPoints(int* dice, vector<int> availCategories) {
	
	if (availCategories.empty()) {
		vector<int> availCategories = displayAvailable(dice); 
	}

	
	int score = 0;
	int chosenCategory = -1;
	int highestScoreCat = -1;

	cout << "\nPotential points earned from each available category: " << endl;

	for (int i = 0; i < availCategories.size(); i++) {
		score = calcRunningScore(dice, availCategories[i]);
		cout << availCategories[i]+1 << " " << scoreboard1[availCategories[i]][0] << " " << score << endl;
		if (score > highestScoreCat) {
			highestScoreCat = score;
			chosenCategory = availCategories[i];
			
		}
	}
	return chosenCategory;
}

string Scorecard::getCategory(int category) {
	return scoreboard1[category][0];
}

string Scorecard::getWinner(int category) {
	return scoreboard1[category][3];
}

void Scorecard::setWinner(int category, string winner) {
	scoreboard1[category][3] = winner; 
}

int Scorecard::getScore(int category) {
	return scoreboard2[category][0];
}
void Scorecard::setScore(int category, int score) {
	scoreboard2[category][0] = score;
}

int Scorecard::getRound(int category) {
	return scoreboard2[category][1];
}
void Scorecard::setRound(int category, int round) {
	scoreboard2[category][1] = round;
}