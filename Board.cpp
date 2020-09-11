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
bool Board::updateMyBoard(std::string userGuess)
{
        if(withinBoundary(userGuess))
        {       
                if (myBoard)
                {
                        myBoard[m_rowIndex][m_colIndex] = "redHit";
                        return True;
                }
        }
        return false;

}
bool Board::withinBoundary(std::string userGuess)
{
        guessConversion(userGuess);
        if (m_rowIndex < 10 && m_rowIndex > 0 && m_colIndex < 10 && m_colIndex > 0)
        {
                return true;
        }
        return false;
}
