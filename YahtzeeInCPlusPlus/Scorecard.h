#pragma once

#include <iostream>
#include <string>
using namespace std;

class Scorecard
{
    //Array to input winner of round name
    string winners[12][4];


    //2-D array to input How many points have been earned
    //and which round it was earned in
    int scoreboard[12][2];

public:


    Scorecard();

    //Function that displays scorecard
    void displayScorecard();
    int calcScore(string name);
    void updateScorecard(int index, string name, int score, int round);
    void displayAvailable();


};