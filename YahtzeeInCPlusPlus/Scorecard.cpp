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
		winners[i] = " ";
	}


}

void Scorecard::displayScorecard() {
	cout << "Category\t\t " << "Description\t" << "Score\t" << "Winner\t" << "Points\t" << "Round\t" << endl;

	for (int i = 0; i < 12; i++) {
		if (i == 0) {
			cout << "Aces\t\t" << "Any combination\t" << "Sum of dice with the number 1\t" << winners[i] << '\t' << scoreboard[i][0] << '\t' << scoreboard[i][1] << endl;
		}
		else if (i == 1) {
			cout << "Twos\t" << "Any combination\t" << "Sum of dice with the number 2\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 2) {
			cout << "Threes\t" << "Any combination\t" << "Sum of dice with the number 3\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 3) {
			cout << "Fours\t" << "Any combination\t" << "Sum of dice with the number 4\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 4) {
			cout << "Fives\t" << "Any combination\t" << "Sum of dice with the number 5\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 5) {
			cout << "Sixes\t" << "Any combination\t" << "Sum of dice with the number 6\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 6) {
			cout << "Three of a kind\t" << "At least three dice the same\t" << "Sum of all the dice\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 7) {
			cout << "Four of a kind\t" << "At least four dice the same\t" << "Sum of all the dice\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 8) {
			cout << "Full house\t" << "Three of one number and two of another\t" << "25\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 9) {
			cout << "Four Straight\t" << "Four sequential dice\t" << "30\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 10) {
			cout << "Five Straight\t" << "Five sequential dice\t" << "40\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;
		}
		else if (i == 11) {
			cout << "Yahtzee\t" << "All five dice the same\t" << "50\t" << winners[i] << '\t' << scoreboard[i][0] << scoreboard[i][1] << endl;

		}
	}

}