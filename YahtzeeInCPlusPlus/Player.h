#pragma once
#include <iostream>
#include <string>

using namespace std;

class Player {
	
	string name;
	int score;

public:
	Player(string name1 = "Computer") {
		score = 0;
		name = name1;
	}

	string getName() {
		return name;
	}

	int getScore() {
		return score;
	}

	void setName(string name) {
		this->name = name;
	}

	void setScore(int score) {
		this->score = score;
	}

};
