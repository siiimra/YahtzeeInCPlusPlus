#include "Human.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/* *********************************************************************
Function Name: Human (Constructor)
Purpose: To initialize a new Human player object and welcome the player to the game.
Parameters:
	- name1 (string): The name of the player being created. It is passed by value.
Return Value: None (constructor)
Algorithm:
	1) Call the base class constructor to initialize the player.
	2) Display a welcome message for the new player.
Reference: None
**********************************************************************/

Human::Human(string name1) : Player(name1) {
    //Welcomes human player to Yahtzee
    cout << "Welcome to Yahtzee, " << name1 << "!" << endl;



}

/* *********************************************************************
Function Name: turn
Purpose: To handle a human player's turn, allowing them to roll and re-roll dice, receive help, and choose a category to fill.
Parameters:
	- scorecard (Scorecard&): A reference to the scorecard object. It is modified to update scores and categories filled during the player's turn.
	- roundNum (int): The current round number.
	- round (Round&): A reference to the round object that manages dice rolls and re-rolls.
Return Value: None
Algorithm:
	1) Ask the player if they want to input custom dice values or roll randomly.
	2) If the player chooses custom input, validate and assign their values; otherwise, roll randomly.
	3) Allow the player to re-roll twice if desired, offering help for category selection.
	4) Display the current scorecard and ask the player to select a category.
	5) Validate the chosen category and update the scorecard with the player's choice.
	6) Calculate the player's final score based on the categories they have filled.
	7) Display the updated scorecard.
Reference: None
**********************************************************************/

