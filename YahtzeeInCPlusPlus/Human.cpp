#include "Human.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Human::Human(string name1) : Player(name1) {
    //Welcomes human player to Yahtzee
    cout << "Welcome to Yahtzee, " << name1 << "!" << endl;
    // implement if user wants to keep dice
    // Implement if user wants to stand
    // implement which category to be filles

}



void Human::chooseCategory() {
    cout << "Choose a category." << endl;
}
