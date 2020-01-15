#ifndef GAMESTATESBACKEND_MACHINE_H
#define GAMESTATESBACKEND_MACHINE_H

#include <map>
#include <SFML/Graphics.hpp>
#include "stateGameScreen.h"
#include "../config.h"
#include "gamestatesdata/stateData.h"

class State;

class Machine {
public:
    //The states the game can be in.
    enum class stateID { MainMenu, GameScreen, PauseScreen, ScoreScreen};

    /**
     * Constructor add the states to a map for easier to get the state you want.
     */
    Machine();

    /**
     * Destructor delete the states that was added to the map.
     */
    ~Machine();

    /**
     * Set the state on the machine.
     * @param state is the state you want to set on the machine
     */
    void setState(stateID state){
        this->currentState = state;
    }

    /**
     * Get the state that the machine is having
     * @return the state enum
     */
    stateID getState(){
        return currentState;
    }

    /**
     * It runs the states based on witch state the machine have.
     * @param machine is the state machine that is controlling the states.
     * @param window is the render window we are showing the game in.
     * @param config is the settings object that we are getting information from.
     * @param deltaTime is a variable with the time when the loop started, and is used to smooth out the animation if the loop use longer time to get done.
     * @return It returns a int based on witch error code it is giving.
     */
    int run(sf::RenderWindow& window, Config& config, float delta);

    /**
     * Get the state data
     * @return a state data object
     */
    StateData* getStateData();

protected:
    //The current state
    stateID currentState;
    //All the states are put in a map for easy to take them out again.
    //Instead of ID number we use statenames for it. ex: Machine::stateID::MainMenu
    std::map<stateID, State*> states;

};


#endif //GAMESTATESBACKEND_MACHINE_H
