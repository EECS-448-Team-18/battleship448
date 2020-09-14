/*------------------------------------------------------------------
Filename: Executive.cpp, Author: Abhigyan Saxena, Date: 9/06/2020
Desc: Includes implementation for Executive.h file/functions
------------------------------------------------------------------*/
#include "Executive.h"
#include <limits>
#include "algorithm" //for toupper

Executive::Executive()		
{
	int numOfBoats = 0;		

	try		
	{
		numOfBoats = boatCheck();		
	}

	catch(std::runtime_error &rte)	//catch error if function fails
	{
		std::cout << "Invalid number of ships";		
	}

	player_1 = new Player(numOfBoats); 		
	player_2 = new Player(numOfBoats);		
	m_gameOver = false;			
	m_player_1Turn = 1;			

	std::cout <<"\nPlayer 1 place your ships\n";		
	player_1 -> getBoard() -> setupBoard();					
	std::cout <<"\nPlayer 2 place your ships\n";		
	player_2 -> getBoard() -> setupBoard();					
	game();		

}

Executive::~Executive()		
{
	delete player_1;		//delete player1
	delete player_2;		//delete player2 
}

void Executive::game()
{
	std::string guess = " ";

	while(!m_gameOver)
	{
		try
		{
			guess = " ";			

			while(guess.length() != 2)
			{
				if(m_player_1Turn % 2 == 1)	//player 1's turn
				{
					player_1->getBoard()->printShotBoard();
					player_1->getBoard()->printMyBoard();
					std::cout << "Player 1: Where would you like to SHOOT: "; 
					std::getline(std::cin, guess);

					std::transform(guess.begin(), guess.end(),guess.begin(), ::toupper);	

					std::cout << "guess: " << guess << "\n"; 

					if(guess.length() != 2)
					{
						std::cout << "Invalid coordinate! Try again.\n"; //error handling
					}

				}
				else	//player 2's turn
				{
					player_2->getBoard()->printShotBoard();
					player_2->getBoard()->printMyBoard();
					std::cout <<"Player 2: Where would you like to SHOOT: "; 

					std::getline(std::cin, guess);

					std::transform(guess.begin(), guess.end(),guess.begin(), ::toupper);	


					if(guess.length() != 2)
					{
						std::cout << "Invalid coordinate! Try again.\n"; //error handling
					}

				}
			}

			shoot(guess); //shoot the location

			if(m_player_1Turn % 2 == 1 && !m_gameOver) //player 1's turn
			{

				std::cout << "PLAYER 1 TURN\n";
				player_1->getBoard()->printShotBoard();
				player_1->getBoard()->printMyBoard();

				std::cout <<"Player 1 please hit enter and let other player shoot (Please don't cheat and look away): "; //print the board for checking hit or not
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //get rid of user's ramdon input to crash the game

				player_1->getBoard()->printIntermission();
			}
			else if(m_player_1Turn % 2 == 0 && !m_gameOver)	//player 2's turn
			{
				std::cout << "PLAYER 2 TURN\n";
				player_2->getBoard()->printShotBoard();
				player_2->getBoard()->printMyBoard();

				std::cout <<"Player 2 please hit enter and let other player shoot (Please don't cheat and look away): "; //print the board
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //ignore random input for Eg: "Smack-Talking"

				player_2->getBoard()->printIntermission();
			}

			m_player_1Turn++; //change player turn
		}
		catch(std::runtime_error &rte)
		{
			std::cout << rte.what();
		}
	}

	if(m_player_1Turn % 2 == 1) //player turn changes
	{
		player_2->getBoard()->printShotBoard();
		player_2->getBoard()->printMyBoard();

		std::cout << "WINNER PLAYER 2!\n";
	}
	else
	{
		player_1->getBoard()->printShotBoard();
		player_1->getBoard()->printMyBoard();

		std::cout << "WINNER PLAYER 1!\n";
	}

}

void Executive::shoot(std::string location)
{
	int numberOfShips = player_1->getBoard()->getNumberofShips(); //sets the number of ships

	bool hit = false;

	if(m_player_1Turn % 2 == 1)
	{
		hit = player_2->gettingShot(location); //check player_2 ship at location
		player_1->shooting(location,hit); //update hit player_1

		for(int i=0;i<numberOfShips;i++)	//game over?
		{
			if(player_2->getBoard()->getShip()[i].isSunk())
			{
				m_gameOver = true;	//true if sank
			}
			else
			{
				m_gameOver = false;	//false if not sunk and break loop
				break;
			}
		}


	}
	else
	{
		hit = player_1->gettingShot(location); //player_1 has ship at location
		player_2->shooting(location,hit); //update hit player_2

		for(int i=0;i<numberOfShips;i++)	//game over?
		{
			if(player_1->getBoard()->getShip()[i].isSunk())
			{
				m_gameOver = true;	//true if sank
			}
			else
			{
				m_gameOver = false; //false if not sunk and break loop
				break;
			}
		}
	}
}

int Executive::boatCheck() //return number of boats
{
	int numOfBoats = 0;						
	std::string tempBoats = " ";	//storing numOfBoats as a string

	std::cout << "How many ships would you like to play with? (Choose 1-5): ";		

	std::getline(std::cin, tempBoats);		

	if(tempBoats.length() < 1 || tempBoats.length() > 1)		//check length of string NOT equal to one
	{
		std::cout << "Must be a one-digit number from 1-5!\n";	//error handling when digit was greater than length 1
		return boatCheck();		//return boatCheck function to get a new input 
	}

	else		//if tempBoats equal to 1
	{
		numOfBoats = tempBoats.at(0) - '0';		//set numOfBoats integer equal to the first character of the tempBoats string

		if(numOfBoats < 1 || numOfBoats > 5)		//if numOfBoats is not between 1 and 5
		{
			std::cout << "Must be an integer from 1-5!\n";		//error handling
			return boatCheck();		//get a new input for the number of boats desired
		}

		else
		{
			return numOfBoats;		//if boats valid (1-5), return numOfBoats
		}
	}

}
