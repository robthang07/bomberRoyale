#include <iostream>

#include "machine.h"
#include "stateMainMenu.h"
#include "stateGameScreen.h"
#include "stateScoreScreen.h"
#include "statePauseScreen.h"

Machine::Machine() {
    //Start inn the main menu
    currentState = stateID::MainMenu;

    //Put the states in to a map so we can easier call them.
    states.emplace(stateID::MainMenu, new StateMainMenu());
    states.emplace(stateID::GameScreen, new StateGameScreen());
    states.emplace(stateID::PauseScreen, new StatePauseScreen());
    states.emplace(stateID::ScoreScreen, new StateScoreScreen());

}

Machine::~Machine(){
    std::cout << "Machine destructor called." << std::endl;

    // Free the states from memory
    for (auto s: states)
        delete s.second;

    //Then clear map for data.
    states.clear();
}

int Machine::run(sf::RenderWindow& window, Config& config, float deltaTime) {

    int stateReturn;

    //Run the current states run command. Work for every state.
    stateReturn = states[currentState]->run(*this, window, config, deltaTime);

    return stateReturn;

}

//If using this function you need to cast it so you get the derived type.
StateData* Machine::getStateData(){
    return states[currentState]->getStateData();
}