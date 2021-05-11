#include <iostream>
#include <vector>
#include <set>
#include "Map.h"



int Map::nbrOfMaps = 0;
//Territory (Country and Region) class definitions


Armies::Armies(std::string ownerName, int armyAmmount) {
    Armies::owner = new std::string(ownerName);
    Armies::ammount = new int(armyAmmount);
}
Armies::~Armies() {
    delete owner;
    owner = NULL;

    delete ammount;
    ammount = NULL;
}
void Armies::addAmmount(int add) {
    (*ammount) = (*ammount) + add;
}
void Armies::removeAmmount(int remove) {
    if ((*ammount) < remove) {
        (*ammount) = 0;
    }
    else {
        (*ammount) = (*ammount) - remove;
    }
}
std::string Armies::getOwner() const {return *owner;}
int Armies::getAmmount() const { return *ammount; }

Cities::Cities(std::string ownerName) {
    Cities::owner = new std::string(ownerName);
}
Cities::~Cities() {
    delete owner;
    owner = NULL;
}
std::string Cities::getOwner() const { return *owner; }


//Default constructor (not used)
Territory::Territory() : country(new std::string("")), continent(new std::string("")), nbrArmies(new int(0)), adjRegions(NULL)
{}

//Continent constructor
Territory::Territory(bool* isRegion, std::string* continentName) : isCountry(isRegion), country(NULL), continent(continentName), nbrArmies(new int(0)), ownerName(NULL), adjRegions(NULL)
{}

//Region/Country constructor
//!Continent string doesn't create a continent (placeholder only so the continent needs to be created after)
Territory::Territory(bool* isRegion, std::string* countryName, std::string* continentName, int* nbrArmy, std::string* ownerName, std::vector<Territory*>* adjCountries) : isCountry(isRegion), country(countryName), continent(continentName), nbrArmies(nbrArmy), ownerName(ownerName), adjRegions(adjCountries)
{}

//destructor - (all regions/continents are deleted in Map class) 
Territory::~Territory()
{
    delete isCountry;
    isCountry = NULL;
    delete continent;
    continent = NULL;
    delete nbrArmies;
    nbrArmies = NULL;
    delete ownerName;
    ownerName = NULL;
    delete adjRegions;
    adjRegions = NULL;

    for (int i = 0; playerArmies.size(); i++) {
        delete playerArmies[i];
    }
    playerArmies.clear();

    for (int i = 0; playerCities.size(); i++) {
        delete playerCities[i];
        playerCities[i] = NULL;
    }
    playerCities.clear();
}

//Accessors
bool Territory::getTerritoryType() { return *isCountry; }

std::string Territory::getCountry() { return *country; }

std::string Territory::getContinent() { return *continent; }

std::string Territory::getOwner() { return *ownerName; }

int Territory::getNbrArmies() { return *nbrArmies; }

std::vector<Territory*>* Territory::getadjRegions() { return adjRegions; }

//Mutators
void Territory::setNbrArmies(int* count) { this->nbrArmies = count; }

//Method to add adjacent territories (one direction: add new Territory to 'this')
void Territory::addAdjTerritory(Territory* newTerritory)
{
    if (*isCountry == true && *newTerritory->isCountry == true)
    {
        for (int i = 0; i < adjRegions->size(); i++)
        {
            //If the country is already in the adjacency list, we don't add it to avoid duplicates
            if ((*adjRegions)[i]->getCountry() == newTerritory->getCountry())
            {
                //testing
                //std::cout << "Duplicate territory: already exists witin the adjacent regions" << std::endl;
                return;
            }

        }
        adjRegions->push_back(newTerritory);

        //testing
        //std::cout << "Successfully added territory to my adjacency list" << std::endl;
    }
    else
    {
        //keeping out for now
        //std::cout << "Error: Territories aren't both countries!";
    }
}

