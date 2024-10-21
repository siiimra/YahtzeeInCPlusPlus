#include "Player.h"


/* *********************************************************************
Function Name: Player (Constructor)
Purpose: To initialize a new Player object with the given name.
Parameters:
	- name1 (string): The name of the player being created. It is passed by value.
Return Value: None (constructor)
Algorithm:
	1) Set the player's score to 0.
	2) Assign the given name to the player.
Reference: None
**********************************************************************/

Player::Player(string name1) {
	score = 0;
	name = name1;
}

/* *********************************************************************
Function Name: getName
Purpose: To retrieve the name of the player.
Parameters: None
Return Value: The name of the player (string).
Algorithm:
	1) Return the player's name.
Reference: None
**********************************************************************/

string Player::getName() const {
	// Returns players name
	return name;
}

/* *********************************************************************
Function Name: setName
Purpose: To set or update the player's name.
Parameters:
	- name (string): The new name to be assigned to the player.
Return Value: None
Algorithm:
	1) Update the player's name with the given value.
Reference: None
**********************************************************************/

void Player::setName(string name) {
	// Set players name
	this->name = name;
}

/* *********************************************************************
Function Name: getScore
Purpose: To retrieve the current score of the player.
Parameters: None
Return Value: The player's current score (int).
Algorithm:
	1) Return the player's score.
Reference: None
**********************************************************************/

int Player::getScore() const {
	// Returns players score
	return score;
}

/* *********************************************************************
Function Name: setScore
Purpose: To set or update the player's score, ensuring it is non-negative.
Parameters:
	- score (int): The new score to be assigned to the player.
Return Value: None
Algorithm:
	1) If the given score is non-negative, update the player's score.
Reference: None
**********************************************************************/

void Player::setScore(int score) {
	// Sets players score
	if (score >= 0)
		this->score = score;
		
}


