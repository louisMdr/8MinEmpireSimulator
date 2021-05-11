#pragma once
#include <string>
#include <vector>
#include <ostream>
#include "BiddingFacility.h"
#include "Map.h"

class Cards;
class BiddingFacility;

class Player {
private:
	//Player Attributes 
	std::string* name;
	int* coins;
	int* score;
	int* elixers;
	int* armies;
	int* cities;
	std::vector<Cards*>* hand;
	std::vector<Territory*>* ownedTerritories;
	BiddingFacility* biddingFacility;



public:
	//Constructor
	Player(std::string name, int numOfPlayers);
	//Copy Constructor
	Player(const Player& player);
	//Desconstructor
	~Player();

	//Assignment opperator
	void operator = (const Player& player);

	//Player Action Methods
	bool PayCoin(int cost);
	void InitializeNewArmies(int amount, Map& map);
	void placeNewArmies(int amount, Map& gameBoard);
	bool MoveArmies(int amount, std::string regionFrom, std::string regionTo, Map &aMap);
	void BuildCity(Map &gameBoard);
	void DestroyArmy(std::vector<Player*>, Map &gameBoard, int ammount);
	void andOr(std::string type, std::string first, std::string second, int val1, int val2);

	//Accessors
	std::string getName() const;
	int getCoins() const;
	int getArmies() const;
	int getCities() const;
	int getElixers() const;
	int getScore() const;
	std::vector<Cards*>* getHand() const;
	std::vector<Territory*>* getTerritories() const;
	BiddingFacility* getBiddingFacility() const;

	//Mutators
	void setCoins(int coins);
	void setArmies(int armies);
	void setCities(int cities);
	void setName(std::string name);
	void returnArmies(int armies);

	//Score based methods
	void ComputeScore();
	int computeAttributePoints(std::vector<Cards*>* playerHand, int coins, std::string desiredAttribute);
	void increaseElixers(int numOfExliers);
	void increaseScore(int numOfNewPoints);

	friend std::ostream& operator<<(std::ostream& os, const Player& dt);
};
