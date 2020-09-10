#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class Player{
public:
  Player(int numOfBoats);
  ~Player();
  int getNumOfBoats();

private:
  int _numOfBoats;
};

#endif
