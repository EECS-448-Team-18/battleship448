
#include "Executive.h"
#include <limits>
#include "algorithm" //for toupper

int Executive::boatCheck() //will return number of boats when valid
{
	int numOfBoats = 0;						//declaring numberOfBoats
	std::string tempBoats = " ";	//storing numOfBoats as a string

	std::cout << "How many ships would you like to play with? (Choose 1-5): ";		//prompt user for number of ships

	std::getline(std::cin, tempBoats);		//users desired number of boats in a getline

	if(tempBoats.length() < 1 || tempBoats.length() > 1)		//check if the length of the string is NOT equal to one
	{
		std::cout << "Must be a one-digit number from 1-5!\n";	//error handling when digit was greater than length 1
		return boatCheck();		//return the boatCheck function to get a new input 
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

Executive::Executive()		
{
	int numOfBoats = 0;		//store the number of boats

	try		//trying to catch error...
	{
		numOfBoats = boatCheck();		//try block
	}

	catch(std::runtime_error &rte)	//catch error if function fails
	{
		std::cout << "Invalid number of ships";		//print error
	}

	player_1 = new Player(numOfBoats); 		//create player 1 object 
	player_2 = new Player(numOfBoats);		//create player 2 object 
	m_gameOver = false;			//m_gameOver member variable set to false at the beginning
	m_player_1Turn = 1;			// boolean set to 1, game starts with player 1

	std::cout <<"\nPlayer 1 place your ships\n";		//player1 place ships
	player_1 -> getBoard() -> setupBoard();					//get and setup board for player 1
	std::cout <<"\nPlayer 2 place your ships\n";		//player2 place ships
	player_2 -> getBoard() -> setupBoard();					//get and setup board for player 2
	game();		//start the game once both players have set up their boards

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
			guess = " ";			//prevent infinite out of boundary loop

			while(guess.length() != 2)
			{
				if(m_player_1Turn % 2 == 1)	//if it is player 1's turn
				{
					player_1->getBoard()->printShotBoard();
					player_1->getBoard()->printMyBoard();
					std::cout << "Player 1: Where would you like to shoot: "; //print player's board and opponent's board and ask for a location to shoot

					std::getline(std::cin, guess);

					std::transform(guess.begin(), guess.end(),guess.begin(), ::toupper);	

					std::cout << "guess: " << guess << "\n"; //print out guess

					if(guess.length() != 2)
					{
						std::cout << "Invalid coordinate! Try again.\n"; //error handling
					}

				}
				else	//if player 2's turn
				{
					player_2->getBoard()->printShotBoard();
					player_2->getBoard()->printMyBoard();
					std::cout <<"Player 2: Where would you like to shoot: "; //print player's board and opponent's board and ask for a location to shoot

					std::getline(std::cin, guess);

					std::transform(guess.begin(), guess.end(),guess.begin(), ::toupper);	


					if(guess.length() != 2)
					{
						std::cout << "Invalid coordinate! Try again.\n";//error handling
					}

				}
			}

			shoot(guess); //shoot the location

			if(m_player_1Turn % 2 == 1 && !m_gameOver) //if player 1's turn
			{

				std::cout << "PLAYER 1 TURN\n";
				player_1->getBoard()->printShotBoard();
				player_1->getBoard()->printMyBoard();

				std::cout <<"Player 1 please hit enter and let other player shoot at your ships (Please don't cheat and look away): "; //print the board for checking hit or not
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //get rid of user's ramdon input to crash the game

				player_1->getBoard()->printIntermission();
			}
			else if(m_player_1Turn % 2 == 0 && !m_gameOver)	//if it is player 2's turn
			{
				std::cout << "PLAYER 2 TURN\n";
				player_2->getBoard()->printShotBoard();
				player_2->getBoard()->printMyBoard();

				std::cout <<"Player 2 please hit enter and let other player shoot at your ships (Please don't cheat and look away): ";//print the board for checking hit or not and hit
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //get rid of user's random input to crash the game

				player_2->getBoard()->printIntermission();
			}

			m_player_1Turn++; //change player turn
		}
		catch(std::runtime_error &rte)
		{
			std::cout << rte.what();
		}
	}

	if(m_player_1Turn % 2 == 1) //m_player_1Turn gets changed right before this, therefore different value
	{
		player_2->getBoard()->printShotBoard();
		player_2->getBoard()->printMyBoard();

		std::cout << "PLAYER 2 WINS!\n";
	}
	else
	{
		player_1->getBoard()->printShotBoard();
		player_1->getBoard()->printMyBoard();

		std::cout << "PLAYER 1 WINS!\n";
	}

}

void Executive::shoot(std::string location)
{
	int numberOfShips = player_1->getBoard()->getNumberofShips(); //sets the number of ships

	bool hit = false;

	if(m_player_1Turn % 2 == 1)
	{
		hit = player_2->gettingShot(location); //check player_2 has a ship at the location or not
		player_1->shooting(location,hit); //update hit marker for player_1

		for(int i=0;i<numberOfShips;i++)	//checks for game over
		{
			if(player_2->getBoard()->getShip()[i].isSunk())
			{
				m_gameOver = true;	//sets to true if they are sunk
			}
			else
			{
				m_gameOver = false;	//sets back to false if any are not sunk and then breaks out of for loop
				break;
			}
		}


	}
	else
	{
		hit = player_1->gettingShot(location); //check player_1 has a ship at the location or not
		player_2->shooting(location,hit); //update hit marker for player_2

		for(int i=0;i<numberOfShips;i++)	//checks for game over
		{
			if(player_1->getBoard()->getShip()[i].isSunk())
			{
				m_gameOver = true;	//sets to true if they are sunk
			}
			else
			{
				m_gameOver = false; //sets back to false & breaks out of for loop
				break;
			}
		}
	}
}
