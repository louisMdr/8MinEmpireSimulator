#pragma once
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include <vector>


class GameEngine
{
private:
	std::vector<Player*>* gamePlayers;
	Deck* cardDeck;
	Map* gameBoard;
	int* turnCount;

	Map* setupMap();
	std::vector<Player*>* setupPlayers();
	void decideWinner();
	void initiatePlayerBoard();
	void biddingPlayers();
	void cardMainLoop(int currentRound, std::vector<Cards*>& board6Cards);

public:
	GameEngine();
	~GameEngine();
	void gameLoop();
};
