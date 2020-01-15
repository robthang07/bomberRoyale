#include <SFML/Graphics.hpp>
#include "object.h"



//Destructor
Object::~Object()
{
    delete texture;
    texture = nullptr;
}

//Gets tile Coordination to use when loading tiles
void Object::getTileCoords(int tile, int& x, int& y)
{
    // Tileid 0 means no tile, so the ids actually start from 1
    tile--;

    int tileXcount = texture->getSize().x / (tileSize.x + tileSize.s);

    x = (tile % tileXcount) * (tileSize.x + tileSize.s);
    y = (tile / tileXcount) * (tileSize.x + tileSize.s);
}

