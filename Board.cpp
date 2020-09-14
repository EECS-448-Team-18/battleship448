/* -----------------------------------------------------------------------------

@author Abhigyan Saxena, Xiaoyi Lu, Evelyn Thomas, @file Board.cpp, @date 09/12/20, @brief Board functions implemented

 ---------------------------------------------------------------------------- */
#include "Board.h"
#include <sstream>
#include <limits>

Board::Board(int shipnum)
{
	numberOfShips = shipnum;	//the number of ships per player.
	blueTilde = "\033[1;36m~\033[0m";	//blue water color
	redHit = "\033[1;31mX\033[0m";	//red ship hit color
	whiteMiss = "\033[1;37mO\033[0m";		//white missed shot color
	ship = "\033[1;32m∆\033[0m";	//green ship color 

	for (int i=0; i<9; i++)	//initializes myBoard and shotBoard to a grid of blue water
	{
		for(int j=0; j<9; j++)
		{
			myBoard[i][j] = blueTilde;
			shotBoard[i][j] = blueTilde;
		}
	}
}

Board::~Board()	//destructor to delete m_ship
{
	delete[] m_ship;
}

void Board::printMyBoard()	//prints the player's board 
{
	std::cout << "\t\t\tYour board\n";
	std::cout << "\t";

	for(int i=0;i<9;i++)
	{
		std::cout << m_rowNames[i] << "\t";	//prints the columns
	}
	std::cout << "\n";

	for(int i=0;i<9;i++)
	{
		std::cout << i+1;	//print the rows
		for(int j=0;j<9;j++)
		{
			std::cout << "\t" << myBoard[i][j];	//print the board symbols
		}
		if(i<9) //reduce space
		{
			std::cout << "\n\n\n";
		}
		else
		{
			std::cout << "\n\n";
		}
	}
}

bool Board::updateMyBoard(std::string userGuess)	//updates the current player board
{
	guessConversion(userGuess);	//updates m_rowIndex and m_columnIndex based on userGuess
	std::string location = myBoard[m_rowIndex][m_columnIndex];	//sets the location to the current element in the index that the player got shot at
	if(location == blueTilde)	//if location is water, then it is a miss
	{
		myBoard[m_rowIndex][m_columnIndex] = whiteMiss;
	}
	else if(location == ship)	//if location is a green triangle, then set to a red traingle
	{
		myBoard[m_rowIndex][m_columnIndex] = redHit;
		for(int i = 0; i < numberOfShips; i++)	//searches through each ship, at the length of each ship, until it finds the correct index holding the userGuess location
		{
			for(int j = 0; j < m_ship[i].getLength(); j++)
			{
				if(m_ship[i].getCoordinate(j) == userGuess)
				{
					m_ship[i].addDamage();	//damage++
					if(m_ship[i].isSunk())	//if damage counter equal to length, it has sunk
					{
						std::cout << "BATTLESHIP SUNK!\n";	//prints that the ship has been sunk
					}
					break;
				}
			}
		}
		return true;	//true, ship hit
	}
	else if(location == redHit || location == whiteMiss)	//can't shoot at same location twice
	{
		throw(std::runtime_error("You already shot here! Try again!"));
	}
	return false;	//if there were no hits, then this runs and we return false because it was a miss
}

void Board::printShotBoard()	//prints rival board 
{
	std::cout << "\n\t\t\tYour Rival's board\n";
	std::cout << '\t';
	for(int i=0;i<9;i++)
  {
    std::cout << m_rowNames[i] << "\t";	//prints the column names
  }
std::cout << "\n";

  for(int i=0;i<9;i++)
  {
		std::cout << i+1;	//prints the row names
		for(int j=0;j<9;j++)
		{
			std::cout << "\t" << shotBoard[i][j];	//print the board symbols
		}
		if(i != 8)
		{
			std::cout << "\n\n\n"; //space b/w rows 
		}
		else
		{
			std::cout << "\n\n"; //space b/w rows
		}
  }
}

void Board::updateShotBoard(std::string userGuess, bool wasHit)	
{
	guessConversion(userGuess);	
	if(wasHit)	//redHit for hit
	{
		shotBoard[m_rowIndex][m_columnIndex] = redHit;
	}
	else	//whiteMiss for miss
	{
		shotBoard[m_rowIndex][m_columnIndex] = whiteMiss;
	}
}



void Board::guessConversion(std::string userGuess)
{
	if(userGuess.length() != 2)	//if it isn't a coordinate like "A2, B7" etc. we return so user can try agane
	{
		return;
	}
	else
	{
	for(unsigned int i=0;i<m_rowNames.length();i++)	
	{
		if(userGuess.at(0) == m_rowNames.at(i) ||userGuess.at(0) == (tolower(m_rowNames.at(i))))	
			

		{
			m_columnIndex = i;	
			break;
		}
		else
		{
			m_columnIndex = 10; 
		}

	}
}

	int temp = userGuess.at(1) - '0'; //convert ASCII to decimal

	m_rowIndex = temp - 1; //sets the column user wants, -1 for computer scientist index :)

}

bool Board::withinBoundary(std::string userGuess) //true for userGuess within bounds of the board
{
	if(userGuess.length() != 2)
		{
			return false;
		}
		else
		{
			guessConversion(userGuess);	
			if((0 <= m_rowIndex && m_rowIndex <= 8) && (0 <= m_columnIndex && m_columnIndex <= 8))
			{
				return true;	
			}
			else
			{
				return false;	
			}
		}
}