//Map class definitions
Map::Map() : vectorOfTerritories(new std::vector<Territory*>()), vectorOfContinents(new std::vector<Territory*>())
{
    Map::nbrOfMaps++;
}

Map::Map(std::vector<Territory*>* refTerritory, std::vector<Territory*>* refContinent) : vectorOfTerritories(refTerritory), vectorOfContinents(refContinent)
{
    Map::nbrOfMaps++;
}

Map::Map(const Map& map)
{
    this->vectorOfContinents = new std::vector<Territory*>();
    for (int i = 0; i < map.vectorOfContinents->size(); i++)
    {
        this->vectorOfContinents[i] = map.vectorOfContinents[i];
    }
    this->vectorOfTerritories = new std::vector<Territory*>();
    for (int i = 0; i < map.vectorOfTerritories->size(); i++)
    {
        this->vectorOfTerritories[i] = map.vectorOfTerritories[i];
    }
}

//Since territories will call their own destructor
Map::~Map()
{
    //delete pointers (territories are deleted by their own destroyer)
    (*vectorOfTerritories).clear();
    delete vectorOfTerritories;
    vectorOfTerritories = NULL;
    (*vectorOfContinents).clear();
    delete vectorOfContinents;
    vectorOfContinents = NULL;
}

Map& Map::operator =(const Map& map)
{
    this->vectorOfContinents = new std::vector<Territory*>();
    for (int i = 0; i < map.vectorOfContinents->size(); i++)
    {
        this->vectorOfContinents[i] = map.vectorOfContinents[i];
    }
    this->vectorOfTerritories = new std::vector<Territory*>();
    for (int i = 0; i < map.vectorOfTerritories->size(); i++)
    {
        this->vectorOfTerritories[i] = map.vectorOfTerritories[i];
    }
    return *this;
}

//stream operator for Map class -------NOT FINISHED
std::ostream& operator <<(std::ostream& strm, const Map& map)
{
    std::cout << "Territory:" << std::endl;
    for (int i = 0; i < map.vectorOfTerritories->size(); i++)
    {
        std::cout << '[' << (i + 1) << "] " << (*(*map.vectorOfTerritories)[i]) << std::endl;
    }
    if (map.vectorOfTerritories->size() == 0)
    {
        std::cout << "none";
    }

    std::cout << "Continents:" << std::endl;
    for (int j = 0; j < map.vectorOfContinents->size(); j++)
    {
        std::cout << '[' << (j + 1) << "] " << (*(*map.vectorOfContinents)[j]) << std::endl;
    }
    if (map.vectorOfContinents->size() == 0)
    {
        std::cout << "none";
    }
    return strm << "";
}

//Accessor of map count
int Map::getNbrMaps()
{
    return Map::nbrOfMaps;
};

//copy constructor
Territory::Territory(const Territory& territ)
{
    this->country = new std::string(*(territ.country));
    this->nbrArmies = new int(*(territ.nbrArmies));
    this->continent = new std::string(*(territ.continent));
    this->ownerName = new std::string(*(territ.ownerName));
    this->adjRegions = new std::vector<Territory*>();
    for (int i = 0; i < adjRegions->size(); i++)
    {
        this->adjRegions[i] = territ.adjRegions[i];
    }
}

//assignment operator
Territory& Territory::operator =(const Territory& territ)
{
    this->country = new std::string(*(territ.country));
    this->nbrArmies = new int(*(territ.nbrArmies));
    this->continent = new std::string(*(territ.continent));
    this->ownerName = new std::string(*(territ.ownerName));
    this->adjRegions = new std::vector<Territory*>();
    for (int i = 0; i < adjRegions->size(); i++)
    {
        this->adjRegions[i] = territ.adjRegions[i];
    }
    return *this;
}

