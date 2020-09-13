#include "Ship.h"

using namespace std;

Ship::Ship()
{
  m_ship = nullptr;   
  m_length = 0;      
  m_damage = 0;       
}

Ship::~Ship(){
    delete[] m_ship;
}

void Ship::createShip(int length) 
{
    m_length = length;
    m_ship = new string[length];
}

void Ship::setCoordinate(string coordinate, int index) {
    m_ship[index]=coordinate;
}

string Ship::getCoordinate(int index) const{
    return m_ship[index];
}

void Ship::setLength(int length){
    m_length = length;
}

int Ship::getLength() const{
    return(m_length);
}

bool Ship::isSunk()
{
     if(m_damage == m_length)    //damage equals the length
  {
    return true;    //the ship is sunk
  }
  else    //damage does not equal the length
  {
    return false;   //the ship is not sunk
  }
}

void Ship::addDamage(){
    m_damage++;
}

int Ship::getDamage() const{
    return m_damage;
}

void Ship::setDamage(int newDamage){
    m_damage = newDamage;
}
