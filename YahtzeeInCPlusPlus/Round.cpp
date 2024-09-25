#include "Round.h"
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
		cout << name1 << " won this round.\n";
		return name1;
	}
	else {
		cout << name2 << " won this round.\n";
		return name2;
	}
}

void Round::playRound(Human& human, Computer& computer, Scorecard& scorecard) {

	string tossWinner = toss(human.getName(), computer.getName());
	rollDice(tossWinner);

}

void Round::rollDice(string name) {

	// Roll the dice using a regular for-loop
	for (int i = 0; i < 5; ++i) {
		diceRoll[i] = rand() % 6 + 1;
	}

	// Display the dice values using a regular for-loop
	cout << name << " rolled: ";
	for (int i = 0; i < 5; ++i) {
		cout << diceRoll[i] << " ";
	}
	cout << endl;

}

