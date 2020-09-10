#include "Player.h"
#include <iostream>
#include <string>
using namespace std;


Player::Player(int numOfBoats){
  _numOfBoats = numOfBoats;
  boardPtr = new Board();
}


int Player::getNumOfBoats(){
  return(_numOfBoats);
}

void setGuess(string location) {
    _guessShot = location;
}

string getGuess() {
    return(_guessShot);
}

*Board getBoard() const {
    return(*boardPtr);
}

bool gettingShot(string location) {
    
}

void shooting(string location, bool hit) {

}
