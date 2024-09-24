#include "Player.h"



	Player::Player(string name1 = "Computer") {
		score = 0;
		name = name1;
	}

	string Player::getName() {
		return name;
	}

	int Player::getScore() {
		return score;
	}

	void Player::setName(string name) {
		this->name = name;
	}

	void Player::setScore(int score) {
		this->score = score;
	}


