#include <iostream>
#include <string>
#include <vector>
#include "Tournament.h"
#include "Round.h"

using namespace std;

// no default constructur because no tournament can be played without human and computer

Tournament::Tournament(Human& human, Computer& computer) {
	
	
	this->human = &human;
	this->computer = &computer;

}

void Tournament::startGame() {
	cout << "Game has started!\n";
	cout << "Toss\n";

	string tossWinner = toss();
	int nextPlayer = -1;
	int roundNumber = 1;
	while ((scorecard.gameOver())) {
		Round round;
		nextPlayer = round.playRound(*human, *computer, scorecard, roundNumber, tossWinner);
		if (nextPlayer == 0) {
			tossWinner = toss();
		}
		else if (nextPlayer == 1) {
			tossWinner = computer->getName();
		}
		else {
			tossWinner = human->getName(); 
		}
		roundNumber++;
	}
	

}

string Tournament::toss() {

	//Dice For Human
	int dice1 = -1;

	//Dice for Computer
	int dice2 = -1;

	//Dice roll that determines the next player
	//Re-rolls if tied
	while (dice1 == dice2) {
		cout << human->getName() << " is rolling the dice...\n";
		dice1 = rand() % 6 + 1;
		cout << human->getName() << " rolled: " << dice1;
		cout << endl;

		//Dice roll for computer
		cout << computer->getName() << " is rolling the dice...\n";
		dice2 = rand() % 6 + 1;
		cout << computer->getName() << " rolled: " << dice2;
		cout << endl;
		if (dice1 == dice2) {
			cout << "It's a tie! Re-rolling...\n";
		}
	}


	if (dice1 > dice2) {
		cout << human->getName() << " won the toss.\n";
		return human->getName();
	}
	else {
		cout << computer->getName() << " won the toss.\n";
		return computer->getName();
	}
}