#ifndef BOARD_H
#define BOARD_H
#include "Ship.h"
#include <iostream>
#include <string>
using namespace std;

class Board
{
        private:
        	string shotBoard[9][9];
		string myBoard[9][9];
		string m_rowNames = "A B C D E F G H I";
		string m_columnNames = "1 2 3 4 5 6 7 8 9";
		int m_rowIndex;
		int m_columnIndex;
		/**
		* @pre none
		*	@param takes a location string from user
		*	@post converts userGuess to two array indices, updating rowIndex and columnIndex
		*/
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

