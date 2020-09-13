#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Board.h"
using namespace std;

class Player{
public:
  Player(int shipsNum);
  ~Player();
  int getNumOfBoats();
  void setRecentGuess(std::string guess);
  std::string getRecentGuess() const;
  Board* getBoard() const;
  bool gettingShot(std::string guess);
  void shooting(string guess, bool hit);

private:
  int numOfShips;
  std::string recentguess;
  Board* m_board = nullptr;
};

#endif

