/*
 * File Name: Ship.cpp
 * Author: Linh Nguyen
 * Project 1 EECS 448
 * Brief: The implementation of the ship that define in Ship.h
 * Date: Sep 13, 2020
 * 
*/
#include "Ship.h"

using namespace std;

Ship::Ship(){}

Ship::~Ship(){
    delete m_ship;
}

void Ship::createShip(int length) {
    m_ship = new string[length];
}

void Ship::setCoordinate(string coordinate, int index) {
    m_ship[index]=coordinate;
}

string Ship::getCoordinate(int index) const{
    return m_ship[index];
}

void Ship::setLength(int length){
    this->length = length;
}

int Ship::getLength() const{
    return(length);
}

bool Ship::isSunk(){
    return (length == 0);
}

void Ship::addDamage(){
    damage++;
}

int Ship::getDamage() const{
    return damage;
}

void Ship::setDamage(int newDamage){
    damage = newDamage;
}
