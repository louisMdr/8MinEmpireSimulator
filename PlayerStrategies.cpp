#include "PlayerStrategies.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;
class Player;

Strategy::Strategy()
{}

Strategy::~Strategy() {}

//OPERATORS
  void Strategy::setStrategy(int nbr)
  {
    this->type = nbr;
  }
  int Strategy::getStrategy() const
  {
    return this->type;
  }

HumanStrategy::HumanStrategy()
{
  Strategy::setStrategy(1);
}

HumanStrategy::~HumanStrategy() {}

int HumanStrategy::pickCard(Player& player, std::vector<Cards*>& cardSpace)
{
      bool successfullPurchase = false;
      int position, index, cost;
        do {
        std::cin >> position;
        if (position < 1 || position > 6) {
            std::cout << "Invalid input: " << position << ". Please enter an integer from 1 to 6: " << std::endl;
            continue;
        }
        if (position == 1) {
            cost = 0;
        }
        else if (position == 2 || position == 3) {
            cost = 1;
        }
        else if (position == 4 || position == 5) {
            cost = 2;
        }
        else if (position == 6) {
            cost = 3;
        }

        successfullPurchase = player.PayCoin(cost);

    } while (!successfullPurchase); //test comment

    index = position - 1;

    player.getHand()->emplace_back(cardSpace.at(index));

    std::cout << player.getName() << " added the following card to their hand: " << *player.getHand()->back() << std::endl;
    return position;
}

bool HumanStrategy::startArmy(Player* players, Territory* startingRegion, Map& theMap)
{
			string region;
			cin >> region;
			bool successMove = players->MoveArmies(1, startingRegion->getCountry(), region, theMap);
      return successMove;
}

int HumanStrategy::bidChoice(Player* player)
{
int bid;
std::cin >> bid;
while (bid < 0 || bid > player->getCoins()) 
{
  std::cout << "Invalid Bid! Please enter a number between 0 and " << player->getCoins() << ": ";
  std::cin >> bid;
}
return bid;
}

void HumanStrategy::moveArmy(Player* player, int value, Map& gameBoard)
{
  std::string start;
	std::string end;
  
  std::cout << "Choose origin region: " << std::endl;
  std::cin >> start;
  std::cout << "Choose destenation region: " << std::endl;
  std::cin >> end;

  player->MoveArmies(value, start, end, gameBoard);
}


int HumanStrategy::pickBetween(std::string first, std::string second, int val1, int val2)
{
  int choice;
  std::cin >> choice;
  return choice;
}

std::string HumanStrategy::pickCityRegion(Map &gameBoard, Player& player)
{
  std::string regionChoice;
  std::cin >> regionChoice;
  return regionChoice;
}

std::string HumanStrategy::pickDestroyTerritory(Map &gameBoard, Player& player)
{
  std::string regionChoice;
  std::cin >> regionChoice;
  return regionChoice;
}

std::string HumanStrategy::pickDestroyPlayer(std::string region, Map &gameBoard, Player& player)
{
  std::string regionChoice;
  std::cin >> regionChoice;
  return regionChoice;
}

std::string HumanStrategy::placeArmyTerritory(Map &gameBoard, Player& player)
{
  std::string picked;
  std::cin >> picked;
  return picked;
}

int HumanStrategy::placeArmyCount(Map &gameBoard, int armiesToPlace)
{
  //subtracting the of armies from the alloted armies
		int ammountChoice;
		std::cin >> ammountChoice;
    return ammountChoice;
}

//----------------------

GreedyStrategy::GreedyStrategy()
{
  Strategy::setStrategy(2);
}

GreedyStrategy::~GreedyStrategy() {}


