#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include <iostream>


//Constructor
Player::Player(std::string name, int numOfPlayers)
{
	Player::name = new std::string(name);
	Player::armies = new int(14);
	Player::score = new int(0);
  Player::cities = new int(3);
	Player::elixers = new int(0);
	Player::hand = new std::vector<Cards*>();
	Player::biddingFacility = new BiddingFacility();
	Player::ownedTerritories = new std::vector<Territory*>();

	switch (numOfPlayers)
	{
	case 2:
		Player::coins = new int(14);
		break;
	case 3:
		Player::coins = new int(11);
		break;
	case 4:
		Player::coins = new int(9);
		break;
	default:
		Player::coins = new int(14);
		break;
	}
}

//Copy Constructor
Player::Player(const Player& player) {
	Player::name = new std::string(*player.name);
	Player::armies = new int(*player.armies);
  Player::score = new int(*player.score);
	Player::cities = new int(*player.cities);
	Player::coins = new int(*player.coins);
	Player::elixers = new int(*player.elixers);
	Player::hand = player.getHand();
	Player::biddingFacility = player.getBiddingFacility();
	Player::ownedTerritories = player.getTerritories();
}

//Deconstrucotor
Player::~Player() {
	delete name;
	name = NULL;

	delete coins;
	coins = NULL;

	delete score;
	score = NULL;

	delete armies;
	armies = NULL;

	delete cities;
	cities = NULL;

	delete elixers;
	elixers = NULL;

	delete hand;
	hand = NULL;

	delete biddingFacility;
	biddingFacility = NULL;

	delete ownedTerritories;
	ownedTerritories = NULL;
};

//Assignement Opperator
void Player::operator = (const Player& player)
{
	Player::name = new std::string(*player.name);
	Player::armies = new int(*player.armies);
  Player::score = new int(*player.score);
	Player::cities = new int(*player.cities);
	Player::coins = new int(*player.coins);
	Player::elixers = new int(*player.elixers);
	hand = player.getHand();
	biddingFacility = player.getBiddingFacility();
	ownedTerritories = player.getTerritories();
}

//Stream Operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
	os << "Name: " << player.getName() << " / Coins: " << player.getCoins() << " / Armies: " << player.getArmies() << " / Cities: " << player.getCities();
	return os;
}

//Accessors
std::string Player::getName() const {
	return *name;
};
int Player::getCoins() const {
	return *coins;
};
int Player::getScore() const {
	return *score;
};
int Player::getElixers() const {
	return *elixers;
};
int Player::getArmies() const {
	return *armies;
};
int Player::getCities() const {
	return *cities;
};
std::vector<Cards*>* Player::getHand() const {
	return hand;
};
std::vector<Territory*>* Player::getTerritories() const {
	return ownedTerritories;
};
BiddingFacility* Player::getBiddingFacility() const {
	return biddingFacility;
};

//Mutators
void Player::setName(std::string name) {
	*Player::name = name;
};

void Player::setCoins(int coins) {
	*Player::coins = coins;
};

void Player::setArmies(int armies) {
	*Player::armies = armies;
};

void Player::setCities(int cities) {
	*Player::cities = cities;
};

void Player::returnArmies(int armies) {
	*Player::armies += armies;
}

//Player Action Methods

//Checking if player has sufficent coins to make purchase and if so to deduct the ammount
bool Player::PayCoin(int cost) {
	if (*coins < cost) {
		std::cout << "Player " << *name << " has insufficient coins, unable to make the purchase" << std::endl;
		return false;
	}
	else
	{
		setCoins(*coins - cost);
		std::cout << "Purchase was sucessfull, " << *name << " has " << *coins << " coins remaining" << std::endl;
		return true;
	}
}

//Places armies for the start of the game
void Player::InitializeNewArmies(int amount, Map& map) {
	int temp_armies = *armies;
	if (*armies == 0 || amount <= 0) {
		std::cout << "Player " << *name << " does not have any armies to place" << std::endl;
		return;
	}
  *armies -= amount;
  Territory* startingRegion = map.getVectorOfTerritories()->front();
  startingRegion->setNbrArmies(new int((startingRegion->getNbrArmies())+amount));

	 
  startingRegion->playerArmies.emplace_back(new Armies(*name,amount)); //fixed here!
	std::cout << amount << " army has been placed in starting region (" << startingRegion->getCountry() << ")" << std::endl;
  //prevent de-allocation
  startingRegion = NULL;
}

