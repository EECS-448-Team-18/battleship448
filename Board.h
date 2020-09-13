#ifndef BOARD_H
#define BOARD_H
#include "Ship.h"
#include "algorithm"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Board
{
        private:
        	string shotBoard[9][9];
		string myBoard[9][9];
		string m_rowNames = "ABCDEFGHI";
		string m_columnNames = "123456789";
		int m_rowIndex;
		int m_columnIndex;
		void guessConversion(std::string userGuess);
		string blueTilde;
		string redHit;
		string whiteMiss;
		string ship;
		int numberOfShips;
		Ship* m_ship = nullptr;

        public:
        	Board();
        	~Board();
		Board(int shipNum);
		void printShotBoard();
		void printMyBoard();
		void printIntermission(); // prints blank space to hide the board from the next player and asks that player to press Enter to continue
		void setNumberofShips(int shipnum);
		int getNumberofShips() const;
		void setupBoard();
		void updateShotBoard(std::string userGuess, bool wasHit);
		bool updateMyBoard(std::string userGuess);
		bool withinBoundary(std::string userGuess);
		bool noHorizontalCollision(std::string userGuess, int shipLength); // check whether the horizontal placed ship will collide with another ship or not. return true if ships will collide
bool noVerticalCollision(std::string userGuess, int shipLength); // same as above but for vertical ships
Ship* getShip() const; //get ship object

};
#endif

