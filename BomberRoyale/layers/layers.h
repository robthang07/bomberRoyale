#ifndef LAYER_H
#define LAYER_H

#include <string>

#include "../objects/object.h"

// Class representing a tile layer which inherits from class Object
class Layer : public Object
{
    // Map needs to access protected/private data
    friend class Map;

public:

    /**
     * Constructor to class Layer
     * @param map from class Object used to store layers, same as sprite class
     */
    explicit Layer(Map& map) : Object(map) { }

    /**
     * Deconstructor which deletes the pointer used on tilemap variable
     */
    ~Layer() override { delete[] tilemap; }


    /**
     * draw function to draw and render each tile and override the inherited Object class which also uses the draw function
     * @param window to get which window to draw/render in
     * @param config is from the inherited class Object
     */
    void draw(sf::RenderWindow& window, Config& config) override;

protected:

    /**
     * Variables used / needed
     */
    std::string name;
    int id = 0;
    int width = 0;
    int height = 0;
    bool visible = false;
    unsigned int* tilemap = nullptr;
};

#endif
