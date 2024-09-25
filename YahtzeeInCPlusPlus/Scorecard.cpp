#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include "Scorecard.h"

using namespace std;

Scorecard::Scorecard()
{

	for (int i = 0; i < 12; i++) {
		
		for (int j = 0; j < 2; j++){
			scoreboard[i][j] = 0;
		}
	}

	for (int i = 0; i < 12; i++) {
		winners[i] = "Example";
	}


}

void Scorecard::displayScorecard() {
	cout << "Category\t" << "Description\t\t\t" << "Score\t\t\t\t" << "Winner\t\t" << "Points\t" << "Round\t" << endl;

	for (int i = 0; i < 12; i++) {
		if (i == 0) {
			cout << "Aces\t\t" << "Any combination\t\t\t" << "Sum of dice with the number 1\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 1) {
			cout << "Twos\t\t" << "Any combination\t\t\t" << "Sum of dice with the number 2\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 2) {
			cout << "Threes\t\t" << "Any combination\t\t\t" << "Sum of dice with the number 3\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 3) {
			cout << "Fours\t\t" << "Any combination\t\t\t" << "Sum of dice with the number 4\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 4) {
			cout << "Fives\t\t" << "Any combination\t\t\t" << "Sum of dice with the number 5\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 5) {
			cout << "Sixes\t\t" << "Any combination\t\t\t" << "Sum of dice with the number 6\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 6) {
			cout << "3 of a kind\t" << "At least 3 dice the same\t" << "Sum of all the dice\t\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 7) {
			cout << "4 of a kind\t" << "At least 4 dice the same\t" << "Sum of all the dice\t\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 8) {
			cout << "Full house\t" << "3 of one number and 2 of another\t" << "25\t\t\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 9) {
			cout << "Four Straight\t" << "4 sequential dice\t\t\t" << "30\t\t\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 10) {
			cout << "Five Straight\t" << "5 sequential dice\t\t\t" << "40\t\t\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 11) {
			cout << "Yahtzee\t\t" << "All 5 dice the same\t\t\t" << "50\t\t\t" << winners[i] << "\t\t" << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;

		}
	}
	cout << '\n';
}

int Scorecard::calcScore(string name)
{
	int score = 0;
	for (int i = 0; i < 12; i++)
	{
		if (winners[i] == name)
		{
			score += scoreboard[i][0];
		}
	}
	return score;
}

void Scorecard::updateScorecard(int index, string name, int score, int round)
{
	if (winners[index] != " ") {
		winners[index] = name;
		scoreboard[index][0] = score;
		scoreboard[index][1] = round;
	}
	
}