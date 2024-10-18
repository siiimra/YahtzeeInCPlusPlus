#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
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
	int roundNumber = 1;
	while (!(scorecard.gameOver())) {
		Round round;
		if (tossWinner == human->getName()) {
			human->turn(scorecard, roundNumber, round);
			computer->turn(scorecard, roundNumber, round);
		}
		else {
			computer->turn(scorecard, roundNumber, round); 
			human->turn(scorecard, roundNumber, round); 
		}
		if (human->getScore() == computer->getScore()) {
			tossWinner = toss();
		}
		else if (human->getScore() > computer->getScore()) {
			tossWinner = computer->getName();
		}
		else {
			tossWinner = human->getName(); 
		}
		roundNumber++;
		char saveState;
		cout << "Would you quit and save your progress? (y/n): ";
		cin >> saveState;
		while (saveState != 'y' && saveState != 'Y' && saveState != 'n' && saveState != 'N') {
			cout << "Incorrect input. Try again." << endl;
			cin >> saveState; 
		}
		if (saveState == 'y' || saveState == 'Y') {
			writeFile(roundNumber);
			break;
		}


	}

	if (scorecard.gameOver()) {
		cout << "Total score for " << human->getName() << human->getScore() << endl;
		cout << "Total score for " << computer->getName() << computer->getScore() << endl;

		if (human->getScore() == computer->getScore()) {
			cout << "Its a tie!";
		}
		else if (human->getScore() > computer->getScore()) {
			cout << "\nWinner: " << human->getName() << " !";
		}
		else {
			cout << "\nWinner: " << computer->getName() << " !";
		}
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

void Tournament::writeFile(const int roundNum) {
	ofstream file("savedGame.txt");

	if (!file) {
		cout << "ERROR: File not found ";
		return;
	}

	file << "Round: " << roundNum << " \n";

	file << "Scorecard: \n";

	for (int i = 0; i < 12; i++) {
		if (scorecard.getWinner(i) != " ") {
			file << scorecard.getScore(i) << " " << scorecard.getWinner(i) << " " << scorecard.getRound(i) << '\n';
		}
		else {
			file << "0" << endl; 
		}
	}

	file.close(); 


}

void Tournament::readFile(int& roundNum, string fileName, Human& human) {
	ifstream file(fileName);

	if (!file) { 
		cout << "ERROR: File not found ";
		return;
	}

	string line;

	while (getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		if (line.find("Round:")) {
			// gives string after : and converts to int
			roundNum = stoi(line.substr(line.find(":") + 1));
			break;
		}
	}
	while (getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		if (line.find("Scorecard:")) {
			break;
		}
	}

	int categoryRead = 0;
	string winner;
	int score, round;

	while (categoryRead != 12) {
		if (line.empty()) {
			continue;
		}
		istringstream parsedLine(line);

		parsedLine >> score >> winner >> round;

		scorecard.setScore(categoryRead, score);
		scorecard.setWinner(categoryRead, winner);
		scorecard.setRound(categoryRead, round);
	}
	for (int i = 0; i < 12; i++) {
		if (scorecard.getWinner(i) != " " && scorecard.getWinner(i) != "Computer") {
			human.setName(scorecard.getWinner(i));
			break;
		}
	}
	file.close();
}