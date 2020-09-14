/*------------------------------------------------------------------
Filename: Executive.h, Author: Abhigyan Saxena, Date: 9/06/2020
Desc: Includes Executive.h functions for battleship game.
------------------------------------------------------------------*/
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <string>
#include <iostream>
#include <fstream>
#include "Player.h"		//include player header file


class Executive
{
public:
	/*
	@pre: Executive class constructor
	@post:
	@param:
	*/
	Executive();
	/*
	@pre: Executive class destructor
	@post:
	@param:
	*/
	~Executive();
	/*
	@pre: Function to shoot at given location.
	@post:
	@param: std::string location
	*/
	void shoot(std::string location);
	/*
	@pre: 
	@post:
	@param:
	*/
	void game();
	/*
	@pre: Function including all the game functionality.
	@post:
	@param:
	*/
	int boatCheck();

private:

	Player* player_1;		//player object for player1
	Player* player_2;		//player object for player2
	int m_player_1Turn; //true if player1 turn, false if player2 turn
	bool m_gameOver;	//game over to stop the while loop once the game ends
};
#endif