void Human::turn(Scorecard& scorecard, int roundNum, Round& round) {

	vector<bool> rerolled(5, true);

	// Indicate that it is the human players first roll
	cout << "\nRoll 1\n";

	// Ask user if they would like to input their own dice
	cout << "Would you like to input your own dice? (y/n) ";

	// Char variable that holds user choice to input own dice or not
	char choice;

	// Get user input to see if they want intentional or random dice
	cin >> choice;

	// Input validation
	// Prompt for a valid choice if input is not y/Y or n/N
	while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
		cout << "Invalid choice, input Y or N: ";
		cin >> choice;
	}

	// If user chooses to input their own dice..
	if (choice == 'Y' || choice == 'y') {

		// Variable that holds custom dice value
		int diceChoice;

		// Move through five dice
		for (int i = 0; i < 5; i++) {

			// Prompt user to enter values of the five die
			cout << "Enter dice " << i + 1 << ": ";

			// Recieve custom dice input
			cin >> diceChoice;

			// Input validation
			// Prompt for valid input if user attempts to populate diceChoice with values 
			// less than 1 or greather than 6
			while (diceChoice < 1 || diceChoice > 6) {
				cout << "Invalid dice input. Dice can only be in range 1-6. ";
				cin >> diceChoice;
			}

			// Populate the dice roll array with the custom values
			(round.setDice(diceChoice, i));
		}

	}

	// If user opts out of inputting custom dice..
	else if (choice == 'N' || choice == 'n') {
		// Randomly generate and display 5 dice
		round.rollDice(name);
	}

	// Asks user if they would like to reroll dice after initial roll
	cout << "Would you like to change any of your dice? (y/n/? for help): ";

	// Get input from user if they would like to keep or reroll dice
	cin >> choice;

	// Input validation
	// Prompt for valid input if the input is not y/Y, n/N, or ?
	while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' && choice != '?') {
		cout << "Incorrect input. Try again." << endl;
		cin >> choice;
	}

	// HELP MODE
	
	// If user inputs ?, enter help mode
	if (choice == '?') {
		cout << "\nHELP MODE" << endl << endl;

		// Display current dice user has
		round.displayDice(); 
		cout << endl;

		// Variable that calls getPotentialPoints function
		// Assigned and returns the category that will earn highest points
		int highestPoints = scorecard.getPotentialPoints(round.getDice());

		// Suggests user which category to fill based on current roll 
		// Uses the highestPoints variable to output a category and the potential points
		cout << "Based on your current roll, you should fill " 
			<< scorecard.getCategory(highestPoints) 
			<< " because it will earn you the highest number of points. (" 
			<< scorecard.calcRunningScore(round.getDice(), highestPoints) 
			<< ")" << endl;
		
		// If more points can potentially be earned, use shouldReroll() function 
		// to suggest which dice to re-roll and which category to aim for
		round.shouldReroll(round.getDice(), scorecard, true);

		// Ask the user if they would like to change any dice
		cout << "\nWould you like to change any of your dice? (y/n): ";

		// Recieve user input -- see if human wants to re-roll or stand
		cin >> choice;

		// Input validation
		// Prompt for valid input if the input is not y/Y or n/N
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
			cout << "Incorrect input. Try again." << endl;
			cin >> choice;
		}
	}

	// Go in for second roll if human decides to re-roll
	if (choice == 'y' || choice == 'Y') {
		cout << "\nRoll 2\n";

		// Display dice after asking user for intentional or random regeneration of dice for each dice
		round.reRoll(name, rerolled);

		// Asks user if they would like to try for a third re roll
		cout << "Would you like to change any of your dice? (y/n/? for help): ";

		//char inputDice;
		cin >> choice;

		// Input validation
		// Prompt for valid input if the input is not y/Y, n/N, or ?
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' && choice != '?') {
			cout << "Incorrect input. Try again." << endl;
			cin >> choice;
		}

		// HELP MODE
		// If user inputs ?, enter help mode
		if (choice == '?') {
			cout << "\nHELP MODE" << endl << endl;

			// Display current dice user has
			round.displayDice();
			cout << endl;

			// Variable that calls getPotentialPoints function
			// Assigned and returns the category that will earn highest points
			int highestPoints = scorecard.getPotentialPoints(round.getDice());
			int bestCategory = -1;


			// If there is a category that can be filled..
			if (bestCategory != -1 ){
				cout << "Based on the final roll, the computer will fill "
					<< scorecard.getCategory(bestCategory)
					<< " because it will earn the highest number of points ("
					<< highestPoints << ")." << endl;

				// Update scorecard with the computer's chosen category
				scorecard.updateScorecard(bestCategory, name, highestPoints, roundNum);
			}
			else {
				cout << "No category can be filled" << endl;
			}


			// If more points can potentially be earned, use shouldReroll() function 
			// to suggest which dice to re-roll and which category to aim for
			round.shouldReroll(round.getDice(), scorecard, true);

			// Ask the user if they would like to change any dice
			cout << "\nWould you like to change any of your dice? (y/n): ";

			// Get input from user if they would like to keep or reroll dice
			cin >> choice;

			// Input validation
			// Prompt for valid input if the input is not y/Y or n/N
			while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
				cout << "Incorrect input. Try again." << endl;
				cin >> choice;
			}
		}

		// If user decides to re roll again.. 
		if (choice == 'y' || choice == 'Y') {
			cout << "\nRoll 3\n";
			// Display dice after asking user for intentional 
			// or random regeneration of dice for each dice
			round.reRoll(name, rerolled);
		}
	}

	// Display scorecard after each player finishes rolling dice
	scorecard.displayAll();

	cout << endl;

	// Int vector that holds the current available categories
	vector<int> displayGood;

	// displayGood assigned to called displayAvailable function
	// Which outputs current available categories
	displayGood = scorecard.displayAvailable(round.getDice());


	// Variable that takes input for which category the player would like to pursue
	int chooseCategory;

	// Prompt user to choose a category to fill
	// They can also enter -2 to enter help mode
	// If no category can be filled, -1 can be entered to move on to next player/round/turn
	cout << "\nChoose a category to fill (-2 for help, -1 if no category can be filled): ";

	// Take input for desired category that human wants to fill
	cin >> chooseCategory;

	chooseCategory--;


	// Input validation
	// Makes sure the chosen category is available and valid for dice chosen
	while (!(round.checkIsNumberInVector(displayGood, chooseCategory)) && chooseCategory != -3 && chooseCategory != -2) {
		cout << "Please input a valid input. ";
		cin >> chooseCategory;
	}

	// HELP MODE
	// Helps user choose a category
	if (chooseCategory == -3) {
		cout << "\nHELP MODE\n";
		cout << endl;

		// Display current dice
		round.displayDice(); 

		// Variable that calls getPotentialPoints function
		// Assigned and returns the category that will earn highest points
		int highestPoints = scorecard.getPotentialPoints(round.getDice());

		// Suggests user which category to fill based on current roll 
		// Uses the highestPoints variable to output a category and the potential points
		cout << "\nBased on your current roll, you should fill " 
			<< scorecard.getCategory(highestPoints) 
			<< " because it will earn you the highest number of points. (" 
			<< scorecard.calcRunningScore(round.getDice(), highestPoints) 
			<< ")" << endl;

		// Prompts user to choose a category
		// If nothing can be fufilled, -1 can be entered and next player rolls
		cout << "\nChoose a category to fill (-1 if no category can be filled): ";

		// Take input for desired category that human wants to fill
		cin >> chooseCategory;
		chooseCategory--;

		// Input validation
		// Makes sure the chosen category is available and valid for dice chosen
		while (!(round.checkIsNumberInVector(displayGood, chooseCategory)) && chooseCategory != -2) {
			cout << "Please input a valid input. ";
			cin >> chooseCategory;
		}
	}
	//Running scores players
	int humanScore = 0;

	if (round.checkIsNumberInVector(displayGood, chooseCategory)) {
		// Generate score earned by category using calcRunningScore() function
		humanScore = scorecard.calcRunningScore(round.getDice(), chooseCategory);

		// Save score, human winner, and round to chosen category
		scorecard.updateScorecard(chooseCategory, name, humanScore, roundNum); 
	}

	// Update human score by calculating which categories it has won
	setScore(scorecard.calcFinalScore(name));

	// Display updated scorecard
	scorecard.displayAll();
}
