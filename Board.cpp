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
		std::cout << i+1;	//print the row names
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

void Board::printIntermission()	//prints the break/no-cheat screen to switch players
{
	for(int i=0;i<40;i++)
	{
		std::cout << "\n\n\n\n\n\n";	//prints a lot of newlines to add blank space so that player's can swap turns without seeing each other's boards
	}
	std::cout << "Press Enter when ready! ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');	//takes in input of the user, basically ignoring any input so that the user can type anything
}

bool Board::updateMyBoard(std::string userGuess)	//updates the current player's board
{
	guessConversion(userGuess);	//updates m_rowIndex and m_columnIndex based on userGuess
	std::string location = myBoard[m_rowIndex][m_columnIndex];	//sets the location to the current element in the index that the player got shot at
	if(location == blueTilde)	//if the location is a blueTilde (aka water), then it becomes a miss
	{
		myBoard[m_rowIndex][m_columnIndex] = whiteMiss;
	}
	else if(location == ship)	//if the location is a ship, then we set that element to a redHit
	{
		myBoard[m_rowIndex][m_columnIndex] = redHit;
		for(int i = 0; i < numberOfShips; i++)	//searches through each ship, at the length of each ship, until it finds the correct index holding the userGuess location
		{
			for(int j = 0; j < m_ship[i].getLength(); j++)
			{
				if(m_ship[i].getCoordinate(j) == userGuess)
				{
					m_ship[i].addDamage();	//add damage counter to that ship
					if(m_ship[i].isSunk())	//then, we check if it has an amount of damage counters equal to its length, meaning it has been sunk
					{
						std::cout << "BATTLESHIP SUNK!\n";	//prints that the ship has been sunk
					}
					break;	//we can break since we found the indices of the userGuess location ship
				}
			}
		}
		return true;	//return true because a ship was hit
	}
	else if(location == redHit || location == whiteMiss)	//if the user guesses a location already shot at before, we prompt them to try again
	{
		throw(std::runtime_error("You've already shot at this location! Try again."));
	}
	return false;	//if there were no hits, then this runs and we return false because it was a miss
}

void Board::updateShotBoard(std::string userGuess, bool wasHit)	//takes in the userGuess and a bool wasHit
{
	guessConversion(userGuess);	//calls guess conversion to get back the correct indices based on userGuess
	if(wasHit)	//if that location was hit, then we changed it to a redHit
	{
		shotBoard[m_rowIndex][m_columnIndex] = redHit;
	}
	else	//if that location was a miss, we change it to whiteMiss
	{
		shotBoard[m_rowIndex][m_columnIndex] = whiteMiss;
	}
}

//assumes userGuess is within boundary since that is checked first
void Board::guessConversion(std::string userGuess) //converts userGuess to two indices and updates member variables m_rowIndex and m_columnIndex with those indices
{
	if(userGuess.length() != 2)	//if userGuess is not a string of length 2, we instantly return because it cannot be a valid input
	{
		return;
	}
	else
	{
	for(unsigned int i=0;i<m_rowNames.length();i++)	//had to make i an unsigned int since m_rowNames.length() returns an unsigned in as well
	{
		if(userGuess.at(0) == m_rowNames.at(i) ||userGuess.at(0) == (tolower(m_rowNames.at(i))))	//compares the first char in userGuess to every element in m_rowNames,
			//which is "ABCDEFGHI" until it matches one, and returns that index.
			//it also compares it to the tolower version, so "abcdefghi"
		{
			m_columnIndex = i;	//sets m_columnIndex to the correct index, and then breaks out since we do not need to scan through m_rowNames anymore
			break;
		}
		else
		{
			m_columnIndex = 10; //sets m_rowIndex to a number outside of the range so that it's not just the value it held previously.
			//if the letter the user typed is withing "ABCDEFGHI", then the correct index is set and we break out
			//of this for loop and m_rowIndex does not become 10
		}

	}
}

	int temp = userGuess.at(1) - '0'; //sets temp to the index the user typed. We subtract '0' to convert it from the ASCII value to the decimal value.

	m_rowIndex = temp - 1; //sets it to the column the user wants, but subtracts 1 to get the proper index

}

