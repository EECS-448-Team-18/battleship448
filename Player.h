/**------------------------------------------------------------------
Filename: Player.h, Author: Achyut Paudel, Date: 9/13/2020
Desc: Defining functions for Player.cpp file/functions
------------------------------------------------------------------
*/

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Board.h"
using namespace std;

class Player{
public:
  // @pre none
    // @post initializes numOfShips and players board
    // @param number of ships
  Player(int shipsNum);
  
  
  // @pre none
    // @post player object deleted
    // @param none
  ~Player();
  
  
  // @pre player board is populated with boats
    // @post returns number of boats that the player still has
    // @param none
  int getNumOfBoats();
  
  
  // @pre none
    // @post recent guess is updated
    // @param location of guess
  void setRecentGuess(std::string guess);
  
  
  // @pre there exists a recent guess
    // @post recent guess is returned
    // @param none
  std::string getRecentGuess() const;
  
  
  // @pre none
    // @post Players board is returned
    // @param none
  Board* getBoard() const;
  
  
  // @pre none
    // @post returns if the location that was guessed is within the boundary of the board
    // @param location of guess
  bool gettingShot(std::string guess);
  
  
  // @pre location of guess must be valid
    // @post updates this players board with location of guess marked
    // @param location of guess and boolean whose value indicated whether the location is valid
  void shooting(string guess, bool hit);
  
  

private:
  int numOfShips;
  std::string recentguess;
  Board* m_board = nullptr;
};

#endif

