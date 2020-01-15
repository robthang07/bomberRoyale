#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/System/Clock.hpp>
#include "object.h"

class Sprite : public Object
{
    // Map needs to access protected/private data
    friend class Map;

public:

    /**
     * Constructor to class Sprite which inherits from class Object
     * @param map from class Object used to store layers, same as layer class
     */
    explicit Sprite(Map& map) : Object(map) {}

    /**
     * Function process from class Object animation with regards to deltaTime
     * @param time is a clock used in several classes to smooth / time the animation with regards to clock used in delta time
     */
    void process(float time) override;


    /**
     * draw function to draw and render each sprite and override the inherited Object class
     * @param window to get which window to draw/render in
     * @param config is not used but is from the inherited class Object
     */
    void draw(sf::RenderWindow& window, Config& config) override;


    /**
     * Getter function to get a sprite
     * @return sprite created in this class
     */
    sf::Sprite getSprite(){
        return sprite;
    }

protected:

    // Id of first tile
    unsigned int gid = 0;


    // Object id
    int id = 0;


    // Location on screen
    int x = 0;
    int y = 0;

    // Dimensions
    int width = 0;
    int height = 0;

    // Current animation frame
    int frame = 0;

    // Times the animation
    sf::Clock clock;

    sf::Sprite sprite;

};

#endif
