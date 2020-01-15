#ifndef BOMBER_ROYALE_POWERUPBOMBPOWER_H
#define BOMBER_ROYALE_POWERUPBOMBPOWER_H

#include "basePowerUps.h"

class PowerUpBombPower : public BasePowerUps {
public:

    /**
     * Create a constructor
     */
    PowerUpBombPower();

    /**
     * Constructor with parameters
     * @param x position
     * @param y position
     * @param xspeed
     * @param yspeed
     */
    PowerUpBombPower(float x, float y, float xspeed, float yspeed);

    /**
     * set the Destructor
     */
    ~PowerUpBombPower() override;

    /**
     * Move function inherited from basePowerUps
     * which inherits from baseObjects
     */
    void Move() override;

    /**
     * Draw function inherited from basePowerUps
     * which inherits from baseObjects
     * @param window
     */
    void Draw(sf::RenderWindow& window) override;

    /**
    * Function to modify player inherited from base Power Ups
    * @param player
    */
    void modifyPlayer(std::shared_ptr<Player>& player) override;

protected:
    int capBombPower; // Not used at the moment
};


#endif //BOMBER_ROYALE_POWERUPBOMBPOWER_H
