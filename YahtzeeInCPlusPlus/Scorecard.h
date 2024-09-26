#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool checkConsecutive(int* dice, int count1);

class Scorecard
{
    //Holds Category, Description, Score, Winner
    string scoreboard1[12][4];

    //2-D array to input How many points have been earned
    //and which round it was earned in
    int scoreboard2[12][2];

public:


    Scorecard();

    //Function that displays scorecard
    void displayScorecard();

    //calculate score
    int calcScore(string name);

    //update score
    void updateScorecard(int index, string name, int score, int round);
    void displayAll();

    //Takes in diceRoll, checks if it can fill category or not
    vector<int> displayAvailable(int* dice);


};