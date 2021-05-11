#include "Cards.h"
#include <ctime>
#include <algorithm>
#include <vector> 


Cards::Cards() {

    this->numOfGood = nullptr;
    this->good = nullptr;
    this->action = nullptr;
    this->attribute = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Cards& cards) {

    return os << *cards.getGood() << " (" << *cards.getNumOfGood() << ") - " << *cards.getAction();

}

std::istream& operator>>(std::istream& is, Cards& cards) {

    return is >> *cards.getGood() >> *cards.getNumOfGood() >> *cards.getAction();

}

Cards::~Cards() {

    if (good) {

        delete good;
        good = nullptr;

    }
    if (action) {

        delete action;
        action = nullptr;

    }
    if (numOfGood) {

        delete numOfGood;
        numOfGood = nullptr;

    }
    if (attribute)
    {
        delete attribute;
        attribute = NULL;
    }
}

std::string* Cards::getGood() const {

    return good;

}

void Cards::setGood(std::string good) {

    Cards::good = new std::string(good);

}

std::string* Cards::getAction() const {

    return this->action;

}

void Cards::setAction(std::string action) {

    Cards::action = new std::string(action);

}

std::string* Cards::getAttribute() const {

    return this->attribute;

}

void Cards::setAttribute(std::string attribute) {

    Cards::attribute = new std::string(attribute);

}

Cards::Cards(int numOfGood, std::string attribute, std::string good, std::string action) {
    this->numOfGood = new int(numOfGood);
    this->good = new std::string(good);
    this->action = new std::string(action);
    this->attribute = new std::string(attribute);
}

Cards::Cards(const Cards& card) {

    this->numOfGood = new int(*(card.numOfGood));
    this->attribute = new std::string(*card.attribute);
    this->good = new std::string(*(card.good));
    this->action = new std::string(*(card.action));


}

Cards& Cards::operator=(const Cards& card) {

    this->numOfGood = new int(*(card.numOfGood));
    this->attribute = new std::string(*card.attribute);
    this->good = new std::string(*(card.good));
    this->action = new std::string(*(card.action));

    return *this;
}

int* Cards::getNumOfGood() const {

    return this->numOfGood;

}

void Cards::setNumOfGood(int numOfGood) {

    Cards::numOfGood = new int(numOfGood);

}

//2 player game cards
Cards* cards01 = new Cards(1, "Ancient", "Flying", "MOVE_ARMIES 5");                            // ancient pheonix
Cards* cards02 = new Cards(1, "Ancient", "VP_Ancient", "MOVE_ARMIES 3");                        // ancient sage         //Victory point for each ancient card
Cards* cards03 = new Cards(3, "Ancient", "Elixer", "PLACE_ARMIES 4");                           // ancient tree spirit
Cards* cards04 = new Cards(1, "Ancient", "Army", "BUILD_CITIES 1 + PLACE_ARMIES 1");            // ancient woods
Cards* cards05 = new Cards(2, "Cursed", "Elixer", "MOVE_ARMIES 6");                             // cursed banshee
Cards* cards06 = new Cards(1, "Cursed", "Flying", "MOVE_ARMIES 5");                             // cursed gargoyles
Cards* cards07 = new Cards(1, "Cursed", "Elixer", "PLACE_ARMIES 3 / MOVE_ARMIES 4 ");           // cursed king
Cards* cards08 = new Cards(1, "Cursed", "Move", "BUILD_CITIES 1");                              // cursed mausoleum
Cards* cards09 = new Cards(1, "Cursed", "VP_Flying", "BUILD_CITIES 1");                         // cursed tower         //Victory point for each flying card
Cards* cards10 = new Cards(1, "Dire", "Flying", "PLACE_ARMIES 3 + DESTROY_ARMIES 1");           // dire dragon
Cards* cards11 = new Cards(1, "Dire", "Flying", "PLACE_ARMIES 4");                              // dire eye
Cards* cards12 = new Cards(1, "Dire", "Immune", "PLACE_ARMIES 3 + DESTROY_ARMIES 1");           // dire giant
Cards* cards13 = new Cards(1, "Dire", "Elixer", "MOVE_ARMIES 5");                               // dire goblin
Cards* cards14 = new Cards(1, "Dire", "VP_Coins", "MOVE_ARMIES 2");                             // dire ogre            //Victory point for each 3 coins you own
Cards* cards15 = new Cards(1, "Forest", "Army", "PLACE_ARMIES 3 / MOVE_ARMIES 2");              // forest elf
Cards* cards16 = new Cards(3, "Forest", "Elixer", "MOVE_ARMIES 2");                             // forest gnome
Cards* cards17 = new Cards(1, "Forest", "Army", "MOVE_ARMIES 4");                               // forest pixie
Cards* cards18 = new Cards(1, "Forest", "Move", "BUILD_CITIES 1");                              // forest treetown
Cards* cards19 = new Cards(1, "NULL", "VP_Cursed", "PLACE_ARMIES 2");                           // graveyard            //victory point per cursed card
Cards* cards20 = new Cards(1, "NULL", "VP_Forest", "PLACE_ARMIES 2 / MOVE_ARMIES 3");           // lake                 //victory point per forest card
Cards* cards21 = new Cards(1, "Night", "Army", "MOVE_ARMIES 5 / DESTROY_ARMIES 1");             // night hydra
Cards* cards22 = new Cards(1, "Night", "Army", "BUILD_CITIES 1");                               // night village
Cards* cards23 = new Cards(1, "Night", "VP_Night", "PLACE_ARMIES 3 + DESTROY_ARMIES 1");        // night wizard         //victory point per night card
Cards* cards24 = new Cards(4, "Noble", "VP_Noble", "PLACE_ARMIES 3");                           // noble hills          //Victory Point if own 3 noble cards
Cards* cards25 = new Cards(1, "Noble", "Move", "PLACE_ARMIES 4 + DESTROY_ARMIES 1");            // noble night
Cards* cards26 = new Cards(1, "Noble", "Move", "MOVE_ARMIES 4 + PLACE_ARMIES 1");               // noble unicorn
Cards* cards27 = new Cards(1, "NULL", "VP_Dire", "BUILD_CITIES 1");                             // stronghold           //Victory point per Dire card

