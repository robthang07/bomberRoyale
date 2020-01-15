#ifndef GAMESTATESBACKEND_STATE_H
#define GAMESTATESBACKEND_STATE_H

#include <SFML/Graphics.hpp>

#include "../config.h"
#include "../objects/object.h"
#include "gamestatesdata/stateData.h"

class Machine;

class State{
public:

    /**
     * Constructor - do not do anything
     */
    State() = default;
    /**
     * Destructor - do not do anything
     */
    virtual ~State() = default;

    /**
     * It runs the states. Pure virtual so it is only running in the sub classes.
     * @param machine is the state machine that is controlling the states.
     * @param window is the render window we are showing the game in.
     * @param config is the settings object that we are getting information from.
     * @param deltaTime is a variable with the time when the loop started, and is used to smooth out the animation if the loop use longer time to get done.
     * @return It returns a int based on witch error code it is giving.
     */
    virtual int run(Machine& machine, sf::RenderWindow& window, Config& config, float deltaTime) = 0;

    /**
     * Get the state data -  Pure virtual so it is only running in the sub classes.
     * @return the state data object
     */
    virtual StateData* getStateData() = 0;

};

#endif //GAMESTATESBACKEND_STATE_H
