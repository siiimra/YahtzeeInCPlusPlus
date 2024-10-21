#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Tournament.h"
#include "Round.h"

using namespace std;

// No default constructur because no tournament can be played without human and computer

/* *********************************************************************
Function Name: Tournament (Constructor)
Purpose: To create a Tournament object that initializes references to a Human player and a Computer player.
Parameters:
    - human (Human&): A reference to a Human player object. Passed by reference, not modified by the function.
    - computer (Computer&): A reference to a Computer player object. Passed by reference, not modified by the function.
Return Value: None (Constructor)
Algorithm:
    1) Assign the address of the Human player reference to the member variable 'human'.
    2) Assign the address of the Computer player reference to the member variable 'computer'.
Reference: The parameters are passed by reference, but the constructor stores them as pointers.
********************************************************************* */

Tournament::Tournament(Human& human, Computer& computer) {
	
	
	this->human = &human;
	this->computer = &computer;

}

/* *********************************************************************
Function Name: startGame
Purpose: To manage the main game loop, including player turns, saving the game, and determining the winner.
Parameters: None
Return Value: None
Algorithm:
	1) Initialize the round number to 1.
	2) Open the selection menu for starting a new game or opening a saved game.
	3) Loop until the game is over (All categories have been filled):
	   a) Determine which player should go first using the toss function.
	   b) Create a Round object and allow both players to take their turns.
	   c) Display the running scores of both players.
	   d) Ask if the user wants to save and quit; if yes, write the game state to a file and exit.
	4) Once all categories are filled, announce the final scores and determine the winner.
Reference: None
********************************************************************* */

void Tournament::startGame() {

	// Initialize first round to 1
	int roundNumber = 1;

	// Open selection menu -- prompts user to start mew game or open previous state
	selectMenu(roundNumber);

	cout << "Game has started!\n";

	cout << "\nToss\n\n";

	// String variable that holds the name of the player with the lowest points
	string nextPlayer;

	while (!(scorecard.gameOver())) {

		// If scores are tied, toss dice to determine next player
		// If it is the first round, this is the initial toss that determines the first player
		if (human->getScore() == computer->getScore()) {
			// Assign the next player the toss function 
			// Rolls one dice for each player
			// nextPlayer populated with player who rolled higher dice
			nextPlayer = toss(); 
		}

		// If human players score is higher, Computers turn
		else if (human->getScore() > computer->getScore()) {
			// nextPlayer populated with computers name 
			// Computer player is first to roll 
			nextPlayer = computer->getName(); 
		}
		// If computers score is higher, humans turn
		else {
			// nextPlayer populated with human's name 
			// Human player is first to roll
			nextPlayer = human->getName(); 
		}

		// Creating an object of the round class
		Round round;

		// Turn logic

		// If the human has the lower score, it will go first in the round
		if (nextPlayer == human->getName()) {
			// Announce Human turn first
			cout << "\nHuman Turn " << endl;
			// Call the human turn
			human->turn(scorecard, roundNumber, round);

			if (scorecard.gameOver()) {

				// Announce scores of both players
				cout << "Total score for " << human->getName() << ": " << human->getScore() << endl;
				cout << "Total score for " << computer->getName() << ": " << computer->getScore() << endl;

				// Announce winner

				// If the human and computer have the same score, announce a tie
				if (human->getScore() == computer->getScore()) {
					cout << "Its a tie!";
				}

				// If the human has a higher score, announce the human players name
				else if (human->getScore() > computer->getScore()) {
					cout << "\nWinner: " << human->getName() << " !";
				}
				//If the human has a higher score, announce the computers name
				else {
					cout << "\nWinner: " << computer->getName() << " !";
				}
				break;
			}

			// Announce Computer's turn next
			cout << "\nComputer Turn " << endl;
			// Call the computer turn
			computer->turn(scorecard, roundNumber, round);
		}
		else {
			// If the computer has the lower score, it will go first in the round
			// Announce computers turn first
			cout << "\nComputer Turn " << endl;
			// Call the computer turn
			computer->turn(scorecard, roundNumber, round);

			if (scorecard.gameOver()) {

				// Announce scores of both players
				cout << "Total score for " << human->getName() << ": " << human->getScore() << endl;
				cout << "Total score for " << computer->getName() << ": " << computer->getScore() << endl;

				// Announce winner

				// If the human and computer have the same score, announce a tie
				if (human->getScore() == computer->getScore()) {
					cout << "Its a tie!";
				}

				// If the human has a higher score, announce the human players name
				else if (human->getScore() > computer->getScore()) {
					cout << "\nWinner: " << human->getName() << " !";
				}
				//If the human has a higher score, announce the computers name
				else {
					cout << "\nWinner: " << computer->getName() << " !";
				}
				break;
			}

			// Announce Human's turn next
			cout << "\nHuman Turn " << endl;
			// Call the human turn
			human->turn(scorecard, roundNumber, round); 
		}

		// Announce running score for both players after each round
		cout << human->getName() << "'s score: " << human->getScore() << endl;
		cout << computer->getName() << "'s score: " << computer->getScore() << endl;

		// Increase round number after both players have had a turn
		roundNumber++;

		// char variable that takes input if human player would like to save the state and quit or not
		char saveState;

		// Ask user if they want to quit&save or continue playing
		cout << "Would you quit and save your progress? (y/n): ";
		cin >> saveState;

		// Input validation
		// Prompts for correct input if anything other than y/Y or n/N is given
		while (saveState != 'y' && saveState != 'Y' && saveState != 'n' && saveState != 'N') {
			cout << "Incorrect input. Try again." << endl;
			cin >> saveState; 
		}

		// If human player chooses to save and quit..
		if (saveState == 'y' || saveState == 'Y') {
			// Send current round number to writeFile function
			// Saves current state of game to savedGame.txt
			writeFile(roundNumber);
			break;
		}


	}
	 

}


