#include "Player.h"
#include <iostream>
#include <string>
using namespace std;


Player::Player(string firstName, string lastName){
  getfirstName = firstName;
  getlastName = lastName;
}


void Player::print(){
  cout<<"Player Name: "<<getfirstName<<" "<<getlastName<<endl;
}

string Player::getName(){
  string name = getfirstName + getlastName;
  return(name);
}

