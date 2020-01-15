#ifndef BOMBER_ROYALE_PLAYERPOSITIONS_H
#define BOMBER_ROYALE_PLAYERPOSITIONS_H

#include "../../config.h"

class PlayerPositions {
public:

    // Constructor
    PlayerPositions() = default;

    // Destructor
    ~PlayerPositions() = default;

    /**
     * Set player in position x-axis
     * @param playerCount, checks which player you are
     * @param xsize, the size of the player
     * @return position to the player
     *
     *
     * SetplayerY is the same, but for y-axis
     */
    int setPlayerX(int playerCount, int xsize);
    int setPlayerY(int playerCount, int ysize);


protected:
    //positions the player is supposed to be placed on
    Config config;
};


#endif //BOMBER_ROYALE_PLAYERPOSITIONS_H