//Places new armies when available
void Player::placeNewArmies(int totalArmies, Map& gameBoard) {

	//Checking if the player has any available armies to place
	if (*armies == 0) {
		std::cout << *name << " does not have available armies to place." << std::endl;
		return;
	}

	int armiesToPlace;
	std::vector<std::string> placementTerritories;

	//If player does not have sufficient armies for the value on the card, what is left is placed
	if (totalArmies > *armies) {
		armiesToPlace = *armies;
	}
	else {
		armiesToPlace = totalArmies;
	}

	//Loop to place armies
	for (int i = 0; i < armiesToPlace; i++) {
		
		std::cout << *name << " has " << armiesToPlace << " armies to place." << std::endl;
		std::cout << "Regions where armies can be placed: " << std::endl;

		//retriving list of terrirotries where the player can place an army
		placementTerritories = gameBoard.getRegionsToAddArmies(*name);

		for (int j = 0; placementTerritories.size(); j++) {
			std::cout << placementTerritories[j] << std::endl;
		}

		//prompting the user
		std::cout << "What is your choice?: " << std::endl;

		std::string regionChoice;
		std::cin >> regionChoice;

		std::cout << "How many armies?: " << std::endl;
		
		//subtracting the of armies from the alloted armies
		int ammountChoice;
		std::cin >> ammountChoice;
		armiesToPlace = armiesToPlace - ammountChoice;

		//adding the armies to the board
		gameBoard.addArmy(*name, regionChoice, ammountChoice);

		std::cout << "Armies placed!" << std::endl;
	}
	std::cout << "Done!" << std::endl;

	(*armies) = (*armies) - armiesToPlace;
}

//Method to move armies from one region to another
bool Player::MoveArmies(int amount, std::string regionFrom, std::string regionTo, Map &aMap)
{
  if(regionFrom == "" || regionTo == "" || regionFrom == regionTo)
  {
    std::cout << "No/Invalid region(s) specified to move armies." << std::endl;
    return false;
  }
  else if(amount <= 0)
  {
    std::cout << "No/Invalid amount specified to move armies." << std::endl;
    return false;
  }
  std::vector<Territory*>* allRegions = aMap.getVectorOfTerritories();
  Territory *start = NULL, *end = NULL;

  for(int i=0; i<allRegions->size();i++)
  {
    Territory* regionI = (*allRegions)[i];
    if(regionI->getCountry() == regionFrom)
    {
      start = regionI;
    }
    else if(regionI->getCountry() == regionTo)
    {
      end = regionI;
    }
  }
  //check if the territories exist in map
  if(start && end)
  {
    start->setNbrArmies(new int(start->getNbrArmies()-amount));
    end->setNbrArmies(new int(end->getNbrArmies()+amount));
    std::cout << "Player " << *name << " has moved " << amount << " army from " << start->getCountry() << " to " << end->getCountry() << '.' << std::endl;
    return true;
  }
  else if(!start)
  {
    std::cout << "Error: Region of origin: \"" << regionFrom << "\" is not in the Map." << std::endl;
    return false;
  }
  else
  {
    std::cout << "Error: Region of destination: \"" << regionTo << "\" is not in the Map." << std::endl;
    return false;
  }
}

//Method to build a city
void Player::BuildCity(Map &gameBoard) {
	//No more city pieces
	if (*cities == 0) {
		std::cout << "Player " << *name << " has insufficient available cities to build" << std::endl;
		return;
	}
	else
	{
		std::vector<std::string> placementTerritories;

		std::cout << "Regions where cities can be placed: " << std::endl;

		//Getting a list of territories where the player can place an army
		placementTerritories = gameBoard.getRegionsToAddCities(*name);
		for (int j = 0; placementTerritories.size(); j++) {
			std::cout << placementTerritories[j] << std::endl;
		}

		//Prompting the user
		std::cout << "What is your choice?: " << std::endl;

		std::string regionChoice;
		std::cin >> regionChoice;
		
		//Placing the city
		gameBoard.addCity(*name, regionChoice);

		std::cout << "City placed!" << std::endl;

		(*cities)--;
	}
}

