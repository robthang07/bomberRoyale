#include "powerUpBombPower.h"
#include "../../objects/Player.h"


PowerUpBombPower::PowerUpBombPower() {
    path =  "../resources/powerup/explosion-icon.png";

    loadSprite(sprite, texture, path, 0,0);
}

PowerUpBombPower::PowerUpBombPower(float x, float y, float xspeed, float yspeed) :
        BasePowerUps(x, y, xspeed, yspeed) {
    path =  "../resources/powerup/explosion-icon.png";

    loadSprite(sprite, texture, path, x, y);
}

PowerUpBombPower::~PowerUpBombPower() = default;

void PowerUpBombPower::Move() {
    BaseObject::Move();
}

void PowerUpBombPower::Draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void PowerUpBombPower::modifyPlayer(std::shared_ptr<Player> &player) {

    player->setBombPower(player->getBombPower() + 1);

}