//stream operator for Territory class
std::ostream& operator <<(std::ostream& strm, const Territory& territ)
{
    
        std::string adjacents = "";
        for (int i = 0; i < territ.adjRegions->size(); i++)
        {
            adjacents = adjacents.append((*territ.adjRegions)[i]->getCountry() + " ");
        }
        if (adjacents == "")
        {
            adjacents = "none";
        }
        return strm << "Country name: " << *territ.country << ", Armies: " << *territ.nbrArmies << ", Continent: " << *territ.continent << ", Owner/Player: " << *territ.ownerName << ", Adjacent Regions: " << adjacents;
    

}

//Mutator to add territory to map (by reference) either territory or continent
void Map::addToMap(Territory* regionContinent)
{
    if (regionContinent->getTerritoryType() == false)
    {
        if (vectorOfContinents->size() == 0)
        {
            vectorOfContinents->push_back(regionContinent);
        }
        else
        {
            for (int i = 0; i < vectorOfContinents->size(); i++)
            {
                //If the country is already in the adjacency list, we don't add it to avoid duplicates
                if (regionContinent->getContinent().compare((*vectorOfContinents)[i]->getContinent()) == 0)
                    return;
            }
            vectorOfContinents->push_back(regionContinent);
        }
    }
    else
    {
        if (vectorOfTerritories->size() == 0)
        {
            vectorOfTerritories->push_back(regionContinent);
        }
        else
        {
            for (int i = 0; i < vectorOfTerritories->size(); i++)
            {
                //If the country is already in the adjacency list, we don't add it to avoid duplicates
                if (regionContinent->getCountry().compare((*vectorOfTerritories)[i]->getCountry()) == 0)
                    return;
            }
            vectorOfTerritories->push_back(regionContinent);
        }
    }

}

//Method (unusued) to add an edge between two nodes in the graph.
void Map::addEdge(Territory* n1, Territory* n2)
{
    /*
    Creating a new edge by connecting two nodes together.
    */
    for (int i = 0; i < vectorOfTerritories->size(); i++)
    {
        //if a node in territorylist is the same as the n1 node
        if ((*vectorOfTerritories)[i]->getCountry() == n1->getCountry())
        {
            //add n2 as an adjacent territory
            (*vectorOfTerritories)[i]->addAdjTerritory(n2);
        }
        //if a node in territorylist is the same as the n2 node
        if ((*vectorOfTerritories)[i]->getCountry() == n2->getCountry())
        {
            //add n1 as an adjacent territory
            (*vectorOfTerritories)[i]->addAdjTerritory(n1);
        }
    }
}

//Both accessors return a shallow copy
std::vector<Territory*>* Map::getVectorOfTerritories()
{
    std::vector<Territory*>* territories = new std::vector<Territory*>();
    for (int i = 0; i < vectorOfTerritories->size(); i++)
    {
        territories->push_back((*vectorOfTerritories)[i]);
    }
    return territories;
}


std::vector<Territory*>* Map::getVectorOfContinents()
{
    std::vector<Territory*>* continents = new std::vector<Territory*>();
    for (int i = 0; i < vectorOfContinents->size(); i++)
    {
        continents->push_back((*vectorOfContinents)[i]);
    }
    return continents;
}


//////////////////////////Part 4 utility method/////////////////////////////////////////////

//Checking for regions where the player has a city to place armies in
std::vector<std::string> Map::getRegionsToAddArmies(std::string name) {

    //list of regions to return where the player can add an army
    std::vector<std::string> regionNames;
    //adding the starying region
    regionNames.push_back(vectorOfContinents->front()->getCountry());

    //Looping trough all terrirotires 
    for (int i = 1; vectorOfTerritories->size(); i++)
    {
        //getting the list of all players in the territory with a city
        std::vector<std::string> temp = vectorOfTerritories->at(i)->playerWithCities;

        //if the player is in the list then they have a city and can place armies so the region name is added to list to return
        for (int j = 0; temp.size(); j++) {
            if (temp[j] == name) {

                regionNames.push_back(temp[j]);
            }
        }
    }
    return regionNames;
}

