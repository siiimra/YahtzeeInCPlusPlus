#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;


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
    int calcFinalScore(string name);

    //update score
    void updateScorecard(int index, string name, int score, int round);
    bool checkConsecutive(int* dice, int count1);

    void displayAll();

    //Takes in diceRoll, checks if it can fill category or not
    vector<int> displayAvailable(int* dice);

    int calcRunningScore(int* dice, int category);

    bool gameOver();

    int potentialPoints(int* dice);
    string getCategory(int category);

    string getWinner(int category);
    void setWinner(int category, string winner);

    int getScore(int category);
    void setScore(int category, int score);
    int getRound(int category);
    void setRound(int category, int round); 




};