bool Board::withinBoundary(std::string userGuess) //returns true if userGuess is within bounds of the board, false if not
{
	if(userGuess.length() != 2)	//checks that the userGuess was length 2. If not, returns false immediately
		{
			return false;
		}
		else
		{
			guessConversion(userGuess);	//takes in userGuess and sets the indices based on that guess
			if((0 <= m_rowIndex && m_rowIndex <= 8) && (0 <= m_columnIndex && m_columnIndex <= 8))
			{
				return true;	//if the indices are within the bounds of our board, we return true
			}
			else
			{
				return false;	//otherwise, we return false
			}
		}
}

bool Board::noHorizontalCollision(std::string userGuess, int shipLength)	//returns true if the userGuess location will not cause any horizontal ship collision or out of bounds errors
{
	guessConversion(userGuess);	//updates m_rowIndex and m_columnIndex based on userGuess
	for(int i = 0; i < shipLength; i++)
 {
	if((0 <= m_rowIndex && m_rowIndex <= 8) && (0 <= m_columnIndex + i && m_columnIndex + i <= 8))	//checks that all the next right indices are within the bounds
		{
		if(myBoard[m_rowIndex][m_columnIndex + i] != blueTilde)	//returns false if at any time the next right indices are not blueTildes
			{
			return false;
			}
		}
	else
	{
		return false;	//returns false if any of the right indices are out of bounds
	}
 }
 return true;	//returns true since all the false checks were not hit, so there is no collision that would happen
}

bool Board::noVerticalCollision(std::string userGuess, int shipLength)	//returns true if the userGuess location will not cause any vertical ship collison or out of bounds errors
{
	guessConversion(userGuess);	//updates m_rowIndex and m_columnIndex based on userGuess
	for(int i = 0; i < shipLength; i++)
 {
	if((0 <= m_rowIndex + i && m_rowIndex + i <= 8) && (0 <= m_columnIndex && m_columnIndex <= 8))	//checks that all the next below indices are within bounds
		{
		if(myBoard[m_rowIndex + i][m_columnIndex] != blueTilde)	//returns false if at any time the next below indices are not blueTildes
			{
			return false;
			}
		}
	else
	{
		return false;	//returns false if any of the below indices are out of bounds
	}
 }
 return true;	//returns true since all the false checks were not hit, so there is no collision that would happen
}

