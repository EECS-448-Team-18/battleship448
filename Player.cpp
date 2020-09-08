#include <iostream>
#include <string>
using namespace std;


Player::Player(string firstName, string lastName){
  getfirstName = firstName;
  getlastName = lastName;
}


void Player::print(){
  cout<<endl<<"Employee ID: "<<getId<<"\nEmployee Name: "<<getfirstName<<" "<<getlastName<<"\nAge: "<<getAge<<"\n";
}
