#ifndef BOMBER_ROYALE_POWERUPS_H
#define BOMBER_ROYALE_POWERUPS_H

#include "../../objects/BaseObject.h"
#include <iostream>
#include <memory>

class Player;

class BasePowerUps : public BaseObject {

    friend Player;

public:

    /**
     * Constructor which adds sprites of
     * powerups in a list
     */
    BasePowerUps();
    /**
     *Inheritance from baseObject alternative of constructor
     * @param x position
     * @param y position
     * @param xspeed - speed for x-axis
     * @param yspeed - speed for y-axis
     */
    BasePowerUps(float x, float y, float xspeed, float yspeed);

    /**
     * Set the destructor to default
     */
    ~BasePowerUps() override = default;


    /**
     * Virtual function to load sprite so all classes
     * who inherit this class can use this and override
     * with their own code
     * @param sprite to use in the function
     * @param texture to use in the function
     * @param filename to find the path to the file
     * @param x set position for x-axis
     * @param y set position for y-axis
     */
    virtual void loadSprite(sf::Sprite& sprite,
                            sf::Texture& texture,
                            std::string& filename,
                            float x,
                            float y);

    /**
     * Modify the player when
     * intersecting with the HP icon
     * @param player to modify
     */
    virtual void modifyPlayer(std::shared_ptr<Player>& player) = 0;

    sf::Sprite getSprite(){
        return sprite;
    }


protected:


    // Sprite to use later in class to draw rectShape
    sf::Sprite sprite;


    // Texture to use later in classes with sprites
    sf::Texture texture;


    //Path name for the icons
    std::string path;

};


#endif //BOMBER_ROYALE_POWERUPS_H
