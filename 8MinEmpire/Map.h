#pragma once
#include <iostream>
#include <vector>



//Utility classes to know how who has armies/cities in a territory and how much
class Armies
{
private:
    std::string* owner;
    int* ammount;
public:
    Armies(std::string ownerName, int armyAmmount);
    ~Armies();

    void addAmmount(int add);
    void removeAmmount(int remove);

    std::string getOwner() const;
    int getAmmount() const;


};

class Cities
{
private:
    std::string* owner;
public:

    Cities(std::string ownerName);
    ~Cities();

    std::string getOwner() const;
};

//Territory = Node of Country/Region
class Territory
{
private:
    bool* isCountry;
    //name of said country
    std::string* country;
    //name of continent it belongs to
    std::string* continent;
    //vector of pointers to territories (for adjacent regions)
    std::vector<Territory*>* adjRegions;
    //army count
    int* nbrArmies;
    //owner of said country
    std::string* ownerName;
    //<< operator for Territory class
    friend std::ostream& operator<<(std::ostream&, const Territory&);
public:
    //for country
    Territory();
    //Continent constructor
    Territory(bool* isRegion, std::string* continentName);
    //Country/Region constructor
    Territory(bool* isRegion, std::string* countryName, std::string* continentName, int* nbrArmy, std::string* ownerName, std::vector<Territory*>* adjCountries);
    //copy constructor
    Territory(const Territory& territ);
    //destructor
    ~Territory();
    //assignment operator
    Territory& operator =(const Territory& territ);
    //Accessors
    bool getTerritoryType();
    std::string getCountry();
    std::string getContinent();
    int getNbrArmies();
    std::string getOwner();
    std::vector<Territory*>* getadjRegions();
    //Country * getPointerToCountry() const;
    //Mutators
    void setNbrArmies(int* count);
    //add an adjacent region to 1 territory's list
    void addAdjTerritory(Territory* newTerritory);
    // void setadjRegions(vector<Territory*>* newadjRegions);

    std::vector<std::string> playerWithCities;
    std::vector<std::string> playerWithArmies;
    std::vector<Armies*> playerArmies;
    std::vector<Cities*> playerCities;

//for continents
    std::vector<Territory*>* getNodesInContinent();
};

//Map class to maintain territories
class Map
{
private:
    //keep track of nbr of maps created
    std::vector<Territory*>* vectorOfTerritories;
    std::vector<Territory*>* vectorOfContinents;
    //<< operator for Map class
    friend std::ostream& operator<<(std::ostream&, const Map&);
public:
    static int nbrOfMaps;
    //Constructors
    Map();
    //Constructor in case lists already exist:
    Map(std::vector<Territory*>*, std::vector<Territory*>*);
    //copy constructor
    Map(const Map& map);
    //destructor
    ~Map();
    //Assignment operator
    Map& operator =(const Map& map);

    //Accessor methods
    std::vector<Territory*>* getVectorOfTerritories();
    std::vector<Territory*>* getVectorOfContinents();
    static int getNbrMaps();
    //Mutators
    void addToMap(Territory* regionContinent);
    void addEdge(Territory* n1, Territory* n2);

    //Validation methods
    bool validate();
    bool validate1();
    bool validate2();
    bool validate3();
    // vector<Node*>* getNodesInContinent() { return &nodesInContinent; }

    std::vector<std::string> getRegionsToAddArmies(std::string name);
    std::vector<std::string> getRegionsToAddCities(std::string name);
    void getRegionsToRemoveArmy(std::string name);
    void addArmy(std::string name, std::string regionName, int ammount);
    void addCity(std::string name, std::string regionName);
    void removeArmy(std::string region, std::string playerName, int ammount);
};

