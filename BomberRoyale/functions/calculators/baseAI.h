#ifndef BOMBER_ROYALE_BASEAI_H
#define BOMBER_ROYALE_BASEAI_H

#include <random>
#include "SFML/Graphics.hpp"

#include "../../objects/Player.h"
#include "../../config.h"
#include "iostream"
#include "playerPositions.h"
#include "SFML/Graphics.hpp"


class BaseAI : public Player {

public:

    //Constructor
    BaseAI();

    //Destructor
    ~BaseAI() override;

    /**
     * Function to move the AI
     * @param deltaTime is for the animation and frames to run smoothly
     */
    void Move(float deltaTime) override;

    /**
     * Simply draw the AI character
     * @param window, which window to draw in
     */
    void Draw(sf::RenderWindow& window) override;

    enum Direction { UP, DOWN, LEFT, RIGHT, NONE };

    // Get the direction it currently is facing
    Direction getDirection() {return direction; };


    /**
     * This decides which direction AI is set to
     * @param direction, choose direction
     */
    void setDirection(Direction direction) { this->direction = direction;}

    /**
     * List over players and AI
     * @param players and AI to store in the list
     */
    void setPlayerList(std::list<std::shared_ptr<Player>>& players){this->playerList = players;};

    /**
     * Find the position to all of the players including its own
     * and calculates the shortest distance to the nearest player
     */
    void findPositions();

protected:


    Direction direction;

    // Timer to set direction for a certain time, so it doesnt change direction constantly
    int timer = 1;

    // List over players
    std::list<std::shared_ptr<Player>> playerList;


    /**
     * Arrays over position of the 4 players
     */

    float xArray[4];
    float yArray[4];

    float xDistArray[4];
    float yDistArray[4];


    // Which index it currently is on in the arrays
    int index = 0;

};


#endif //BOMBER_ROYALE_BASEAI_H
