
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <string>
#include <iostream>
#include <fstream>
#include "Player.h"		//include player header file

/**
 * The Executive class controls the game
 * all the methods are implemented for making the Battleship game
 */
class Executive
{
public:
	/**
	* @pre none
	*	@post created and set up the game board
	*/
	Executive();

	/**
	* @pre none
	*	@post Executive object destructor
	*/
	~Executive();

	/**
	* @pre location must be valid
	* @param takes a location from user
	*	@post shoot the location
	*/
	void shoot(std::string location);

	/**
	* @pre none
	* @param none
	*	@post start the game offically
	*/
	void game();

	/**
	* @pre none
	*	@param none
	*	@post checks that number of boats are valid
	* @return number of Ships
	*/
	int boatCheck();

private:

	Player* player_1;		//player object for player1
	Player* player_2;		//player object for player2
	int m_player_1Turn; //true if player1 turn, false if player2 turn
	bool m_gameOver;	//game over to stop the while loop once the game ends
};
#endif
