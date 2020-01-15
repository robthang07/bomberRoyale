#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include "SFML/Graphics.hpp"
#include "layers.h"

namespace Json
{
    class Value;
}


// Class with a single public static function that loads a map into an objects list
class Object;

// Helper struct describing a tileset
struct Tileset
{
    unsigned int firstGid;
    int columns;
    int imageWidth;
    int imageHeight;
    int tileWidth;
    int tileHeight;
    int spacing;

    sf::Texture texture;
};

// Helper struct describing a frame of animation
struct AnimationFrame
{
    AnimationFrame(unsigned int gid, int duration) : gid(gid), duration(duration) {}

    unsigned int gid;
    int duration;
};

// Class containing the information in a Tiled map
class Map
{
public:


    /**
     * Function to load map from Tiled JSON file
     * @param filename is the path to filename
     * @return a bool if true load map
     */
    bool loadFromFile(const std::string& filename);

    /**
     * Function to get width when called upon
     * @return int of width
     */
    int getWidth() const { return width; }

    /**
     * Function to get height when called upon
     * @return int of height
     */
    int getHeight() const { return height; }

    /**
     * Function to get tile width from JSON map
     * @return int TileWidth used in  JSON map
     */
    int getTileWidth() const { return tileWidth; }

    /**
     * Function to get height when called upon
     * @return int TileHeight used in JSON map
     */
    int getTileHeight() const { return tileHeight; }


    /**
     * Call this function after loadFromFile to get a list of objects that you can use to draw etc.
     * @return objects that have been loaded in LoadObjectLayer function
     */
    std::list<std::shared_ptr<Object>>& getObjects() { return objects; }

    /**
     * Call this function after loadFromFile to get a list of objects that you can use to draw etc.
     * @return walls that have been loaded in LoadWallLayer functions as Objects.
     */
    std::list<std::shared_ptr<Object>>& getWalls() { return walls; }

    /**
     * Sets sprite texture and texture coordinates based on global tile id
     * @param get sprite to set texture
     * @param get gid to get texture coordinates based on global tile id
     * @param frame for animation
     */
    void setSpriteTextureFromGid(sf::Sprite& sprite, unsigned int gid, int frame = 0);


    /**
     * Gets animation for a specific global tile id
     * @param gid get global tile id
     * @return a constant vector with animation frame with reference
     */
    const std::vector<std::shared_ptr<AnimationFrame>>& getAnimation(unsigned int gid);

private:

    /**
     * Used in loadFromFile to load information from JSON map
     * @param layer load tile set from map
     */
    void loadTileset(Json::Value& tileset);

    /**
     * Used in loadFromFile to load tile layer from JSON map
     * @param layer load tile layer from map
     */
    void loadTileLayer(Json::Value& layer);

    /**
     * Used in loadFromFile to load object layer from JSON map
     * @param layer load object layer from map
     * @param LoadInToObjects is true if we load in objects, false if we load in walls
     */
    void loadObjectLayer(Json::Value& layer, bool LoadInToObjects);

    //variables of int to store width and height
    int width;
    int height;
    int tileWidth;
    int tileHeight;


    /**
     * 1. List which uses a shared pointer of tileset to store tilesets
     * 2. Map which has key indicator of int and stores vector of shared pointer of Animation frame
     * 3. List of shared pointer storing objects from map, also handles objects layers
     */
    std::list<std::shared_ptr<Tileset>> tilesets;
    std::map<int, std::vector<std::shared_ptr<AnimationFrame>>> animations;
    std::list<std::shared_ptr<Object>> objects;
    std::list<std::shared_ptr<Object>> walls;

};

#endif
