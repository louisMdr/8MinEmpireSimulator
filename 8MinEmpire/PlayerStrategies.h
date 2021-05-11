#pragma once
#include "Map.h"
#include "Cards.h"
#include <iostream>
using namespace std;

//forward declare
class Player;
class Cards;
class Deck;
class Map;

/**
* The classes that implement a concrete strategy should inherit this.
* The Calculator class uses this to use a concrete strategy.
*/
class Strategy {
private:
  int type;
public:
  Strategy();
  Strategy(const Strategy& strat);
  virtual ~Strategy();

  virtual int pickCard(Player& player, std::vector<Cards*>& cardSpace) = 0;
  virtual bool startArmy(Player* players, Territory* startingRegion, Map& theMap) = 0;
  virtual int bidChoice(Player* player) = 0;
  virtual void moveArmy(Player* player, int value, Map& gameBoard) = 0;
  virtual int pickBetween(std::string first, std::string second, int val1, int val2) = 0;
  virtual std::string pickCityRegion(Map &gameBoard, Player& player) = 0;
  virtual std::string pickDestroyTerritory(Map &gameBoard, Player& player) = 0;
  virtual std::string pickDestroyPlayer(std::string region, Map &gameBoard, Player& player) = 0;
  virtual std::string placeArmyTerritory(Map &gameBoard, Player& player) = 0;
  virtual int placeArmyCount(Map &gameBoard, int armiesToPlace) = 0;
  
  void setStrategy(int nbr);
  int getStrategy() const;
  

  
};

//human player that requires user interaction to make decisions
//decided by user interactions only
class HumanStrategy : public Strategy
{
public:
    HumanStrategy();
    HumanStrategy(const HumanStrategy& strat);

    int pickCard(Player& player, std::vector<Cards*>& cardSpace);
    bool startArmy(Player* players, Territory* startingRegion, Map& theMap);
    int bidChoice(Player* player);
    void moveArmy(Player* player, int value, Map& gameBoard);
    int pickBetween(std::string first, std::string second, int val1, int val2);
    std::string pickCityRegion(Map &gameBoard, Player& player);
    std::string pickDestroyTerritory(Map &gameBoard, Player& player);
    std::string pickDestroyPlayer(std::string region, Map &gameBoard, Player& player);
    std::string placeArmyTerritory(Map &gameBoard, Player& player);
    int placeArmyCount(Map &gameBoard, int armiesToPlace);
    ~HumanStrategy();


};

//greedy computer player that focuses on building cities or destroying opponents:
//Attack heavy: use strongest country to conquer weak opponents
//only cities focus - 1 region/country
//defence: protect own country w/ all armies
class GreedyStrategy : public Strategy
{
public:
    GreedyStrategy();
    GreedyStrategy(const GreedyStrategy& strat);
    ~GreedyStrategy();

    int pickCard(Player& player, std::vector<Cards*>& cardSpace);
    bool startArmy(Player* players, Territory* startingRegion, Map& theMap);
    int bidChoice(Player* player);
    void moveArmy(Player* player, int value, Map& gameBoard);
    int pickBetween(std::string first, std::string second, int val1, int val2);
    std::string pickCityRegion(Map &gameBoard, Player& player);
    std::string pickDestroyTerritory(Map &gameBoard, Player& player);
    std::string pickDestroyPlayer(std::string region, Map &gameBoard, Player& player);
    std::string placeArmyTerritory(Map &gameBoard, Player& player);
    int placeArmyCount(Map &gameBoard, int armiesToPlace);

};

//a moderate computer player that control a region in which it just needs to occupy it with more armies than the opponents:
//Defence heavy : reinforce weak countries so army>opponent army
//Not attacker
class ModerateStrategy : public Strategy
{
public:
    ModerateStrategy();
    ModerateStrategy(const ModerateStrategy& strat);
    ~ModerateStrategy();
    // int type;  
    // int getType();

    int pickCard(Player& player, std::vector<Cards*>& cardSpace);
    bool startArmy(Player* players, Territory* startingRegion, Map& theMap);
    int bidChoice(Player* player);
    void moveArmy(Player* player, int value, Map& gameBoard);
    int pickBetween(std::string first, std::string second, int val1, int val2);
    std::string pickCityRegion(Map &gameBoard, Player& player);
    std::string pickDestroyTerritory(Map &gameBoard, Player& player);
    std::string pickDestroyPlayer(std::string region, Map &gameBoard, Player& player);
    std::string placeArmyTerritory(Map &gameBoard, Player& player);
    int placeArmyCount(Map &gameBoard, int armiesToPlace);
    
};

//define class for each action (the others will need to inherit this too I suppose)