#pragma once
#include <iostream>
#include <string>

using namespace std;

class Player {
	
	string name;
	int score;

public:
	Player(string name1 = "Computer");

		string getName();

		int getScore();

		void setName(string name);

		void setScore(int score);

};
