#include <SFML/Graphics.hpp>

#include "layers.h"
#include "map.h"
#include "../config.h"

void Layer::draw(sf::RenderWindow& window, Config& config)
{
    // Render each tile
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned int gid = tilemap[x + y * width];

            // Skip empty tiles
            if (gid == 0)
                continue;

            sf::Sprite sprite;

            // Set source texture and position
            map.setSpriteTextureFromGid(sprite, gid);
            sprite.setPosition((float)(x * map.getTileWidth()) + config.getBoxIndentWidth(), (float)(y * map.getTileHeight()) + config.getBoxIndentHeight());

            window.draw(sprite);
        }
    }
}