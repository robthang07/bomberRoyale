#ifndef BOMBER_ROYALE_BOMB_H
#define BOMBER_ROYALE_BOMB_H


#include <SFML/System/Clock.hpp>
#include <TGUI/Gui.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <SFML/Audio.hpp>
#include "BaseObject.h"
#include "object.h"
#include "powerups/basePowerUps.h"

struct Explosion{
    enum way {LEFT, DOWN, RIGHT, UP};
    int numberOfways = 4;

    bool remove = false;
    bool activated = false;
    float timeActivated = 0;
    sf::Sprite Middle;
    std::vector<sf::Sprite> Left;
    std::vector<sf::Sprite> Right;
    std::vector<sf::Sprite> Down;
    std::vector<sf::Sprite> Up;
};


class Player;

class Bomb :  public BaseObject  {
public:
    /**
     * Default constructor
     */
    Bomb();

    /**
     * Constructor that takes in parameters
     * @param x : position to the bomb
     * @param y : position to the bomb
     * @param xspeed : movement speed to the bomb
     * @param yspeed : movement speed to the bomb
     */
    Bomb(float x, float y, float xspeed, float yspeed);

    /**
     * Override the draw function inherited from BaseObject to draw a bomb
     * Set position for the sprite, and draw it on the window
     * @param window is the game window where the bomb will be drawn
     */
    void Draw(sf::RenderWindow &window) override;

    /**
     * Override the move function to move a bomb
     * If the bomb is going to move make it here
     */
    void Move() override;

    /**
     * Function to load a small bomb picture to the game
     */
    void loadSprite();

    /**
     * Check if the bomb is exploded.
     * If exploded, set up the explosion struct as it should.
     * If it is exploded and the struct is setup then change the time it have still and set it to remove if it is done.
     * But if the bomb is just set down and not exploded it do just set it closer to exploding.
     * @param window is the render window we are drawing on.
     * @param delta is the deltatime we are using to get a smooth loop timer.
     * @param objects is the list over objects on the map
     * @param walls is the list over walls on the map
     * @param player is the player we want to check.
     * @param powerups is a list over powerups in the game.
     */
    void checkForExplosion(sf::RenderWindow& window, float& delta, std::list<std::shared_ptr<Object>>& objects, std::list<std::shared_ptr<Object>>& walls,
            Player& player, Player& diffplayer, std::list<std::shared_ptr<BasePowerUps>>& powerups, Config& config);

    /**
     * Check if the bomb is flaged for remove
     * @return a bool for removing. True = ready for removing.
     */
    bool checkFlagedForRemoving(){ return explosion.remove; };

    /**
     * Spawn the powerups on the map.
     * @param object is the object where we want to place it.
     * @param powerups is the list over powerups in the game. We want to add them to it.
     */
    void spawnPowerUp(std::shared_ptr<Object>& object, std::list<std::shared_ptr<BasePowerUps>>& powerups);

    /**
     * Function to assign duration that a bomb takes to explodes
     * @param timer : duration in seconds
     */
    void setTimer(float timer) { this->timer = timer; }

    // #########3 Functions related to sound effects ########
    /**
     * Function to load sound effect to RAM from Disk
     */
    void loadSoundEffects();



protected:
    int sizeX = 32; //Bomb sizeX
    int sizeY = 32; //Bomb sizeY
    float timer = 5; //Assignment: amount of time a bomb takes to explodes

    //Bomb rectShape data
    sf::Sprite bombSprite; //Base object for bomb
    sf::Texture texture; //Data container to store and manipulate bomb png

    //Explosion data
    Explosion explosion; // A explosion struct element
    float baseTimeForExplosion = 0.5; //Base time for activated explosion

    //Explosions sprites
    sf::Sprite explosionSpriteMiddel; //Base object for explosion
    sf::Texture explosionTextureMiddel; //Data container for explotion png

    sf::Sprite explosionSpriteSideHorisontally; //Base object for explosion
    sf::Texture explosionTextureSide; //Data container for explotion png

    sf::Sprite explosionSpriteEndRigth; //Base object for explosion
    sf::Texture explosionTextureEnd; //Data container for explotion png

    //Next block of data containers for rotation manipulation
    sf::Sprite explosionSpriteSideVertical;

    sf::Sprite explosionSpriteEndLeft;
    sf::Sprite explosionSpriteEndUp;
    sf::Sprite explosionSpriteEndDown;

    //Make a random generator for the spawning of powerups
    long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> spawnChances{1,2};
    std::uniform_int_distribution<int> different{1,4};

    //############ Sound ##############

    //Explosion sound effect
    sf::SoundBuffer explosionSoundBuffer;
    sf::Sound explosionSound;
    bool explosionSoundPlayed = false;
};


#endif //BOMBER_ROYALE_BOMB_H