/* *********************************************************************
Function Name: toss
Purpose: To determine which player goes first by simulating a dice roll for both players.
Parameters: None
Return Value: A string representing the name of the player who won the toss.
Algorithm:
	1) Roll a dice for both the Human and Computer player until there is a clear winner.
	2) Compare the dice values to determine the winner.
	3) Return the name of the player with the higher dice value.
Reference: None
********************************************************************* */

string Tournament::toss() {
	// Dice roll result for the human player
	int humanDice = -1;

	// Dice roll result for the computer player
	int computerDice = -1;

	// Roll dice for both players until there is a clear winner
	while (humanDice == computerDice) {
		// Announce and roll dice for the human player
		cout << human->getName() << " is rolling the dice...\n";
		// Generate random toss for human
		humanDice = rand() % 6 + 1;
		// Announce dice value human recieved
		cout << human->getName() << " rolled: " << humanDice << endl;

		// Announce and roll dice for the computer player
		cout << computer->getName() << " is rolling the dice...\n";
		// Generate random toss for computer
		computerDice = rand() % 6 + 1;
		// Announce dice value computer recieved
		cout << computer->getName() << " rolled: " << computerDice << endl;

		// If both players roll the same value, announce a tie and re-roll
		if (humanDice == computerDice) {
			cout << "It's a tie! Re-rolling...\n";
		}
	}

	// Determine the winner of the toss and return the name of the next player
	if (humanDice > computerDice) {
		// Human player wins the toss
		cout << human->getName() << " won the toss.\n";
		return human->getName();
	}
	else {
		// Computer player wins the toss
		cout << computer->getName() << " won the toss.\n";
		return computer->getName();
	}
}

/* *********************************************************************
Function Name: writeFile
Purpose: To save the current game state, including the round number and scorecard details, to a file.
Parameters:
	- roundNum (const int): The current round number to be saved.
Return Value: None
Algorithm:
	1) Open the file "savedGame.txt" for writing.
	2) If the file cannot be opened, display an error message and return.
	3) Write the current round number to the file.
	4) Write the scorecard details, including scores, winners, and rounds won, for all 12 categories.
	5) If a category is not filled, write a default value of 0.
	6) Close the file.
Reference: None
********************************************************************* */

void Tournament::writeFile(const int roundNum) {
	// Write to file called "savedGame.txt"
	ofstream file("savedGame.txt");

	// If file doesnt exist, output error
	if (!file) {
		cout << "ERROR: File not found ";
		return;
	}

	// Indicate round user is leacing off on
	file << "Round: " << roundNum << " \n";

	// Output the beginning of the scorecard
	file << "Scorecard: \n";

	// For all 12 categories...
	// If already filled, save Score, Winner, and Round won in that order
	// If not filled, save as 0
	for (int i = 0; i < 12; i++) {
		if (scorecard.getWinner(i) != " ") {
			file << scorecard.getScore(i) << " " << scorecard.getWinner(i) << " " << scorecard.getRound(i) << '\n';
		}
		else {
			file << "0" << endl; 
		}
	}

	// Close file
	file.close(); 


}

/* *********************************************************************
Function Name: readFile
Purpose: To read the game state from a file, including the round number and scorecard details, to resume the game.
Parameters:
	- roundNum (int&): Reference to an integer that will hold the current round number after reading from the file.
	- fileName (string): The name of the file to be opened and read.
Return Value: None
Algorithm:
	1) Open the file for reading.
	2) If the file cannot be opened, prompt the user to enter a valid file name until successful.
	3) Read the file line by line:
	   a) Extract the round number from the file.
	   b) Skip lines until the "Scorecard:" section is found.
	   c) Read the scorecard details for each category and update the scorecard.
	4) Update the human player's name if found in the scorecard.
	5) Close the file.
Reference: None
********************************************************************* */

