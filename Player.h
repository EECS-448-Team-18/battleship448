#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class Player{
public:
  Player(string firstName, string lastName);
  ~Player();
  void print();
  string getName();

private:
  string getfirstName;
  string getlastName;
};

#endif
