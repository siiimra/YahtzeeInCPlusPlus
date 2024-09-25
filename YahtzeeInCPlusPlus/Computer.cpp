#include "Computer.h"
#include <iostream>

Computer::Computer(string name1) : Player(name1) {}

void Computer::rollDice(vector<int>& dice) {
    cout << name << " is rolling the dice...\n";
    for (size_t i = 0; i < dice.size(); ++i) {
        dice[i] = rand() % 6 + 1;
    }
    cout << name << " rolled: ";
    for (int die : dice) {
        cout << die << " ";
    }
    cout << endl;
}

void Computer::chooseCategory() {
    cout << "Choose a category." << endl;
}