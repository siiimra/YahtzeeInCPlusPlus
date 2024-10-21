//************************************************************
//* Name:  Simra Ahmed
//* Project : Yahtzee in C++
//* Class : CMPS 366 01 Organization of Programming Languages
//* Date : 10/21/2024
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
#include "Tournament.h"
using namespace std;

/* *********************************************************************
Function Name: main
Purpose: To initialize and start a game of Yahtzee between a human and a computer.
Parameters: None
Return Value: Integer value indicating the success of the program execution (0 for successful completion).
Algorithm:
    1) Prompt the user to enter their name.
    2) Seed the random number generator to ensure randomness for the dice rolls.
    3) Create instances of the Human player and Computer player.
    4) Create a Tournament object that manages the game and start the game by calling the startGame() function.
Reference: None
********************************************************************* */

int main()
{

    string name;
    cout << "Please enter your name: ";
    cin >> name;

    //Seed random number generator
    srand(time(0));

    // Initialize Human player
    Human human(name);
 
    // Initialize Computer player
    Computer computer("Computer");

    // Create tournament -- cannot exist without human and player objects
    Tournament tournament(human, computer); 

    tournament.startGame();    
    

    return 0;
  
}

