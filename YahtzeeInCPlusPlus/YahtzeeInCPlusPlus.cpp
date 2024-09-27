//************************************************************
//* Name:  Simra Ahmed
//* Project : Yahtzee in C++
//* Class : CMPS 366 01 Organization of Programming Languages
//* Date : 9/24/2024
//************************************************************


#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "Human.h"
#include "Scorecard.h"
#include "Computer.h"
#include "Round.h"
using namespace std;


/* *********************************************************************
Function Name: selectMenu
Purpose: To calculate the average grade in a class
Parameters:
            chooseToPlay - int value given by the user to determine if
            they want to play a game of Yahtzee or not
Return Value: 
            Status code for game
            Function again if input is invalid
Algorithm:
            1) Generates a new game if user chooses yes
            2) Exits program if user says no
            3) Says input is invalid if user inputs anything other than 1 or 2
Reference: none
********************************************************************* */
int selectMenu(int& chooseToPlay) {
    if (chooseToPlay == 1) {
        cout << "Starting a new game...\n\n";
        return 1; // Start the game
    }
    else if (chooseToPlay == 2) {
        cout << "Goodbye!\n";
        exit(0); // Exit the game
    }
    else {
        cout << "Invalid input. Please enter a valid option: ";
        cin >> chooseToPlay;
        return selectMenu(chooseToPlay); // Recurse until valid input
    }
}


int main()
{
    ////Variable that allows user to choose to select new game or exit game
    //int chooseToPlay;
    //srand(time(0));

    //////Display welcome screen with options
    //cout << "Welcome! Would you like to begin a game of Yahtzee?" << endl;
    //cout << "1. New Game " << "2. Exit Game" << endl;
    //cout << "What action would you like to take? ";
    //cin >> chooseToPlay;
    //selectMenu(chooseToPlay);

    string name;
    cout << "Please enter your name: ";
    cin >> name;

    ////// Seed random number generator
    srand(time(0));

    ////// Initialize Human player
    Human human1(name);

    ////// Vector to store dice values (5 dice for the game)
    //vector<int> dice(5);

    //// Test human player rolling the dice using the regular for-loop
    //human1.rollDice(dice);

    Scorecard scorecard;
    //scorecard.displayScorecard();

    Computer computer("Computer");
    //computer.rollDice(dice);

    Round round;

    /*round.toss("Simra", "Computer");
    round.rollDice("Simra");*/
    //int test[5] = { 5, 5, 1, 1, 2 };
    //cout << checkConsecutive(test, 4);
    
    round.playRound(human1, computer, scorecard, 1);
   

    return 0;
  
}

