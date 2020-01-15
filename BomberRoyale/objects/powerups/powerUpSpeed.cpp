#include "powerUpSpeed.h"
#include "../../objects/Player.h"


powerUpSpeed::powerUpSpeed(){
    path = "../resources/powerup/speed-icon.png";

    loadSprite(sprite, texture, path, 0, 0);
}


powerUpSpeed::powerUpSpeed(float x, float y, float xspeed, float yspeed) :
        BasePowerUps(x, y, xspeed, yspeed) {

    path = "../resources/powerup/speed-icon.png";

    loadSprite(sprite, texture, path, getX(), getY());

}

powerUpSpeed::~powerUpSpeed() = default;


void powerUpSpeed::Move() {
    BaseObject::Move();
}

void powerUpSpeed::Draw(sf::RenderWindow &window) {
    window.draw(sprite);

}


void powerUpSpeed::modifyPlayer(std::shared_ptr<Player>& player) {

    // If the players sprite intersects the power up
    if (player->getRectangleShape().getGlobalBounds().intersects(sprite.getGlobalBounds())){
        if (player->getSpeed() < capSpeed) {
            //Increase the players speed
            player->setSpeed(player->getSpeed() + addSpeed);
            std::cout << "Speed: " << player->getXspeed() << " " << player->getYspeed() << "\n";
        }
    }

}