void Tournament::readFile(int& roundNum, string fileName) {
	// Open the file name given previously for reading
	ifstream file(fileName);

	// Loop to handle file not found or incorrect file name
	while (!file) { 
		// Prompt user to enter a valid file name
		cout << "ERROR: File not found. Enter file name again: ";
		cin >> fileName;
		// Clear the file state and attempt to open the file again
		file.clear(); 
		file.open(fileName); 
	}


	// Variable to hold each line of the file
	string line;

	// Loop to read lines from the file
	while (getline(file, line)) {
		// Skip empty lines
		if (line.empty()) {
			continue;
		}

		// Check if the line contains the round number information
		if (line.find("Round:") != string::npos) {
			// Extract the round number from the line 
			// gives string after : and converts round number to int
			roundNum = stoi(line.substr(line.find(":") + 1));
			break;
		}
	}
	// Loop to find the "Scorecard:" section in the file
	while (getline(file, line)) {

		// Skip empty lines
		if (line.empty()) {
			continue;
		}
		// Break the loop when "Scorecard:" is found
		if (line.find("Scorecard:") != string::npos) {
			break;
		}
	}

	// int variable that holds which of the 12 categories is being read
	int categoryRead = 0;
	// string variable that reads winner from each line
	string winner;
	// int variables that read score and round from each line
	int score, round;

	// Loop to read the scorecard details (maximum of 12 categories)
	while (categoryRead != 12 && getline(file, line)) {
		
		// Skip empty lines
		if (line.empty()) {
			continue;
		}
		// Parse the line to extract score, winner, and round information
		istringstream parsedLine(line);

		// Set default values if no winner
		if (line == "0"){
			scorecard.setScore(categoryRead, 0);
			scorecard.setWinner(categoryRead, " " );
			scorecard.setRound(categoryRead, 0);
			categoryRead++;
			 
		}
		// Set score, winner, and round details for the current category
		else if (parsedLine >> score >> winner >> round) {
			scorecard.setScore(categoryRead, score); 
			scorecard.setWinner(categoryRead, winner); 
			scorecard.setRound(categoryRead, round);
			categoryRead++;
		}
	}

	// Updates human name according to scorecard
	for (int i = 0; i < 12; i++) {
		if (scorecard.getWinner(i) != " " && scorecard.getWinner(i) != "Computer") {
			// Update human's name if it is found in the scorecard
			human->setName(scorecard.getWinner(i));
			break;
		}
	}

	// Close the file after reading
	file.close();

	scorecard.displayAll();
}

/* *********************************************************************
Function Name: selectMenu
Purpose: To prompt the user to either start a new game or open a saved game state.
Parameters:
	- roundNumber (int&): Reference to an integer that will hold the round number, which is updated based on user selection.
Return Value: None
Algorithm:
	1) Display options for starting a new game or opening a saved game.
	2) Prompt the user for their choice and validate the input.
	3) If the user chooses a new game, initialize the round number to 1.
	4) If the user chooses to open a saved game, prompt for the file name and call readFile() to load the game state.
	5) Update player scores based on the loaded game state.
Reference: None
********************************************************************* */


void Tournament::selectMenu(int& roundNumber) {

	// Variable that will hold the humans choice to begin a new game or open saved state
	int chooseToPlay;

	// Announce options to begin new game or open saved game
	cout << "1. New Game " << "2. Open Saved Game " << endl;
	// Ask end user desired course of action
	cout << "What action would you like to take? ";

	// Recieve input of humans action and assign to chooseToPlay
	cin >> chooseToPlay;

	// Input validation
	// If a user enters a number other than 1 or 2..
	while (chooseToPlay != 1 && chooseToPlay != 2) {
		// Prompt for a valid input
		cout << "Invalid input. Please enter a valid option: ";

		//Assign chooseToPlay with correct input
		cin >> chooseToPlay; 
	}

	// If user decides to start a new game..
	if (chooseToPlay == 1) {
		// Announce that program is beginning a new game
		cout << "\nStarting a new game...\n\n";

		// Set round number to 1 since we are starting fresh
		roundNumber = 1;
	}

	// If user decides to open from a saved state...
	else if (chooseToPlay == 2) {

		// String variable that holds name of file to be opened
		string fileName; 

		// Prompt user to enter filename
		cout << "Enter file name: ";

		// Populate fileName with desired input
		// Input validation done soon in readFile() function
		cin >> fileName; 

		// Call readFile to open from saved state
		readFile(roundNumber, fileName); 

		// Set score for each player based on previous state
		human->setScore(scorecard.calcFinalScore(human->getName()));
		computer->setScore(scorecard.calcFinalScore(computer->getName()));
	}
	
}