int GreedyStrategy::pickCard(Player& player, std::vector<Cards*>& cardSpace)
{
    //building cities or destroying opponents
    //stores cost of each build city
    // Cards* buildCityard;
    // int buildCityCount;
    int position;
    int cost;
    //going through the cards
    for(int i=0;i<6;i++)
    {
      position = i+1;

      if (position == 1) {
        cost = 0;
      }
      else if (position == 2 || position == 3) {
          cost = 1;
      }
      else if (position == 4 || position == 5) {
          cost = 2;
      }
      else if (position == 6) {
          cost = 3;
      }



      //if card is cheap enough
      if(cost <= player.getCoins() && player.getCoins() != 0)
      {
        //if card is about building cities
        if( (cardSpace[i]->getAction())->find("BUILD_CITIES") != std::string::npos )
        {
          std::cout << position << std::endl;
          player.PayCoin(cost);
          player.getHand()->emplace_back(cardSpace[i]);
          std::cout << player.getName() << " added the following card to their hand: " << *player.getHand()->back() << std::endl;
          int position2 = i + 1;
          // player.BuildCity(Map &gameBoard);
          return position2;
        }
        //to call different method?
        else if( (cardSpace[i]->getAction())->find("DESTROY_ARMIES") != std::string::npos )
        {
          std::cout << position << std::endl;
          player.PayCoin(cost);
          player.getHand()->emplace_back(cardSpace[i]);
          std::cout << player.getName() << " added the following card to their hand: " << *player.getHand()->back() << std::endl;
          int position2 = i + 1;
          return position2;
        }
      }
    }

    //being here means all too expensive or not the same type
    //default: cheapest card
    position = 1;
    std::cout << position << std::endl;
    player.PayCoin(cost);
    player.getHand()->emplace_back(cardSpace[0]);
    std::cout << player.getName() << " added the following card to their hand: " << *player.getHand()->back() << std::endl;
    return position;
}

bool GreedyStrategy::startArmy(Player* players, Territory* startingRegion, Map& theMap)
{
    vector<Territory*> temp = *theMap.getVectorOfTerritories();
    //get random country
    string region = temp[(rand() % temp.size())]->getCountry();
    std::cout << region << std::endl;
    bool successMove = players->MoveArmies(1, startingRegion->getCountry(), region, theMap);
    return successMove;
}

int GreedyStrategy::bidChoice(Player* player)
{
int bid = rand() % (player->getCoins());
std::cout << bid << std::endl;
return bid;
}

void GreedyStrategy::moveArmy(Player* player, int value, Map& gameBoard)
{
  std::string start;
	std::string end;
  

  player->MoveArmies(value, start, end, gameBoard);
}

int GreedyStrategy::pickBetween(std::string first, std::string second, int val1, int val2)
{
  if(first.find("BUILD_CITIES") != std::string::npos || first.find("DESTROY_ARMIES") != std::string::npos)
  {
				return 1;
	}
  else if(second.find("BUILD_CITIES") != std::string::npos || second.find("DESTROY_ARMIES") != std::string::npos)
  {
    return 2;
  }
  else
  {
    return rand() % 2;
  }
  
}

std::string GreedyStrategy::pickCityRegion(Map &gameBoard, Player& player)
{
  std::vector<std::string>* placementTerritories = gameBoard.getRegionsToAddCities(player.getName());
  int index = rand() % placementTerritories->size();
  std::string regionChoice = placementTerritories->at(index);
  return regionChoice;
}

std::string GreedyStrategy::pickDestroyTerritory(Map &gameBoard, Player& player)
{
  std::string regionChoice;
  std::vector<std::string> playerOptions;

  for (int i = 0; gameBoard.getVectorOfTerritories()->size(); i++) 
  {
    int hasArmy = 0;
    std::vector<std::string> temp = gameBoard.getVectorOfTerritories()->at(i)->playerWithArmies;

    for (int j = 0; temp.size(); j++) {
        if (temp[j] == player.getName()) {
            hasArmy = 1;
        }
    }

    if (hasArmy == 1) 
    {
        playerOptions.push_back(gameBoard.getVectorOfTerritories()->at(i)->getContinent());
    }

  }

  return playerOptions.at(rand() % size(playerOptions));
}