//3 player game cards
Cards* cards28 = new Cards(1, "Arcane", "Move", "PLACE_ARMIES 4 + DESTROY_ARMIES 1");           // arcane manticore
Cards* cards29 = new Cards(1, "Arcane", "Flying", "PLACE_ARMIES 3 / MOVE_ARMIES 4");            // arcane sphinx
Cards* cards30 = new Cards(1, "Arcane", "VP_Arcane", "MOVE_ARMIES 3");                          // arcane temple        //Victory point per arcane card
Cards* cards31 = new Cards(3, "Mountain", "VP_Mountain", "PLACE_ARMIES 2 + DESTROY_ARMIES 1");  // mountain dwarf       //Victory point for 2 mountain cards
Cards* cards32 = new Cards(1, "Mountain", "2Coin + Elixer", "MOVE_ARMIES 3");                   // mountain treasury

//4 player game cards
Cards* cards33 = new Cards(1, "NULL", "Elixer", "PLACE_ARMIES 3 / BUILD_CITIES 1");             // castle 
Cards* cards34 = new Cards(1, "NULL", "Elixer", "MOVE_ARMIES 3 + BUILD_CITIES 1");              // castle two


void Cards::performeAction(Player* player) {
    std::string temp = *action;

    if (temp.find('+') != std::string::npos) {

        std::string::size_type pos = temp.find('+');

        std::string first = temp.substr(0, pos - 1);
        std::string second = temp.substr(pos + 2);

        std::string::size_type pos2_1 = first.find(' ');
        std::string::size_type pos2_2 = second.find(' ');

        std::string firstValue = first.substr(pos2_1 + 1);
        std::string secondValue = second.substr(pos2_2 + 1);

        int val1 = stoi(firstValue);
        int val2 = stoi(secondValue);

        player->andOr("+", first, second, val1, val2);
    }
    else if (temp.find('/') != std::string::npos) {

        std::string::size_type pos = temp.find('/');

        std::string first = temp.substr(0, pos - 1);
        std::string second = temp.substr(pos + 2);

        std::string::size_type pos2_1 = first.find(' ');
        std::string::size_type pos2_2 = second.find(' ');

        std::string firstValue = first.substr(pos2_1 + 1);
        std::string secondValue = second.substr(pos2_2 + 1);

        int val1 = stoi(firstValue);
        int val2 = stoi(secondValue);

        player->andOr("/", first, second, val1, val2);

    }
    else {
        std::string action = temp;
        std::string::size_type pos = temp.find(' ');
        std::string value = temp.substr(pos + 1); 
        int val1 = stoi(value);

        if (action.find("PLACE") != std::string::npos) {

        }
        else if (action.find("MOVE") != std::string::npos) {

        }
        else if (action.find("BUILD") != std::string::npos) {

        }
        else if (action.find("DESTROY") != std::string::npos) {

        }
    }
}


//This should not be called during the game
Deck::Deck()
{
    std::cout << "This is a default constructor" << std::endl;
}

