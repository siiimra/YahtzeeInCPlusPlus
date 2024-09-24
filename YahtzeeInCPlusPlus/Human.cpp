#include "Human.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Human::Human(string name1) : Player(name1) {

    cout << "Welcome to Yahtzee, " << name1 << "!" << endl;
    // implement if user wants to keep dice
    // Implement if user wants to stand
    //implement which category to be filles

}

void Human::rollDice(vector<int>& dice) {
    cout << "It's your turn to roll the dice.\n";

    // Roll the dice using a regular for-loop
    for (size_t i = 0; i < dice.size(); ++i) {
        dice[i] = rand() % 6 + 1;  
    }

    // Display the dice values using a regular for-loop
    cout << "You rolled: ";
    for (size_t i = 0; i < dice.size(); ++i) {
        cout << dice[i] << " ";
    }
    cout << endl;
}

void Human::chooseCategory() {
    cout << "Choose a category." << endl;
}