std::string GreedyStrategy::pickDestroyPlayer(std::string region, Map &gameBoard, Player& player)
{
  std::vector<std::string> playerOptions;

  for (int i = 0; gameBoard.getVectorOfTerritories()->size(); i++) 
  {
    int hasArmy = 0;
    std::vector<std::string> temp = gameBoard.getVectorOfTerritories()->at(i)->playerWithArmies;

    for (int j = 0; temp.size(); j++) {
        if (temp[j] == player.getName()) {
            hasArmy = 1;
        }
    }

    if (hasArmy == 1) 
    {
        for (int k = 0; gameBoard.getVectorOfTerritories()->at(i)->playerArmies.size(); k++) {
                if (gameBoard.getVectorOfTerritories()->at(i)->playerArmies[k]->getOwner() != player.getName() && gameBoard.getVectorOfTerritories()->at(i)->playerArmies[k]->getAmmount() != 0)
                {
                    playerOptions.push_back(gameBoard.getVectorOfTerritories()->at(i)->playerArmies[k]->getOwner());
                }
            }
    }

  }

  return playerOptions.at(rand() % size(playerOptions));
}

std::string GreedyStrategy::placeArmyTerritory(Map &gameBoard, Player& player)
{
  std::vector<std::string>*  placementTerritories = gameBoard.getRegionsToAddArmies(player.getName());

  std::string picked = placementTerritories->at(rand() % placementTerritories->size());
  return picked;
}

int GreedyStrategy::placeArmyCount(Map &gameBoard, int armiesToPlace)
{
  int taken;
  do
  {
    taken = rand() % armiesToPlace;
  }
  while(taken == 0);
return taken;
}

//----------------------

ModerateStrategy::ModerateStrategy()
{
  Strategy::setStrategy(3);
}

ModerateStrategy::~ModerateStrategy() {}

int ModerateStrategy::pickCard(Player& player, std::vector<Cards*>& cardSpace)
{
    //secure regions - my army > your army
    int position;
    int cost;
    //going through the cards
    for(int i=0;i<6;i++)
    {
      position = i+1;

      if (position == 1) {
        cost = 0;
      }
      else if (position == 2 || position == 3) {
          cost = 1;
      }
      else if (position == 4 || position == 5) {
          cost = 2;
      }
      else if (position == 6) {
          cost = 3;
      }

      //if card is cheap enough
      if(cost <= player.getCoins() && player.getCoins() != 0)
      {
        //if card is about building cities
        if( (cardSpace[i]->getAction())->find("PLACE_ARMIES") != std::string::npos )
        {
          std::cout << position << std::endl;
          //int index = (cardSpace[i]->getAction())->at((cardSpace[i]->getAction())->find("BUILD_CITIES") + 13);
          player.PayCoin(cost);
          player.getHand()->emplace_back(cardSpace[i]);
          std::cout << player.getName() << " added the following card to their hand: " << *player.getHand()->back() << std::endl;
          int position2 = i + 1;
          // player.BuildCity(Map &gameBoard);
          return position2;
        }
        //to call different method?
        else if( (cardSpace[i]->getAction())->find("MOVE_ARMIES") != std::string::npos )
        {
          std::cout << position << std::endl;
          player.PayCoin(cost);
          player.getHand()->emplace_back(cardSpace[i]);
          std::cout << player.getName() << " added the following card to their hand: " << *player.getHand()->back() << std::endl;
          int position2 = i + 1;
          // player.DESTROY_ARMIES
          return position2;
        }
      }
    }

    //being here means all too expensive or not the same type
    //default: cheapest card
    position = 1;
    std::cout << position << std::endl;
    player.PayCoin(cost);
    player.getHand()->emplace_back(cardSpace[0]);
    std::cout << player.getName() << " added the following card to their hand: " << *player.getHand()->back() << std::endl;
    return position;
}

