#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <string>
#include <iostream>
#include <fstream>
#include "Player.h"		//include player header file


class Executive
{
public:
	Executive();
	~Executive();
	void shoot(std::string location);
	void game();
	int boatCheck();

private:

	Player* player_1;		//player object for player1
	Player* player_2;		//player object for player2
	int m_player_1Turn; //true if player1 turn, false if player2 turn
	bool m_gameOver;	//game over to stop the while loop once the game ends
};
#endif