Deck::Deck(int numPlayers) {

    position = new int();

    if (numPlayers >= 2)
    {
        deck.push_back(cards01);
        deck.push_back(cards02);
        deck.push_back(cards03);
        deck.push_back(cards04);
        deck.push_back(cards05);
        deck.push_back(cards06);
        deck.push_back(cards07);
        deck.push_back(cards08);
        deck.push_back(cards09);
        deck.push_back(cards10);
        deck.push_back(cards11);
        deck.push_back(cards12);
        deck.push_back(cards13);
        deck.push_back(cards14);
        deck.push_back(cards15);
        deck.push_back(cards16);
        deck.push_back(cards17);
        deck.push_back(cards18);
        deck.push_back(cards19);
        deck.push_back(cards20);
        deck.push_back(cards21);
        deck.push_back(cards22);
        deck.push_back(cards23);
        deck.push_back(cards24);
        deck.push_back(cards25);
        deck.push_back(cards26);
        deck.push_back(cards27);
    }
    
    if (numPlayers >= 3)
    {
        deck.push_back(cards28);
        deck.push_back(cards29);
        deck.push_back(cards30);
        deck.push_back(cards31);
        deck.push_back(cards32);
    }
 
    if (numPlayers == 4)
    {
        deck.push_back(cards33);
        deck.push_back(cards34);
    }

}

Deck::~Deck() {

    if (cost) {
        delete cost;
        cost = nullptr;
    }

    if (position) {
        delete position;
        position = nullptr;
    }
}

//THIS IS WHERE THE ERROR IS
//I fixed it, DO NOT REMOVE THESE CHANGES
Cards* Deck::draw() {

    Cards* card = NULL;

    random_shuffle(deck.begin(), deck.end());

    if (deck.size() > 0)
    {
        card = deck.back();
        deck.pop_back();
    }
    
    std::cout << "Size of Deck: " << deck.size() << std::endl;

    return card;

}

//generates the 6 cards that are bought
std::vector<Cards*> Deck::cardSpaceGenetor(Deck& deck) {

    auto tb = new std::vector<Cards*>();

    for (int i = 0; i < 6; i++) {

        tb->emplace_back(deck.draw());

    }

    return *tb;

}

//Shows the cards
void Deck::displayCardSpace(std::vector<Cards*>& cardSpace) {

    int j = 0;
    int i = 0;

    std::cout << "\nCard Space:" << std::endl;

    for (auto it = cardSpace.begin(); it != cardSpace.end(); ++it)
    {
        std::cout << ++j << ") " << posArray[i++] << " Coins - " << **it << std::endl;
    }
}


void Deck::updateCardSpace(int& position, std::vector<Cards*>& cardSpace, Deck& deck) {

    int index = position - 1;

    cardSpace.erase(cardSpace.begin() + index);

    Cards* tempCard = deck.draw();

    if (!(tempCard == NULL))//DO NOT REMOVE THIS
    {
        cardSpace.emplace_back(tempCard);
    }
    else
    {
        std::cout << "THE DECK IS EMPTY" << std::endl;
    }

}

Hand::Hand() {

    this->hand = new std::vector<Cards>();
}

Hand::Hand(const Hand& Hand) {

    std::vector<Cards>* cards = new std::vector<Cards>(Hand.hand->begin(), Hand.hand->end());

    this->hand = cards;
}

Hand& Hand::operator=(const Hand& Hand) {

    std::vector<Cards>* cards = new std::vector<Cards>(Hand.hand->begin(), Hand.hand->end());

    delete this->hand;

    this->hand = cards;

    return *this;
}

std::istream& operator>>(std::istream& in, const Hand& Hand) {

    Cards card;

    in >> card;

    Hand.hand->push_back(card);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Hand& Hand)
{
    // Creating an iterator
    std::vector<Cards>::iterator iterator;

    // Iterating through the hand
    for (iterator = Hand.hand->begin(); iterator != Hand.hand->end(); ++iterator) {
        // Output the card to the stream, using its textual type.
        out << *iterator << " ";
    }

    // Returning the stream.
    return out;
}



Hand::~Hand() {

    delete this->hand;
    this->hand = nullptr;

}

// std::string* Hand::getHand() const {

//     return hand;

// }

void Hand::addCard(Cards& card) {

    this->hand->push_back(card);

}


void Deck::exchange(Player& player, std::vector<Cards*>& cardSpace, Deck& deck) {

    bool successfullPurchase = false;

    int cost, position, index;

    displayCardSpace(cardSpace);

    std::cout << player.getName() << ", you have " << player.getCoins() << " coins remaining in your stash." << std::endl;

    std::cout << "Which card do you want to buy? Please enter an integer from 1 to 6: " << std::endl;

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

    } while (!successfullPurchase); 


    index = position - 1;

    player.getHand()->emplace_back(cardSpace.at(index));

    std::cout << player.getName() << " added the following card to their hand: " << *player.getHand()->back() << std::endl;

    updateCardSpace(position, cardSpace, deck);

}
