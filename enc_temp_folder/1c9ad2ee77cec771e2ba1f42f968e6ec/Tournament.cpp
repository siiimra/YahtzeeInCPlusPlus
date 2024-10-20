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

	// Initialize first round to 1
	int roundNumber = 1;

	// Open selection menu -- prompts user to start mew game or open previous state
	selectMenu(roundNumber);

	cout << "Game has started!\n";

	cout << "\nToss\n\n";

	string tossWinner;

	while (!(scorecard.gameOver())) {

		// Initial toss to decide who goes first
		// If scores are tied, toss dice to determine next player
		if (human->getScore() == computer->getScore()) {
			tossWinner = toss();
		}

		// If human players score is higher, Computer turn
		else if (human->getScore() > computer->getScore()) {
			tossWinner = computer->getName();
		}
		// If computers score is higher, human turn
		else {
			tossWinner = human->getName();
		}

		Round round;

		// Turn logic
		if (tossWinner == human->getName()) {
			cout << "\nHuman Turn " << endl;
			human->turn(scorecard, roundNumber, round);
			cout << "\nComputer Turn " << endl;
			computer->turn(scorecard, roundNumber, round);
		}
		else {
			cout << "\nComputer Turn " << endl;
			computer->turn(scorecard, roundNumber, round);
			cout << "\nHuman Turn " << endl;
			human->turn(scorecard, roundNumber, round); 
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

void Tournament::readFile(int& roundNum, string fileName) {
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
		if (line.find("Round:") != string::npos) {
			// gives string after : and converts to int
			roundNum = stoi(line.substr(line.find(":") + 1));
			break;
		}
	}
	while (getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		if (line.find("Scorecard:") != string::npos) {
			break;
		}
	}

	int categoryRead = 0;
	string winner;
	int score, round;

	while (categoryRead != 12 && getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		istringstream parsedLine(line);
		if (line == "0"){
			scorecard.setScore(categoryRead, 0);
			scorecard.setWinner(categoryRead, " " );
			scorecard.setRound(categoryRead, 0);
			categoryRead++;
			 
		}
		else if (parsedLine >> score >> winner >> round) {
			scorecard.setScore(categoryRead, score); 
			scorecard.setWinner(categoryRead, winner); 
			scorecard.setRound(categoryRead, round);
			categoryRead++;
		}
	}

	for (int i = 0; i < 12; i++) {
		if (scorecard.getWinner(i) != " " && scorecard.getWinner(i) != "Computer") {
			human->setName(scorecard.getWinner(i));
			break;
		}
	}
	file.close();
}

void Tournament::selectMenu(int& roundNumber) {

	int chooseToPlay;

	cout << "1. New Game " << "2. Open Saved Game " << endl;
	cout << "What action would you like to take? ";
	cin >> chooseToPlay;

	while (chooseToPlay != 1 && chooseToPlay != 2) {
		cout << "Invalid input. Please enter a valid option: ";
		cin >> chooseToPlay; 
	}

	if (chooseToPlay == 1) {
		cout << "\nStarting a new game...\n\n";
		roundNumber = 1;
	}
	else if (chooseToPlay == 2) {
		string fileName; 
		cout << "Enter file name: ";
		cin >> fileName; 

		readFile(roundNumber, fileName); 
		human->setScore(scorecard.calcFinalScore(human->getName()));
		computer->setScore(scorecard.calcFinalScore(computer->getName()));
	}
	
}

