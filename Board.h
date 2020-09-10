#ifndef BOARD_H
#define BOARD_H
#include "Ship.h"
#include <iostream>
using namespace std;

class Board
{
        private:
        //      int x; //rows
        //      char y; //columns
                char** boardArray;

        public:
                Board();
                ~Board();
                bool shipLocation(int x, char y);
                void fire(int x, char y);
        //      bool match();
                void printBoard();


};
#endif