bool Board::noHorizontalCollision(std::string userGuess, int shipLength)	
{
	guessConversion(userGuess);	
	for(int i = 0; i < shipLength; i++)
 {
	if((0 <= m_rowIndex && m_rowIndex <= 8) && (0 <= m_columnIndex + i && m_columnIndex + i <= 8))	//checks indices within boundary
		{
		if(myBoard[m_rowIndex][m_columnIndex + i] != blueTilde)	//returns false if right indices are not water
			{
			return false;
			}
		}
	else
	{
		return false;	//false if out of bounds
	}
 }
 return true;	//passed all checks, no collosion
}

bool Board::noVerticalCollision(std::string userGuess, int shipLength)
{
	guessConversion(userGuess);	
	for(int i = 0; i < shipLength; i++)
 {
	if((0 <= m_rowIndex + i && m_rowIndex + i <= 8) && (0 <= m_columnIndex && m_columnIndex <= 8))	
		{
		if(myBoard[m_rowIndex + i][m_columnIndex] != blueTilde)	//false if not on water
			{
			return false;
			}
		}
	else
	{
		return false;	//false if out of bounds
	}
 }
 return true;	//if passes all checks, no collision
}

void Board::setupBoard()	
{
	std::string userGuess;	
	std::string userDirection;	
	bool validLocation = false;	
	std::string temp; 		
	bool HorV = false; 

	m_ship =  new Ship[numberOfShips];	
	for(int i = 0; i < numberOfShips; i++)
	{
		m_ship[i].createShip(i+1);	
		if(m_ship[i].getLength() == 1)	
		{
			userGuess = " ";	

				do {
					printMyBoard();	
					std::cout<<"Where would you like to place this ship of size 1? Enter your coordinate: ";
					std::getline(std::cin, userGuess);	

					std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper); 

					if(!withinBoundary(userGuess))	
					{
						std::cout << "Wrong coordinate! Try again.\n";
					}

				} while(!withinBoundary(userGuess));	

					myBoard[m_rowIndex][m_columnIndex] = ship;	
					m_ship[i].setCoordinate(userGuess, 0);	
					printMyBoard();	


		}
		else
		{
			std::cout<<"which way do you want this ship? HORIZONTAL(H/h) OR VERTICAL(V/v) ship size:" <<i+1 <<": ";
			std::getline(std::cin, userDirection);	

			do
			{
				HorV = false;	

				if(userDirection == "H" || userDirection == "h")
				{
					validLocation = false; 

					std::cout<<"Type in left most coordinate of this ship on the board to place it? ";

					std::getline(std::cin, userGuess);

					std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);	

					while(validLocation == false)	
					{

						if(noHorizontalCollision(userGuess,i+1))	//collion check
						{
							guessConversion(userGuess); 
							temp = userGuess;	

							for(int j = 0; j < m_ship[i].getLength(); j++ )
							{
								myBoard[m_rowIndex][m_columnIndex+j] = ship;	
								m_ship[i].setCoordinate(temp, j);
								temp[0] = temp.at(0) + 1;	
																					
							}
							printMyBoard();

							validLocation = true;	
							HorV = true;	
						}
						else	
						{
							printMyBoard();	
							std::cout << "Wrong location! Try again!\n";
							std::cout<<"type left most coordinate of this ship to place it on the board? ";

							std::getline(std::cin, userGuess);

							std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);	

						}
					}

				}
				else if(userDirection == "V" || userDirection == "v")
				{
					validLocation = false; //reinitializes to false since if they do H twice in a row, it could have been set to true from before

					std::cout<<"type top most coordinate of this ship to place it on the board? ";

					std::getline(std::cin, userGuess);

					std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);	


					while(validLocation == false)
					{
						if(noVerticalCollision(userGuess,i+1))
						{
							guessConversion(userGuess); 
							temp = userGuess;	
							for(int j = 0; j < m_ship[i].getLength(); j++ )
							{
								myBoard[m_rowIndex+j][m_columnIndex] = ship;
								m_ship[i].setCoordinate(temp, j);
								temp[1] = temp.at(1) + 1;	
																					
																					

							}
							printMyBoard();	

							validLocation = true;	
							HorV = true;	
						}
						else
						{
							printMyBoard();	
							std::cout << "Wrong location! Try again!\n";
							std::cout<<"type top most coordinate of this ship to place it on the board? ";

							std::getline(std::cin, userGuess);

							std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);	//converts guess to uppercase

						}
					}
				}
				else	
				{
					std::cout << "Invalid Direction. Try again!\n";
					printMyBoard();	
					std::cout<<"Would you like this ship to be HORIZONTAL(H/h) OR VERTICAL(V/v). Ship size: " <<i+1 <<": ";
					std::getline(std::cin, userDirection);
				}
			}while(!HorV);	


		}

	}
	std::cout << "Press Enter to go to the next Player's turn: ";

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 
	printIntermission();	



}

void Board::setNumberofShips(int shipnum)	
{
	numberOfShips = shipnum;
}

int Board::getNumberofShips() const	
{
	return numberOfShips;
}

Ship* Board::getShip() const	
{
	return m_ship;
}

void Board::printIntermission()
{
	for(int i=0;i<40;i++)
	{
		std::cout << "\n\n\n\n\n\n";	//print blank space
	}
	std::cout << "Press Enter when ready! ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');	//ignore all input except enter .. mainly for friendly smack talking
}
