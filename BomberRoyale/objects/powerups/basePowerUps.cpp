#include "basePowerUps.h"

BasePowerUps::BasePowerUps() : BaseObject() {

}

BasePowerUps::BasePowerUps(float x, float y, float xspeed, float yspeed) :
BaseObject(x,y,xspeed,yspeed) {

}

void BasePowerUps::loadSprite(sf::Sprite &sprite, sf::Texture &texture,
        std::string &filename, float x, float y) {

    //load texture from file and set it on the rectShape
    if (!texture.loadFromFile(filename)){
        std::cout << "Failed to load bomb icon!";
    }

    sprite.setTexture(texture);

    //Scale the bombSprite so it can fit to the player rectShape
    sf::Vector2u cSize = texture.getSize();
    sprite.scale((float) 30 / cSize.x , (float) 30 / cSize.y);

    sprite.setPosition(x, y);
}


