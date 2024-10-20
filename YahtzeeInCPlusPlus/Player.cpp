#include "Player.h"



	Player::Player(string name1) {
		score = 0;
		name = name1;
	}

	string Player::getName() const {
		return name;
	}

	int Player::getScore() const {
		return score;
	}

	void Player::setName(string name) {
		this->name = name;
	}

	void Player::setScore(int score) {
		if (score >= 0)
			this->score = score;
		
	}


