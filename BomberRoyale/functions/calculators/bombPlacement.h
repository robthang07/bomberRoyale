#ifndef BOMBER_ROYALE_BOMBPLACEMENT_H
#define BOMBER_ROYALE_BOMBPLACEMENT_H

#include "../../objects/Player.h"
#include "../../objects/Bomb.h"
#include "../../config.h"
#include <list>
#include <iostream>

class bombPlacement{
public:
    /**
     * This function places the bomb in the given modulus
     * @param player is used to get the players position
     * @param bombs is used to add bombs
     * @param config is the settings object that we are getting information from.
     */
     static void Bombplacement(std::shared_ptr<Player>& player,
            std::list<std::shared_ptr<Bomb>>& bombs, Config config);

     static sf::Vector2f CheckBombPlacment(std::shared_ptr<Player>& player, Config config);

};

#endif //BOMBER_ROYALE_BOMBPLACEMENT_H
