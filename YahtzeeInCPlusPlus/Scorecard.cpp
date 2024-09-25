#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include "Scorecard.h"

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
	scoreboard1[7][2] = "Sum of all dices ";
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



void Scorecard::displayScorecard()
{
	cout << "Category\t" << "Description\t\t\t" << "Score\t\t\t\t" << "Winner\t\t" << "Points\t" << "Round\t" << endl;

	for (int i = 0; i < 12; i++)
	{
		cout << i+1 << ' ' << scoreboard1[i][0] << ' ' << scoreboard1[i][1] << ' ' << scoreboard1[i][2] << ' ' << scoreboard1[i][3] << ' ' << scoreboard2[i][0] << ' ' << scoreboard2[i][1] << ' ' << endl;
	}
}

int Scorecard::calcScore(string name)
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
	if (scoreboard1[index][3] != " ") {
		scoreboard1[index][3] = name;
		scoreboard2[index][0] = score;
		scoreboard1[index][1] = round;
	}

}

void Scorecard::displayAvailable() {
	for (int i = 0; i < 12; i++) {
		if (scoreboard1[i][3] == " ") {
			cout << i + 1 << ' ' << scoreboard1[i][0] << ' ' << scoreboard1[i][1] << ' ' << scoreboard1[i][2] << ' ' << scoreboard1[i][3] << ' ' << scoreboard2[i][0] << ' ' << scoreboard2[i][1] << ' ' << endl;
		}
	}
}