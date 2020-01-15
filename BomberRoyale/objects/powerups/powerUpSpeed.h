#ifndef BOMBER_ROYALE_POWERUPSPEED_H
#define BOMBER_ROYALE_POWERUPSPEED_H

#include "basePowerUps.h"

class powerUpSpeed : public BasePowerUps{
public:

    /**
     * Constructor
     */
    powerUpSpeed();

    /**
     * Constructor with parameters
     * @param x position
     * @param y position
     * @param xspeed
     * @param yspeed
     */
    powerUpSpeed(float x, float y, float xspeed, float yspeed);

    /**
     * Destructor
     */
    ~powerUpSpeed()override;

    /**
     *   Move, Draw is from base Object
     */

    void Move() override;

    void Draw(sf::RenderWindow& window) override;

    /**
   * Modify player when intersected with power ups
   * @param player to modify
   */
    void modifyPlayer(std::shared_ptr<Player>& player) override;

protected:
    int capSpeed = 200;
    int addSpeed = 25;

};


#endif //BOMBER_ROYALE_POWERUPSPEED_H
