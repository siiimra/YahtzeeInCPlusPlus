#pragma once

#include <iostream>
#include <string>
using namespace std;

class Scorecard
{

    string winners[12];
    int scoreboard[12][2];

public:
    Scorecard();
    void displayScorecard();


};