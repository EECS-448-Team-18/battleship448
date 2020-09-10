#include <iostream>

using namespace std;

class Ship {
    private:
        int size;
        char orientation;

        int startRow;
        int endRow;

        char startCol;
        char endCol;

        int *row;
        int *col;

    public:
        //Comment Linh
        //Constructor
        Ship(int size, char orientation, int startRow, int endRow, char startCol, char endCol, int *row, char *col);
        ~Ship();
        //return size of a ship
        int getSize();

        //return orientation either 'horizontal' and 'vertical'
        char getOrientation();

        //if player hit the ship, change the row to 0 and col to 'O'
        void fireSpace(int rowPosition, char colPosition);

        //Check the ship is sunk
        bool isSunk(int size);

}
