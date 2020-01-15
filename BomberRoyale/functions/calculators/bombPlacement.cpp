#include "../../functions/calculators/bombPlacement.h"


void bombPlacement::Bombplacement(std::shared_ptr<Player>& player,std::list<std::shared_ptr<Bomb>>& bombs, Config config ) {

    /*
     * various integers used to calculate where the bomb is supposed to be placed
     * offsets are for how much the actual game screen is decentralized from the borders
     * mods are what you have left from what tile your player is in
     * tiles are what tiles you are in
     * positions are the true positions you use to place the bomb
     */
    int offsetX = config.getBoxIndentWidth();
    int modX = (int) (player->getX() - offsetX) % 32;
    int tileX = (player->getX() - offsetX - modX) / 32;
    int positionX;

    int offsetY = config.getBoxIndentHeight();
    int modY = (int) (player->getY() - offsetY) % 32;
    int tileY = (player->getY() - offsetY - modY) / 32;
    int positionY;

    //checks the moduli to see where the bombs are to be placed relative to the player
    //if the player is far enough into one tile it will be placed there rather than the value you get
    if (modX > 15) {
        positionX = (tileX + 1) * 32 + offsetX;
    } else {
        positionX = tileX * 32 + offsetX;
    }

    if (modY > 15) {
        positionY = (tileY + 1) * 32 + offsetY;
    } else {
        positionY = tileY * 32 + offsetY;

    }

    //Adds a bomb to the bomb list
    bombs.push_back(std::make_shared<Bomb>(positionX, positionY, 0, 0));
}

sf::Vector2f bombPlacement::CheckBombPlacment(std::shared_ptr<Player> &player, Config config) {
    /*
    * various integers used to calculate where the bomb is supposed to be placed
    * offsets are for how much the actual game screen is decentralized from the borders
     * mods are what you have left from what tile your player is in
     * tiles are what tiles you are in
     * positions are the true positions you use to place the bomb
    */
    int offsetX = config.getBoxIndentWidth();
    int modX = (int) (player->getX() - offsetX) % 32;
    int tileX = (player->getX() - offsetX - modX) / 32;
    int positionX;

    int offsetY = config.getBoxIndentHeight();
    int modY = (int) (player->getY() - offsetY) % 32;
    int tileY = (player->getY() - offsetY - modY) / 32;
    int positionY;

    //checks the moduli to see where the bombs are to be placed relative to the player
    //if the player is far enough into one tile it will be placed there rather than the value you get
    if (modX > 15) {
        positionX = (tileX + 1) * 32 + offsetX;
    } else {
        positionX = tileX * 32 + offsetX;
    }

    if (modY > 15) {
        positionY = (tileY + 1) * 32 + offsetY;
    } else {
        positionY = tileY * 32 + offsetY;

    }

    return sf::Vector2f(positionX,positionY);
}