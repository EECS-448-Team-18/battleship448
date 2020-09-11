//Board.cpp
#include "Board.h"

Board::Board()
{

}

Board::~Board()
{
	for(int i = 1; i < 9; i++)
	{
		delete [] boardArray[i];
	}
	delete boardArray;
}

void Board::printMyBoard()
{
       // cout << " A B C D E F G H I" <<endl;
//      if(x >= 1 && x <= 9)
//        {
                for(int i = 1; i < 9; i++)
                {
                        for(int j = 1; j < 9; j++)
                        {
                                cout << boardArray[i][j] << "\n";
                        }
                }
		cout << "\n";
  //      }
}

void Board::printShotBoard()
{

}

void Board::setNumberofShips(int shipNum)
{
	numberOfShips = shipNum;	
}

void Board::getNumberofShips() const
{
	return(numberOfShips);
}

