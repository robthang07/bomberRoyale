#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "../config.h"


namespace sf
{
    class RenderWindow;
    class Texture;
}

class Map;

// Base class representing any game object, including tile layers and sprites
class Object
{
public:

    /**
     * Constructor for this class
     * @param map
     */
    explicit Object(Map& map) : map(map) {
    }

    /**
     * Virtual means classes can inherit this class
     * and use the functions but can edit and
     * write more codes in the functions they use
     */



    /**
     * destructor set to default so classes
     * who inherits this class can define their
     * own destructor as necessary
     *
     */
    virtual ~Object() = default;


    /**
     * virtual process function to clock animation and smooth frame
     * @param deltaTime
     */
    virtual void process(float deltaTime) {}

    /**
     * draw function to render and draw whatever is necessary
     * just need to write the code in the function
     * @param window to draw in
     * @param config is settings which is necessary for the other states
     */
    virtual void draw(sf::RenderWindow& window, Config& config) = 0;


protected:
    // Reference to map class so objects can use the map to set textures for drawing
    Map& map;


};

#endif
