#ifndef BOMBER_ROYALE_POWERUPHP_H
#define BOMBER_ROYALE_POWERUPHP_H

#include "basePowerUps.h"

class powerUpHP : public BasePowerUps{
public:

    /**
     * Constructor
     */
    powerUpHP();

    /**
     * Constructor with parameters
     * @param x position
     * @param y position
     * @param xspeed
     * @param yspeed
     */
    powerUpHP(float x, float y, float xspeed, float yspeed);

    /**
     * Destructor
     */
    ~powerUpHP();

    /**
     * Move, Draw is from base Object
     */
    void Move() override;

    void Draw(sf::RenderWindow& window) override;

    /**
     * Modify player when intersected with power ups
     * @param player to modify
     */
    void modifyPlayer(std::shared_ptr<Player>& player) override;
};


#endif //BOMBER_ROYALE_POWERUPHP_H
