#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Board.h"
using namespace std;

class Player{
public:
  Player(int numOfBoats);
  ~Player();
  int getNumOfBoats();
  void setGuess();
  string getGuess();
  *Board getBoard();
  bool gettingShot(string location);
  void shooting(string location, bool hit);

private:
  int _numOfBoats;
  string _guessShot;
  Board *boardPtr;
};

#endif
