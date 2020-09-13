#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>

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

        //Create a ship for desired length
        void createShip(int length);
        //Set coordinate for ship
        void setCoordinate(string coordinate, int index);
        //Get the coordinate for ship, return the coordinates for ship
        string getCoordinate(int index) const;
        // Set the ship length
        void setLength(int length);
        // Get the ship length
        int getLength() const;

        //true if the ship sunk
        bool isSunk();
        //hit the enemy ship and give damage
        void addDamage();
        //get the damage to the ship
        int getDamage() const;
        //set the damage to the ship
        void setDamage(int newDamage);

};
#endif
