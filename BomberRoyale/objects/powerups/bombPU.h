#ifndef BOMBER_ROYALE_BOMBPU_H
#define BOMBER_ROYALE_BOMBPU_H


#include "basePowerUps.h"

class bombPU : public BasePowerUps {
public:

    /**
     * Create a constructor
     */
    bombPU();

    /**
     * Constructor with parameters
     * @param x position
     * @param y position
     * @param xspeed
     * @param yspeed
     */
    bombPU(float x, float y, float xspeed, float yspeed);

    /**
     * set the Destructor
     */
    ~bombPU() override;

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
    int capMaxBombs; //Not used at the moment
};


#endif //BOMBER_ROYALE_BOMBPU_H
