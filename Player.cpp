#include "Player.h"
#include <iostream>
#include <string>
using namespace std;


Player::Player(int shipNums){
 m_board = new Board(shipNums); //initialize board for player
	numOfShips = shipNums;
}


Player::~Player()
{
  delete m_board;
}

void Player::setRecentGuess(std::string userGuess)
{
	recentguess = userGuess; //update most recent guess
}

std::string Player::getRecentGuess() const
{
	return recentguess; //return most recent guess
}

Board* Player::getBoard() const
{
	return m_board; //return board object of player
}

bool Player::gettingShot(std::string userGuess)
{
	if(m_board->withinBoundary(userGuess)) // check userGuess within boundary or not
	{
		return (m_board->updateMyBoard(userGuess)); //updated player's board after get shot
	}
	else
	{
		throw(std::runtime_error("Out of Boundary! Try again.\n"));
	}

}

void Player::shooting(std::string userGuess, bool hit)
{
	m_board->updateShotBoard(userGuess, hit); //update the shot board after player shooting
}
