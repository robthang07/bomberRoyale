#include "bombPU.h"
#include "../../objects/Player.h"


bombPU::bombPU(){
    path =  "../resources/powerup/bomb-icon.png";

    loadSprite(sprite, texture, path, 0,0);
}


bombPU::bombPU(float x, float y, float xspeed, float yspeed) :
        BasePowerUps(x, y, xspeed, yspeed){
    path = "../resources/powerup/bomb-icon.png";

    loadSprite(sprite, texture, path, getX(),getY());
}

bombPU::~bombPU() = default;

void bombPU::Move() {
    BaseObject::Move();
}

void bombPU::Draw(sf::RenderWindow &window) {
window.draw(sprite);
}


void bombPU::modifyPlayer(std::shared_ptr<Player>& player) {

    if (player->getRectangleShape().getGlobalBounds().intersects(
            sprite.getGlobalBounds())){

        player->setMaxBomb(player->getMaxBomb() + 1);
        std::cout << "Bomb count: " << player->getMaxBomb() << "\n";

    }

}