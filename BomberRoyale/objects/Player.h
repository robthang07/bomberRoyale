#ifndef BOMBER_ROYALE_PLAYER_H
#define BOMBER_ROYALE_PLAYER_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "../config.h"
#include "../functions/calculators/playerPositions.h"
#include "Bomb.h"
#include "../functions/animation/animation.h"


class Player : public BaseObject {
public:


    /**
     * Default constructor with no parameters that inherits from BaseObject
     * it sets the x, y, xspeed and yspeed variables to 0
     */
     Player();

    /**
     * The player constructor
     * @param config is the settings object that have all the player inputs
     */
    explicit Player(Config &config);

    /**
     * destructor that clears bombs
     */
    virtual ~Player();

    //Override the BaseObjects move function
    /**
     * Move the player
     * @param deltaTime is the deltatime we use to move it based on round trip time.
     */
    virtual void Move(float deltaTime);

    //Overrides the BaseObjects draw function
    /**
     * Draw the player
     * @param window is the render window we draw it on.
     */
    virtual void Draw(sf::RenderWindow &window) override;

    /**
      * Getter for the player number
      * @return a int that return the player nummber
      */
    int getPlayerNumber(){return playerCount; }


    /**
     * It returns the sprite to the player.
     * @return it returns a sf::Sprite of the player.
     */
    sf::RectangleShape& getRectangleShape(){ return rectShape; }


    /**
     * Getter for player(s) size x axes
     * @return the player(s) x size
     */
    int getSizeX(){ return sizeX; }

    /**
     * Getter for player(s) size y axes
     * @return the player(s) y size
     */
    int getSizeY(){ return sizeY; }

    /**
     * Getter to get the speed the different players have
     * @return the speed to the player
     */
    float getSpeed(){ return speed; }

    /**
     * Setter to increase/decrease the player(s) speed at will
     * @param speed is the float vaue of how fast the player(s) is moving
     */
    void setSpeed(float speed){this->speed = speed;}

    /**
     * Getter for the player inputs.
     * @return a vector with the player buttons.
     */
    std::vector<sf::Keyboard::Key> getPlayerInput() { return playerInput;}

    /**
     * Setter that set the player inputs
     * @param playerInputs is a vector with the buttons they have
     */
    void setPlayerInput(std::vector<sf::Keyboard::Key> playerInputs){ this->playerInput = playerInputs;}

    /**
     * Getter for score of player(s)
     * @return the score of player(s) as an int
     */
    long int getScore(){ return score; }

    /**
     * Setter for score of player(s)
     * @param score is the amount of points the player has achiever during the game
     */
    void setScore(long int score) { this->score = score; }

    /**
     * Getter to see how many bombs the player is allowed to have
     * @return the amount of bombs the player can have
     */
    int getMaxBomb(){ return maxBomb;}

    /**
     * Setter to tell the machine how many bombs the player is a allowed to have
     * @param maxBomb is an int that will change the amount of bombs the player is a allowed to have
     */
    void setMaxBomb(int maxBomb){this->maxBomb = maxBomb;}

    /**
     * Getter to get the bomb power, the length of the explosions
     * @return a int with the number of how many elements it is in range each way.
     */
    int getBombPower(){ return bombPower;}

    /**
     * Setter to set the bomb power, the length of the explosions
     * @param a int with the number of how many elements it is in range each way.
     */
    void setBombPower(int bombPower){ this->bombPower = bombPower;}


    /**
     * Getter for the bomb list.
     * @return a std::list<shared_ptr<Bomb>>& with the bombs
     */
    std::list<std::shared_ptr<Bomb>>& getBombs() {return bombs;}

    /**
    * Getter for hp of player(s)
    * @return the hp of the player(s) as an int
    */
    int getHp(){ return hp; }

    /**
     * Setter for hp of player(s)
     * @param hp is the health of the player that is to be set
     */
    void setHp(int hp) { this->hp = hp; }

    /**
     * Get if the player is dead.
     * @return true if the player is dead
     */
    bool getDead(){ return dead; }

    /**
     * Set the player to dead.
     */
    void setDead(){ dead = true;}

    /**
     * Function to assign duration that a player can loose life
     * @param timer : duration in seconds
     */
    void sethitProtectionTimer(float hitProtectiontimer) { this->hitProtectiontimer = hitProtectiontimer; }

    /**
     * Getter to check if the player has been his by bombs recently
     * @return playerHit a boolean that is true if the player has been hit recently
     */
    bool& getPlayerHit(){ return playerHit;}

    /**
    * Function that changes the value of playerHit from false to true if the player if he got hit by a bomb
    * @param deltaTime is used to decide when player can loose life again after beeing hit by a bomb
    */
    void hitExplosives(float &deltaTime);

    bool& getIsPlayer() { return isPlayer; };

    void setIsPlayer(bool isPlayer) { this->isPlayer = isPlayer; };

protected:
    /**
     * Function that loads Sprites
     */
    void loadSprite();
    /**
     * function that takes the inputs of human players and sends it on to the move function
     * @param config is the names we use for keyboard input
     * @param deltaTime a variable that useds the clock on the computer for smoothing/nonlagging
     */
    void moveInput(float deltaTime);

    //integer that chooses which input should be used and the player number -1
    int playerCount;

    //integer that counts up so the players will use different movesets
    static int nextPlayerCount;

    //texture is a Texture from the SFML library
    sf::Texture* texture;

    //The player rectShape
    sf::RectangleShape rectShape;

    //sizeX is the amount of pixels we set the Player to on the x-axis
    int sizeX = 25;
    //sizeY is the amount of pixels we set the Player to on the y-axis
    int sizeY = 25;

    //individual speed for each player, set in constructor which will be increased as player collects powerups
    float speed;

    //A vector with the controls for player
    std::vector<sf::Keyboard::Key> playerInput;

    //score is the points you get from destroying objects, killing players and picking up power-ups
    long int score = 0;

    //Maximum amount of bombs a player can have while in the game
    int maxBomb = 1;

    //Bomb explosion radius
    int bombPower = 1; // The bomb power

    //list over bombs the player have
    std::list<std::shared_ptr<Bomb>> bombs;

    //amount of hits an object can take
    int hp;

    //bool for the player if it is dead or not
    bool dead = false;

    //if the player has been hit by a bomb recently to prevent getting hit several times in a row
    bool playerHit = false;

    //time that the timer gets when reseting / and starting the game;
    float hitProtectiontimeReset = 5;
    //timer to decide when player can lose health again
    float hitProtectiontimer = hitProtectiontimeReset;

    //Animation as a pointer so we dont have to use references
    Animation* animation;

    //Used to decide which row to be in
    unsigned int row;

    //If the player is faced right or not
    bool faceRight;

    //boolean that is true when not AI
    bool isPlayer = true;

};


#endif //BOMBER_ROYALE_PLAYER_H
