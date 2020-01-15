#include "powerUpHP.h"
#include "../../objects/Player.h"

powerUpHP::powerUpHP(){
    //loadSprite(healthSprite, healthTexture, pathHP, getX(),getY());
    path = "../resources/powerup/health-icon.png";


    loadSprite(sprite, texture, path, 0,0);
}


powerUpHP::powerUpHP(float x, float y, float xspeed, float yspeed) :
BasePowerUps(x, y, xspeed, yspeed){
    path = "../resources/powerup/health-icon.png";

    loadSprite(sprite, texture, path, getX(),getY());
}

powerUpHP::~powerUpHP() = default;


void powerUpHP::Move() {
    BaseObject::Move();
}


void powerUpHP::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
}


void powerUpHP::modifyPlayer(std::shared_ptr<Player>& player) {

    if (player->getRectangleShape().getGlobalBounds().intersects(sprite.getGlobalBounds())){
        player->setHp(player->getHp() + 1);
        std::cout << "Health point + 1\n";
    }

}