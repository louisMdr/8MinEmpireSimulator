#include "GameEngine.h"
#include "MapLoader.h"
#include <iostream>
#include <string>


GameEngine::GameEngine()
{
	this->turnCount = new int(1);
	this->gameBoard = setupMap();
	this->gamePlayers = setupPlayers();
	this->cardDeck = new Deck(gamePlayers->size());
}

GameEngine::~GameEngine()
{
	delete turnCount;
	turnCount = nullptr;

	delete cardDeck;
	cardDeck = nullptr;

	for (int i = 0; i < gamePlayers->size(); i++)
	{
		delete gamePlayers->at(i);
	}
	gamePlayers->clear();

	delete gamePlayers;
	gamePlayers = nullptr;

	delete gameBoard;
	gameBoard = nullptr;
}


void GameEngine::gameLoop()
{
	//initiatePlayerBoard();														//Initiate the game board
	biddingPlayers();																//Bids for the starting player
	std::vector<Cards*> board6Cards = cardDeck->cardSpaceGenetor(*cardDeck);		//creates the initial card shop

	while (*this->turnCount <= 13)
	{
		std::cout << "\nTurn #" << *turnCount << std::endl;

		cardMainLoop(*turnCount - 1, board6Cards);
		*this->turnCount += 1;
	} 	

	decideWinner();
	
}

Map* GameEngine::setupMap()
{
	MapLoader mpl;
	int mapChoice(0);
	do
	{
		if (mapChoice != 0)
		{
			std::cout << "\nThat was an invalid input!\nPlease make a valid map choice...\n" << std::endl;
		}

		std::cout << "Please select one of the following game Boards:\n" << std::endl;
		std::cout << "1. Settelment of Asia (L shapped map)" << std::endl;
		std::cout << "2. Battle of North America (| shapped map)" << std::endl;

		std::cin >> mapChoice;
	} while (mapChoice <= 0 || mapChoice >= 3);

	switch (mapChoice)
	{
	case 1:
		return mpl.generateMap("LMap.MAP"); // change return type in MAP_LOADER
		break;
	case 2:
		return mpl.generateMap("VerticleMap.MAP"); // change return type in MAP_LOADER
		break;
	}
}

//NEED TO IMPLEMENT THE AI STUFF
std::vector<Player*>* GameEngine::setupPlayers()
{
	int numPlayers(0);
	std::vector<Player*>* players = new std::vector<Player*>;
	std::string name;

	do
	{
		if (numPlayers != 0)
		{
			std::cout << "\nThat was an invalid input!\nPlease make a valid player count choice...\n" << std::endl;
		}

		std::cout << "Please enter the number of players who will participate (2 - 4): ";
		std::cin >> numPlayers;
	} while (numPlayers <= 1 || numPlayers > 4);

	for (int i = 0; i < numPlayers; i++)
	{
		std::cout << "\nPlease enter the name of player " << (i + 1) << ": ";
		std::cin >> name;

		if (name == "")
		{
			i--;
			std::cout << "\nThat was an invalid name. Please enter a valid name for the player...\n" << std::endl;
		}
		else
		{
			players->push_back(new Player(name, 2));
		}
	}

	return players;
}

