#include "Computer.h"
#include <iostream>

Computer::Computer(string name1) : Player(name1) {}

void Computer::chooseCategory() {
    cout << "Choose a category." << endl;
}