void Board::setupBoard()	//sets up the board
{
	std::string userGuess;	//used to take in the user's location
	std::string userDirection;	//("H" or "h" or "V" or "v") horizontal or vertical ship placement
	bool validLocation = false;	//used to keep asking for valid location if still false
	std::string temp; 		//used for ascii conversion
	bool HorV = false; //gets set to true if the user types "H" or "h" or "V" or "v"

	m_ship =  new Ship[numberOfShips];	//creates an array of Ship objects, the amount is the number of ships
	for(int i = 0; i < numberOfShips; i++)
	{
		m_ship[i].createShip(i+1);	//creates a ship at each index, of which the size corresponds to the index +1 (eg. index 0 houses ship of length 1, index 1 houses ship of length 2)
		if(m_ship[i].getLength() == 1)	//if the ship is length 1, we do not need to do horizontal or vertical collision checks, so we just ask where to place it
		{
			userGuess = " ";	//reinitialize userGuess

				do {
					printMyBoard();	//prints the user's board s they can see where to place the ship
					std::cout<<"Where would you like to place this ship of size 1? Enter your coordinate: ";
					std::getline(std::cin, userGuess);	//takes in the user's input

					std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper); //converts guess to uppercase so that it is always passed in consistently

					if(!withinBoundary(userGuess))	//if that location is not within the boundary, we tell them to try again
					{
						std::cout << "Invalid coordinate! Try again.\n";
					}

				} while(!withinBoundary(userGuess));	//runs until the user's guess is within the boundary

					myBoard[m_rowIndex][m_columnIndex] = ship;	//sets the user's guess location to a ship
					m_ship[i].setCoordinate(userGuess, 0);	//sets the element in the m_ship array to the location string (eg. "A7", "B2"), and passes in the index as 0
					printMyBoard();	//prints the newly updated board


		}
		else
		{
			std::cout<<"HORIZONTAL(H/h) OR VERTICAL(V/v) orientation for this ship of size " <<i+1 <<": ";
			std::getline(std::cin, userDirection);	//takes in the user input of horizontal or vertical

			do
			{
				HorV = false;	//need to reinitialize to false so that each run through, this loop correclty runs

				if(userDirection == "H" || userDirection == "h")
				{
					validLocation = false; //reinitializes to false since if they do H twice in a row, it could have been set to true from before

					std::cout<<"Where would you like the left most coordinate of this ship to be? ";

					std::getline(std::cin, userGuess);

					std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);	//converts guess to uppercase

					while(validLocation == false)	//runs until the location is valid
					{

						if(noHorizontalCollision(userGuess,i+1))	//checks for no horizontal collion, passing in the location and current ship length
						{
							guessConversion(userGuess); //pushing two int indexes back to orignal spot of user guess
							temp = userGuess;	//used to store and manipulate userGuess without changing userGuess

							for(int j = 0; j < m_ship[i].getLength(); j++ )
							{
								myBoard[m_rowIndex][m_columnIndex+j] = ship;	//sets the horizontal locations to a ship
								m_ship[i].setCoordinate(temp, j);
								temp[0] = temp.at(0) + 1;	//sets the first value of temp (which is a copy of userGuess) to the next consecutive alphabetical value, using ASCII math
																					//for example, if temp is "A1" then temp[0] = 'A', and temp.at(0) = 'A'. temp.at(0) + 1 is 'A' + 1, which returns 'B'
																					//so, when then override temp[0] to B, hence traversing the columns

							}
							printMyBoard();	//prints the updated board

							validLocation = true;	//sets valid location to true to help break out of loop
							HorV = true;	//true to kick out of while loop
						}
						else	//if the input was not "H" or "h"
						{
							printMyBoard();	//prints the board again and asks the user to try again
							std::cout << "Invalid location. Try again!\n";
							std::cout<<"Where would you like the left most coordinate of this ship to be? ";

							std::getline(std::cin, userGuess);

							std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);	//converts guess to uppercase

						}
					}

				}
				else if(userDirection == "V" || userDirection == "v")
				{
					validLocation = false; //reinitializes to false since if they do H twice in a row, it could have been set to true from before

					std::cout<<"Where would you like the top most coordinate of this ship to be? ";

					std::getline(std::cin, userGuess);

					std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);	//converts guess to uppercase


					while(validLocation == false)
					{
						if(noVerticalCollision(userGuess,i+1))
						{
							guessConversion(userGuess); //pushing two int indexes back to orignal spot of user guess
							temp = userGuess;	//used to store and manipulate userGuess without changing userGuess
							for(int j = 0; j < m_ship[i].getLength(); j++ )
							{
								myBoard[m_rowIndex+j][m_columnIndex] = ship;
								m_ship[i].setCoordinate(temp, j);
								temp[1] = temp.at(1) + 1;	//sets the second value of temp (which is a copy of userGuess) to the next consecutive numberical value
																					//for example, if temp is "A1" then temp[1] = '1', and temp.at(1) = '1'. temp.at(1) + 1 is '1' + 1, which returns '2'
																					//so, when then override temp[1] to 2, hence traversing the rows

							}
							printMyBoard();	//prints the updated board

							validLocation = true;	//sets valid location to true to help break out of loop
							HorV = true;	//true to kick out of while loop
						}
						else
						{
							printMyBoard();	//prints the updated board again and asks the user to try again
							std::cout << "Invalid location. Try again!\n";
							std::cout<<"Where would you like the top most coordinate of this ship to be? ";

							std::getline(std::cin, userGuess);

							std::transform(userGuess.begin(), userGuess.end(),userGuess.begin(), ::toupper);	//converts guess to uppercase

						}
					}
				}
				else	//if the input was not "V" or "v"
				{
					std::cout << "Invalid Direction. Try again!\n";
					printMyBoard();	//prints the board again so that the user can try again
					std::cout<<"HORIZONTAL(H/h) OR VERTICAL(V/v) orientation for this ship of size " <<i+1 <<": ";
					std::getline(std::cin, userDirection);
				}
			}while(!HorV);	//runs until the user has inputed "H" or "h" or "V" or "v". Also, there are checks to insure that the location was valid first as well, before getting to this point


		}

	}
	std::cout << "Press Enter to go to the next Player's turn: ";

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //basically lets the user type in anything, ignoring their input
	printIntermission();	//prints the intermission screen



}

void Board::setNumberofShips(int shipnum)	//sets the number of ships
{
	numberOfShips = shipnum;
}

int Board::getNumberofShips() const	//returns the number of ships
{
	return numberOfShips;
}

Ship* Board::getShip() const	//returns m_ship
{
	return m_ship;
}
