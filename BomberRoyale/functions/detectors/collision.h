#ifndef BOMBER_ROYALE_COLLISION_H
#define BOMBER_ROYALE_COLLISION_H

#include "../../config.h"
#include "../../objects/Player.h"
#include "../../objects/sprite.h"


class collision {
public:

    /**
     * Function to detect if the player and sprite objects are colliding
     * @param player is whichever playable character or AI who needs detection
     * @param sprite is the walls, bombs or explodable objects we need to check collision with
     * @param config is the parameter who in this case checks the indentation of the playable screen
     */
    void Detection(std::shared_ptr<Player>& player, std::shared_ptr<Sprite>& sprite, Config& config);

};


#endif //BOMBER_ROYALE_COLLISION_H