bool ModerateStrategy::startArmy(Player* players, Territory* startingRegion, Map& theMap)
{
  vector<Territory*> temp = *theMap.getVectorOfTerritories();
    //get random country
    string region = temp[(rand() % temp.size())]->getCountry();
    std::cout << region << std::endl;
    bool successMove = players->MoveArmies(1, startingRegion->getCountry(), region, theMap);
    return successMove;
}


int ModerateStrategy::bidChoice(Player* player)
{
int bid = rand() % (player->getCoins());
std::cout << bid << std::endl;
return bid;
}


void ModerateStrategy::moveArmy(Player* player, int value, Map& gameBoard)
{
  std::string start;
	std::string end;

  player->MoveArmies(value, start, end, gameBoard);
}

int ModerateStrategy::pickBetween(std::string first, std::string second, int val1, int val2)
{
  if(first.find("PLACE_ARMIES") != std::string::npos || first.find("MOVE_ARMIES") != std::string::npos)
    {
          return 1;
    }
    else if(second.find("PLACE_ARMIES") != std::string::npos || second.find("MOVE_ARMIES") != std::string::npos)
    {
      return 2;
    }
    else
    {
      return rand() % 2;
    }
}

std::string ModerateStrategy::pickCityRegion(Map &gameBoard, Player& player)
{
  std::vector<std::string>* placementTerritories = gameBoard.getRegionsToAddCities(player.getName());
  int index = rand() % placementTerritories->size();
  std::string regionChoice = placementTerritories->at(index);
  return regionChoice;
}

std::string ModerateStrategy::pickDestroyTerritory(Map &gameBoard, Player& player)
{
  std::string regionChoice;
  std::vector<std::string> playerOptions;

  for (int i = 0; gameBoard.getVectorOfTerritories()->size(); i++) 
  {
    int hasArmy = 0;
    std::vector<std::string> temp = gameBoard.getVectorOfTerritories()->at(i)->playerWithArmies;

    for (int j = 0; temp.size(); j++) {
        if (temp[j] == player.getName()) {
            hasArmy = 1;
        }
    }

    if (hasArmy == 1) 
    {
        playerOptions.push_back(gameBoard.getVectorOfTerritories()->at(i)->getContinent());
    }

  }

  return playerOptions.at(rand() % size(playerOptions));
}

std::string ModerateStrategy::pickDestroyPlayer(std::string region, Map &gameBoard, Player& player)
{
  std::vector<std::string> playerOptions;

  for (int i = 0; gameBoard.getVectorOfTerritories()->size(); i++) 
  {
    int hasArmy = 0;
    std::vector<std::string> temp = gameBoard.getVectorOfTerritories()->at(i)->playerWithArmies;

    for (int j = 0; temp.size(); j++) {
        if (temp[j] == player.getName()) {
            hasArmy = 1;
        }
    }

    if (hasArmy == 1) 
    {
        for (int k = 0; gameBoard.getVectorOfTerritories()->at(i)->playerArmies.size(); k++) {
                if (gameBoard.getVectorOfTerritories()->at(i)->playerArmies[k]->getOwner() != player.getName() && gameBoard.getVectorOfTerritories()->at(i)->playerArmies[k]->getAmmount() != 0)
                {
                    playerOptions.push_back(gameBoard.getVectorOfTerritories()->at(i)->playerArmies[k]->getOwner());
                }
            }
    }

  }

  return playerOptions.at(rand() % size(playerOptions));
}

std::string ModerateStrategy::placeArmyTerritory(Map &gameBoard, Player& player)
{
  std::vector<std::string>* placementTerritories = gameBoard.getRegionsToAddArmies(player.getName());

  std::string picked = placementTerritories->at(rand() % placementTerritories->size());
  return picked;
}

int ModerateStrategy::placeArmyCount(Map &gameBoard, int armiesToPlace)
{
  int taken;
  do
  {
    taken = rand() % armiesToPlace;
  }
  while(taken == 0);
return taken;
}