void GameEngine::decideWinner()
{
	Player* placeholder = gamePlayers->at(0);
	int mostElixers(0);
	int topScore(0);
	int winningPos;

	//Compute the score of the players and add points for most elixers
	for (int i = 0; i < gamePlayers->size(); i++)
	{
		Player* currentPlayer = gamePlayers->at(i);
		currentPlayer->ComputeScore();

		if (gamePlayers->at(i)->getElixers() > mostElixers)
		{
			mostElixers = currentPlayer->getElixers();
			placeholder = currentPlayer;
		}
		else if (currentPlayer->getElixers() == mostElixers && mostElixers != 0)
		{
			mostElixers = 0;
			std::cout << "\nThere was a tie in elixer count, no one shall be recieving points for exliers\n" << std::endl;
			break;
		}
	}

	//increment score of person who has most elixers (if the most is not zero)
	if (mostElixers != 0)
	{
		placeholder->increaseScore(2);
		std::cout << placeholder->getName() << " aquired the most elixers (" << placeholder->getElixers() << ") during the game\n" << std::endl;
	}

	//Compares the scores of all the players
	for (int i = 0; i < gamePlayers->size(); i++)
	{
		Player* currentPlayer = gamePlayers->at(i);
		int currentScore = currentPlayer->getScore();

		//If the current player has a larger score than all the others
		//replace the winner (placeholder) with that player
		if (currentScore > topScore)
		{
			topScore = currentScore;
			placeholder = currentPlayer;
			winningPos = i;
		}
		else if (currentScore == topScore && topScore != 0)
		{
			//If there is a tie, make the comparisons to see if the tied player should win over the current winner
			if (currentPlayer->getCoins() > placeholder->getCoins() || currentPlayer->getArmies() > placeholder->getArmies()
				|| currentPlayer->getTerritories()->size() > placeholder->getTerritories()->size())
			{
				placeholder = currentPlayer;
				winningPos = i;
			}
		}
	}

	std::cout << "Player\t\tCards\t\tVictory points\t\tCoins" << std::endl;
	for (int i = 0; i < gamePlayers->size(); i++)
	{
		Player* temp = gamePlayers->at(i);
		std::cout << temp->getName() << "\t\t" << temp->getHand()->size() << "\t\t" << temp->getScore() << "\t\t\t" << temp->getCoins() << std::endl;
	}

	std::cout << "\nThe winner of the game is: " << placeholder->getName() << "\nwith a score of: " << placeholder->getScore() << std::endl;
	
}

//NEED TO TEST AND FINISH IMPLEMENTING THIS SECTION
//I WILL EDIT THIS LATER

void GameEngine::initiatePlayerBoard()
{
	for (int i = 0; i < gamePlayers->size(); i++)
	{
		std::cout << "\nPlayer " << gamePlayers->at(i)->getName() << ':' << std::endl;
		gamePlayers->at(i)->setArmies(18);
		gamePlayers->at(i)->setCities(3);
		gamePlayers->at(i)->InitializeNewArmies(4, *gameBoard);
	}

	if (gamePlayers->size() == 2)
	{
		//add third player's armies count
		std::cout << "\n5 armies added per player:" << std::endl;
		gamePlayers->at(0)->InitializeNewArmies(5, *gameBoard);
		gamePlayers->at(1)->InitializeNewArmies(5, *gameBoard);

		//each take turns placing armies (player 1 starts by default)
		Territory* startingRegion = gameBoard->getVectorOfTerritories()->front();
		std::cout << "Debug startRegion is: " << startingRegion->getCountry() << std::endl;
		for (int j = 0; j < 10; j++)
		{
			bool successMove = false;
			do
			{
				//uses <cmath> for rounding
				std::cout << gamePlayers->at(j % 2)->getName() << ", which region do you want to place 1 army? (" << round((10.0 - j) / 2) << " left)" << std::endl;
				std::string region;
				std::cin >> region;
				successMove = gamePlayers->at(j % 2)->MoveArmies(1, startingRegion->getCountry(), region, *gameBoard);
			} while (!successMove);

		}
	}
}

void GameEngine::biddingPlayers()
{
	BiddingFacility bidController = BiddingFacility();

	//create array of players
	int startingPlayer = BiddingFacility::biddingPhase(*gamePlayers, 2);
	std::cout << "Player " << gamePlayers->at(startingPlayer)->getName() << " starts the game." << std::endl;

	if (startingPlayer == 0)
	{
		return;
	}
	else // This is hardcoded for two players due to the assignment specifying two players. No time to do otherwise
	{
		Player* p1 = gamePlayers->at(0);
		Player* p2 = gamePlayers->at(1);
		gamePlayers->clear();

		gamePlayers->push_back(p2);
		gamePlayers->push_back(p1);
	}
}

void GameEngine::cardMainLoop(int currentRound, std::vector<Cards*>& board6Cards)
{
	for (int i = 0; i < 2; i++)
	{
		cardDeck->exchange(*gamePlayers->at(i), board6Cards, *cardDeck);
		gamePlayers->at(i)->getHand()->at(currentRound)->performeAction(gamePlayers->at(i));
	}
}