//Checking regions where the player has armies and no cities 
std::vector<std::string> Map::getRegionsToAddCities(std::string name) {

    //List of regions to return where the player can place a city
    std::vector<std::string> regionNames;

    //Looping through all territories on the map
    for (int i = 0; vectorOfTerritories->size(); i++)
    {
        int cityBool = 0;//to check if the player has a city already in the territory

        //list of all player that have an army/city in the territory
        std::vector<std::string> temp = vectorOfTerritories->at(i)->playerWithArmies;
        std::vector<std::string> temp2 = vectorOfTerritories->at(i)->playerWithCities;

        //Checking if they have a city
        for (int k = 0; temp2.size(); k++) {
            if (temp2[k] == name) {
                //They do so we will make sure to ommit it from the list
                cityBool = 1;
            }
        }

        //Checking to see if the player has an army in the territory
        for (int j = 0; temp.size(); j++) {
            //will add if player has an army and no city
            if (temp[j] == name && cityBool != 1) {

                regionNames.push_back(temp[j]);
            }
        }
    }
    return regionNames;
}

void Map::getRegionsToRemoveArmy(std::string name) {

    for (int i = 0; vectorOfTerritories->size(); i++) {

        int hasArmy = 0;
        std::vector<std::string> temp = vectorOfTerritories->at(i)->playerWithArmies;

        for (int j = 0; temp.size(); j++) {
            if (temp[j] == name) {
                hasArmy = 1;
            }
        }

        if (hasArmy == 1) {
            std::cout << vectorOfTerritories->at(i)->getContinent() << std::endl;
            for (int k = 0; vectorOfContinents->at(i)->playerArmies.size(); k++) {
                if (vectorOfContinents->at(i)->playerArmies[k]->getOwner() != name && vectorOfContinents->at(i)->playerArmies[k]->getAmmount() != 0) {
                    std::cout << "Player: " << vectorOfContinents->at(i)->playerArmies[k]->getOwner() << " Number of Armies: " << vectorOfContinents->at(i)->playerArmies[k]->getAmmount() << std::endl;
                }
            }
        }
    }

}

//Method to add army to region
void Map::addArmy(std::string name, std::string regionName, int amount) {

    //Looping trough all territories for the specific one
    for (int i = 0; vectorOfContinents->size(); i++) {
       
        if (vectorOfContinents->at(i)->getCountry() == regionName) {
            
            //Looping through all the army objects to find the player's
            for (int j = 0; vectorOfContinents->at(i)->playerArmies.size(); j++) {
                if (vectorOfContinents->at(i)->playerArmies[j]->getOwner() == name) {
                    vectorOfContinents->at(i)->playerArmies[j]->addAmmount(amount);

                    //If the army was previoulsy empty then they must be replaced on the list of players with non empty armies in the territory
                    if (vectorOfContinents->at(i)->playerArmies[j]->getAmmount() == amount) {
                        vectorOfContinents->at(i)->playerWithArmies.push_back(name);
                    }
                }
            }
        }
    }
}

//Method to add a city to a region
void Map::addCity(std::string name, std::string regionName) {
    //Looping trough all territories looking for the specified region and then adding a city object to the region 
    for (int i = 0; vectorOfContinents->size(); i++) {

        if (vectorOfContinents->at(i)->getCountry() == regionName) {
            vectorOfContinents->at(i)->playerCities.emplace_back(new Cities(name)); //modified here
        }
    }
}

