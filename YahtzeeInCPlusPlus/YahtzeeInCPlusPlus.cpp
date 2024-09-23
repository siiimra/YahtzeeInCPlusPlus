//************************************************************
//* Name:  Simra Ahmed
//* Project : Yahtzee in C++
//* Class : CMPS 366 01 Organization of Programming Languages
//* Date : 
//************************************************************


#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


/* *********************************************************************
Function Name: selectMenu
Purpose: To calculate the average grade in a class
Parameters:
            chooseToPlay - int value given by the user to determine if
            they want to play a game of Yahtzee or not
Return Value: 
            
Algorithm:
            1) Generates a new game if user chooses yes
            2) Exits program if user says no
            3) Says input is invalid if user inputs anything other than 1 or 2
Reference: none
********************************************************************* */
int selectMenu(int chooseToPlay) {
    
    
    if (chooseToPlay == 1) {
        cout << "HI";
    }
    else if (chooseToPlay == 2) {
        cout << "Goodbye!";
        exit(0);
    }
    else {
        cout << "Invalid input.";
    }
}

int main()
{
    //Variable that allows user to choose to select new game or exit game
    int chooseToPlay;

    //Display welcome screen with options
    cout << "Welcome! Would you like to begin a game of Yahtzee?" << endl;
    cout << "1. New Game " << "2. Exit Game" << endl;
    cout << "What action would you like to take? ";
    cin >> chooseToPlay;
    selectMenu(chooseToPlay);
    
  
}