void Player::DestroyArmy(std::vector<Player*> players, Map &gameBoard, int amount) {

	std::vector<std::string> placementTerritories;

	std::cout << "Armies that you can destroy:" << std::endl;
	gameBoard.getRegionsToRemoveArmy(*name);

	std::string regionChoice;
	std::string playerChoice;

	std::cout << "Which territoy?" << std::endl;
	std::cin >> regionChoice;

	std::cout << "Which player?" << std::endl;
	std::cin >> playerChoice;

	gameBoard.removeArmy(regionChoice,playerChoice,amount);

	std::cout << "Army has been destroyed!" << std::endl;

	for (int i = 0; players.size(); i++) {
		if (players[i]->getName() == playerChoice) {
			players[i]->returnArmies(amount);
		}
	}
}

void Player::andOr(std::string type, std::string first, std::string second, int val1, int val2) {
	if (type == "+") {
		if (first.find("PLACE") != std::string::npos) {

		}
		else if (first.find("MOVE") != std::string::npos) {

		}
		else if (first.find("BUILD") != std::string::npos) {

		}
		else if (first.find("DESTROY") != std::string::npos) {

		}

		std::cout << "First action done!" << std::endl;

		if (second.find("PLACE") != std::string::npos) {

		}
		else if (second.find("MOVE") != std::string::npos) {

		}
		else if (second.find("BUILD") != std::string::npos) {

		}
		else if (second.find("DESTROY") != std::string::npos) {

		}
	}
	else if (type == "/") {
		std::cout << "Please choose 1: " << first << " or 2: " << second << std::endl;
		int choice;
		std::cin >> choice;

		if (choice == 1) {
			if (first.find("PLACE") != std::string::npos) {

			}
			else if (first.find("MOVE") != std::string::npos) {

			}
			else if (first.find("BUILD") != std::string::npos) {

			}
			else if (first.find("DESTROY") != std::string::npos) {

			}
		}
		else if (choice == 2) {
			if (second.find("PLACE") != std::string::npos) {

			}
			else if (second.find("MOVE") != std::string::npos) {

			}
			else if (second.find("BUILD") != std::string::npos) {

			}
			else if (second.find("DESTROY") != std::string::npos) {

			}
		}
	}
}

void Player::increaseScore(int numOfNewPoints)
{
	*score += numOfNewPoints;
}

void Player::increaseElixers(int numOfExliers)
{
	*elixers += numOfExliers;
}

void Player::ComputeScore()
{
	std::vector<Cards*>* playerHand = this->getHand();
	int playerCoins = this->getCoins();

	std::string good;
	std::string goodTag;

	std::cout << "Computing score for " << this->getName() << std::endl;

	//Computing the score depending on the cards that the player has
	for (int i = 0; i < playerHand->size(); i++)
	{
		good = *playerHand->at(i)->getGood();
		goodTag = good.substr(0, good.find("_"));

		//std::cout << "Good Tag: " << goodTag << std::endl;//Tag on the front of the goods ///TESTING

		if (goodTag == "VP")
		{
			*score += computeAttributePoints(playerHand, playerCoins, good.erase(0, good.find("_") + 1));
		}
		else if (goodTag == "Elixer")
		{
			this->increaseElixers(*playerHand->at(i)->getNumOfGood());
		}
	}

	//Compute the points that the player recieves from the regions and continents they own
	*score += this->getTerritories()->size();
}

int Player::computeAttributePoints(std::vector<Cards*>* playerHand, int coins, std::string desiredAttribute)
{
	int scoreIncrease(0);
	int playerOwnedAttribute(0);

	//std::cout << "Good Attribute: " << desiredAttribute << std::endl; // TESTING

	if (desiredAttribute == "Coins")
	{
		scoreIncrease = coins / 3;
	}
	else
	{
		for (int i = 0; i < playerHand->size(); i++)
		{
			if (*playerHand->at(i)->getAttribute() == desiredAttribute) // checks the attribute of the standard card
			{
				playerOwnedAttribute++;
			}
			// checks the good instead of the attribute for flying cards if needed
			// It is possible for a card to have a valid attribute and be able to fly
			else if (desiredAttribute == "Flying" && *playerHand->at(i)->getGood() == desiredAttribute)
			{
				playerOwnedAttribute++;
			}
		}

		if (desiredAttribute == "Noble")
		{
			if (playerOwnedAttribute == 3)
			{
				scoreIncrease += 4;
			}
		}
		else if (desiredAttribute == "Mountain")
		{
			if (playerOwnedAttribute == 2)
			{
				scoreIncrease += 3;
			}
		}
		else
		{
			scoreIncrease += playerOwnedAttribute;
		}

	}

	return scoreIncrease;
}