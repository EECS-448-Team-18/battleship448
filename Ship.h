/*
 * File Name: Ship.h
 * Author: Linh Nguyen
 * Project 1 EECS 448
 * Brief: Export the template class Ship
 * Date: Sep 13, 2020
 * 
*/
#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Ship {
    private:
        std::string* m_ship;
        int m_length;
        int m_damage;

    public:
        //Default Constructor
        Ship();
        //Destructor
        ~Ship();

        /*
         *pre: none
         *post: create a ship for desired length
         *return: none
        */
        void createShip(int length);
        /*
         *pre: none
         *post: set coordinate for ship
         *return: none
        */
        void setCoordinate(string coordinate, int index);
        /*
         *pre: none
         *post: get the coordinate for ship
         *return: the coordinates for ship
        */
        string getCoordinate(int index) const;
        /*
         *pre: none
         *post: Set the ship length
         *return: none
        */
        void setLength(int length);
        /*
         *pre: none
         *post: Get the ship length
         *return: length of the ship
        */
        int getLength() const;

        /*
         *pre: none
         *post: boolean check the status of the ship
         *return: true of the ship sunk, otherwise return false
        */
        bool isSunk();
        /*
         *pre: none
         *post: hit the enemy ship and give damage
         *return: none
        */
        void addDamage();
        /*
         *pre: none
         *post: get the damage to the ship
         *return: the damage to the ship
        */
        int getDamage() const;
        /*
         *pre: none
         *post: set the damage to the ship
         *return: none
        */
        void setDamage(int newDamage);

};
#endif