void Map::removeArmy(std::string region, std::string playerName, int amount) {
    for (int i = 0; vectorOfContinents->size(); i++) {
        if (vectorOfContinents->at(i)->getCountry() == region) {

            for (int j = 0; vectorOfContinents->at(i)->playerArmies.size(); j++) {

                if (vectorOfContinents->at(i)->playerArmies[j]->getOwner() == playerName) {
                    vectorOfContinents->at(i)->playerArmies[j]->removeAmmount(amount);

                    //If the army was previoulsy empty then they must be replaced on the list of players with non empty armies in the territory
                    if (vectorOfContinents->at(i)->playerArmies[j]->getAmmount() == 0) {
                        for (int k = 0; vectorOfTerritories->at(i)->playerWithArmies.size(); k++) {
                            if (vectorOfTerritories->at(i)->playerWithArmies[k] == playerName) {
                                vectorOfTerritories->at(i)->playerWithArmies[k].erase();
                            }
                        }
                    }
                }
            }
            break;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Validation function
bool Map::validate()
{
    return (validate1() && validate2() && validate3());
}

//every region x must be adjacent to at least one other region y to be a graph
bool Map::validate1()
{
    if ((vectorOfTerritories)->size() == 0 && vectorOfContinents->size() == 0)
    {
        std::cout << "V1: true (empty map)" << std::endl;
        return true;
    }
    //base case - only one country (with its continent) so no adjacent countries needed
    if ((vectorOfTerritories)->size() == 1)
    {
        if (vectorOfContinents->size() >= 1)
        {
            std::cout << "V1: true" << std::endl;
            return true;
        }
        else
        {
            std::cout << "V1 Error: 1 country but missing its continent" << std::endl;
            return false;
        }
    }
    for (int i = 0; i < vectorOfTerritories->size(); i++)
    {
        if ((*vectorOfTerritories)[i]->getadjRegions()->size() == 0)
        {
            std::cout << "V1 Error: At least 1 country is not connected to any other country in the map" << std::endl;
            return false;
        }
    }
    //testing
    //std::cout << "V1: true" << std::endl;
    return true;
}


//Testing the graph's existence and if both graphs have the same continents (focuses on the count, not the name (validate3))
bool Map::validate2()
{
    if ((vectorOfTerritories)->size() >= 1 && (vectorOfContinents)->size() == 0)
    {
        std::cout << "V2 Error: Continent subgraph hasn't been generated" << std::endl;
        return false;
    }
    else
    {
        std::set<std::string> tempContinents;
        for (int i = 0; i < (vectorOfTerritories)->size(); i++)
        {
            tempContinents.insert((*vectorOfTerritories)[i]->getContinent());
        }
        if (tempContinents.size() == (vectorOfContinents)->size())
        {
            //Testing
            //std::cout << "V2: true" << std::endl;
            return true;
        }
        else
        {
            std::cout << "V2 Error: Subgraph missing continents." << std::endl;
            return false;
        }
    }
}

//Ensures every country has a continent & those continents are in the continent subgraph (duplicates checked too)
bool Map::validate3()
{
    //3) for continent, get a string vector of the continent names
      //then loop in graph to check if each continent is associated with one AND only one node. If no, then it means subgraph error! WHY? Unknown loose continent

    //No regions in map -> true
    if ((vectorOfTerritories)->size() == 0)
    {
        std::cout << "V3: true (No regions located)" << std::endl;
        return true;
    }
    for (int i = 0; i < vectorOfTerritories->size(); i++)
    {
        std::string tempContinent = (*vectorOfTerritories)[i]->getContinent();
        //checking if each country belongs to only one continent
        if (tempContinent.empty())
        {
            std::cout << "V3 Error: a region has no continent." << std::endl;
            return false;
        }
        //for each country i check that its continent is in the continent graph
        int inListCount = 0;
        for (int j = 0; j < vectorOfContinents->size(); j++)
        {
            if (tempContinent.compare((*vectorOfContinents)[j]->getContinent()) == 0)
            {
                inListCount += 1;
            }
        }
        if (inListCount == 0)
        {
            std::cout << "V3 Error: A region's continent is not present in the continent subgraph." << std::endl;
            return false;
        }
        else if (inListCount > 1)
        {
            std::cout << "V3 Error: Duplicate entries of continent present in continent list." << std::endl;
            return false;
        }
    }
    //Testing
    //std::cout << "V3: true" << std::endl;
    return true;
}

