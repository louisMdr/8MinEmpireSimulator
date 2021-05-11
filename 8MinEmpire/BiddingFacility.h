#pragma once
#include <vector>
#include <ostream>
#include "Player.h"

// Forward Declaration
class Player;

class BiddingFacility {

private:
    int* bid;

public:
    // Constructor
    BiddingFacility();

    //Copy Constructor
    BiddingFacility(const BiddingFacility& biddingFacility);

    // Deconstructor
    ~BiddingFacility();

    // Gameplay Methods
    static int biddingPhase(std::vector<Player*> players, int numberOfPlayers);

    //Assignment operator
    void operator = (const BiddingFacility& biddingFacility);

    // Accessors
    int getBid() const;

    // Mutators
    void setBid(int bid);

    //Overriding stream insertion operators
    friend std::ostream& operator<<(std::ostream& os, const BiddingFacility& dt);
};

