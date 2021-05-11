#pragma once
#include <string>
#include <ostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "Player.h"


// Forward Declaration
class Player;

class Cards
{

private:

    int* numOfGood;
    std::string* attribute;
    std::string* good;
    std::string* action;

public:

    // constructors
    Cards();
    Cards(int numOfGood, std::string attribute, std::string good, std::string action);

    // deconstructor
    virtual ~Cards();

    // copy constructor
    Cards(const Cards& card);

    // assignment operator
    Cards& operator=(const Cards& card);

    // IOStream Overload
    friend std::ostream& operator<<(std::ostream& os, const Cards& cards);
    friend std::istream& operator>>(std::istream& is, Cards& cards);

    // getters
    std::string* getGood() const;
    std::string* getAction() const;
    std::string* getAttribute() const;
    int* getNumOfGood() const;

    // setters
    void setGood(std::string good);
    void setAction(std::string action);
    void setNumOfGood(int numOfGood);
    void setAttribute(std::string attribute);

    void performeAction(Player* player);

};

class Deck
{

private:

    int* cost;
    int* position;
    int posArray[6] = { 0, 1, 1, 2, 2, 3 };

public:
    // constructor
    Deck();

    Deck(int);

    // deconstructor
    virtual ~Deck();

    // gameplay methods
    Cards* draw();
    std::vector<Cards*> cardSpaceGenetor(Deck& deck);
    void displayCardSpace(std::vector<Cards*>& cardSpace);
    void updateCardSpace(int& position, std::vector<Cards*>& cardSpace, Deck& deck);
    void handReceive(Cards*& card);
    void displayHand(std::vector<Cards*>& hand);
    void exchange(Player& player, std::vector<Cards*>& cardSpace, Deck& deck);
};

static std::vector<Cards*> deck;

class Hand {

public:

    Hand();

    std::vector<Cards>* hand;

    Hand(const Hand& hand);

    Hand& operator =(const Hand& hand);

    void addCard(Cards& card);

    friend std::istream& operator>>(std::istream& in, const Hand& hand);
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);

    // Destructor
    ~Hand();

};
