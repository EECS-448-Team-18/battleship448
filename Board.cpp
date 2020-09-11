//Board.cpp
#include "Board.h"

Board::Board()
{

}

Board::~Board()
{
	for(int i = 0; i < 9; i++)
	{
		delete boardArray[i];
	}
	delete[] boardArray;
}

void Board::printMyBoard()
{
       // cout << " A B C D E F G H I" <<endl;
//      if(x >= 1 && x <= 9)
//        {
                for(int i = 0; i < 9; i++)
                {
                        for(int j = 0; j < 9; j++)
                        {
				if(i == 0 && j == 0)
				{
					cout << "\n";
				}
                                cout << myBoard[i][j] << "\n";
                        }
                }
		cout << "\n";
  //      }
}

void Board::printShotBoard()
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(i == 0 && j == 0)
			{
				cout << "\n";
			}
			cout << shotBoard[i][j] << "\n";
		}
	}
}

void Board::setNumberofShips(int shipNum)
{
	numberOfShips = shipNum;	
}

void Board::getNumberofShips() const
{
	return(numberOfShips);
}
void Board::setupBoard()
{
        for(int i = 1; i < 9; i++)
                {
                        for(int j = 1; j < 9; j++)
                        {
                                myBoard[i][j]="blueTilde";
                        }
                }
        
}
void Board::updateShotBoard(std::string userGuess, bool wasHit)
{
	guessConversion(userGuess);
        if(wasHit)
        {
                shotBoard[m_rowIndex][m_colIndex]="redHit";
        }
        else
        {
                shotBoard[m_rowIndex][m_colIndex]="whiteMiss";
        }
        

}
