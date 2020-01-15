#include <iostream>
#include <SFML/Graphics.hpp>
#include "gamestates/stateGameScreen.h"
#include "gamestates/machine.h"

int main() {
    //Game variable
    int game = 1;

    //Delta time
    float deltaTime = 0;
    //Times the animation
    sf::Clock clock;
    clock.restart();

    //Make a config object
    Config config;

    //Make the game window
    sf::RenderWindow window(sf::VideoMode(config.getScreenWidth(), config.getScreenHeight()), config.getGameName(), config.getScreenMode());

    // Enable vertical sync - prevents tearing and locks framerate to display
    window.setVerticalSyncEnabled(true);

    // Set frame rate limit on the window
    window.setFramerateLimit(60);

    //State Machine for states of the game
    Machine* machine = new Machine;
    
    //Set the state machine to the state you want for testing / working on.
    //machine->setState(Machine::stateID::GameScreen);


    // Run the game loop as long as the window is open
   while (game >= 1) {
       //Run the state the game is in.
        game = machine->run(window, config, deltaTime);
        //Get the current time to the delta objects for smooth animation
        deltaTime = clock.getElapsedTime().asSeconds();
        //Restart the clock for everytime it run around.
        clock.restart();

    }

    //Return game, it give us the exit code.
    //0 = Good, everything negative is error we have defined.
    return game;
}
