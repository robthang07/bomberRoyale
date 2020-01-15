#include <SFML/Graphics.hpp>

#include "sprite.h"
#include "../layers/map.h"
#include "../config.h"
// Process rectShape in regards to clock
void Sprite::process(float deltaTime)
{
    auto& animation = map.getAnimation(gid);

    if (animation.empty())
        return;

    // Go to next animation frame if required
    if (clock.getElapsedTime().asMilliseconds() < animation[frame]->duration)
        return;

    if (++frame >= (int)animation.size())
        frame = 0;

    clock.restart();
}

//Draw Sprite on window
void Sprite::draw(sf::RenderWindow& window, Config& config)
{

    map.setSpriteTextureFromGid(sprite, gid, frame);
    sprite.setPosition((float)x + config.getBoxIndentWidth(), (float)y + config.getBoxIndentHeight());

    window.draw(sprite);
}
