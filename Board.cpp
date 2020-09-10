//Board.cpp
#include "Board.h"

Board::Board()
{

}

Board::~Board()
{

}

bool Board::shipLocation(int x, char y, char target)
{
        cout << "Enter a row number (between 1 to 9) and a column letter (between A to I): " << endl;
        cin >> x;
        cin >> y;
        target = boardArray[x][y];
}


void Board::printBoard()
{
        cout << " A B C D E F G H I" <<endl;
//      if(x >= 1 && x <= 9)
        {
                for(int i = 1; i < 9; i++)
                {
                        for(int j = 1; j < 9; j++)
                        {
                                cout << boardArray[i][j] << "\n";
                        }
                }
        }
}
