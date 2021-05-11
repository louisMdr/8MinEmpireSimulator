#include "BiddingFacility.h"

#include <iostream>
#include <algorithm>


// Constructor

BiddingFacility::BiddingFacility() {
    BiddingFacility::bid = new int(0);
}

//Copy Constructor
BiddingFacility::BiddingFacility(const BiddingFacility& biddingFacility) {
    BiddingFacility::bid = new int(*biddingFacility.bid);
}

// Destructor

BiddingFacility::~BiddingFacility() {
    if (bid) {
        delete bid;
        bid = NULL;
    }
}

// Returns the index of the player who goes first, to determine player order
int BiddingFacility::biddingPhase(std::vector<Player*> players, int numberOfPlayers) {

    // Local Variables
    int bid, highestBid, highestBidder;

    // Each player gets a chance to enter a bid
    for (int i = 0; i < numberOfPlayers; i++) {
        std::cout << "How much would you like to bid " << players[i]->getName() << "?" << std::endl;
        std::cin >> bid;
        while (bid < 0 || bid > players[i]->getCoins()) {
            std::cout << "Invalid Bid! Please enter a number between 0 and " << players[i]->getCoins() << ": ";
            std::cin >> bid;
        }
        players[i]->getBiddingFacility()->setBid(bid);
    }

    // Assume player 1 (index 0) has the highest bid
    highestBidder = 0;
    highestBid = players[0]->getBiddingFacility()->getBid();

    // Bids are compared and index of the highest bidder is going to be returned
    for (int i = 0; i < numberOfPlayers - 1; i++) {
        if (highestBid < players[i + 1]->getBiddingFacility()->getBid()) {
            highestBidder = i + 1;
            highestBid = players[i + 1]->getBiddingFacility()->getBid();
        }

        /*If the bids are tied for most, the player with the alphabetical
         * last name order wins the bid (e.g., Ng will  go first vs. Noah) and pays his coins.*/
        if (highestBid == players[i + 1]->getBiddingFacility()->getBid()
            && players[highestBidder]->getName() > players[i + 1]->getName()) {

            std::vector<std::string>lnames = { "Smith","Doe","Anderson" };
            sort(lnames.begin(), lnames.end());
            // so lnames[0] will return the first last name in the alphabetical order

            highestBidder = i + 1;
        }
    }

    // Highest bidder pays the cost

    players[highestBidder]->PayCoin(players[highestBidder]->getBiddingFacility()->getBid());

    return highestBidder;
}

//Assignment Operator

void BiddingFacility::operator = (const BiddingFacility& biddingFacility) {
    bid = biddingFacility.bid;
}

//Stream Operator

std::ostream& operator<<(std::ostream& os, const BiddingFacility& biddingFacility) {
    os << "Bid: " << biddingFacility.getBid();
    return os;
}

// Accessor

int BiddingFacility::getBid() const {
    return *bid;
}

// Mutator

void BiddingFacility::setBid(int bid) {
    *BiddingFacility::bid = bid;
}
