#include "Player.h"
#include <iostream>
#include <string>
using namespace std;


Player::Player(int numOfBoats){
  _numOfBoats = numOfBoats;
}


int Player::getNumOfBoats(){
  return _numOfBoats;
}

