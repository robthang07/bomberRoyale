#include <iostream>
#include "stateMainMenu.h"
#include "machine.h"
#include "gamestatesdata/gamescreenData.h"

StateMainMenu::StateMainMenu() {
    //TODO Implement MainMenu initialising
    //Like set the data it need when starting up.
    //If using pointers new here

    //Set the data of MM machine to the data of the MM state
    mainMenuMachine.setDataPtr(&mainMenuData);

    // Loads background music from HDD to RAM
    loadBackgroundMusic();
}

StateMainMenu::~StateMainMenu() {
    //TODO Implement MainMenu de-initialising
    //Then delete the pointers here

}

int StateMainMenu::run(Machine &machine, sf::RenderWindow &window, Config& config, float deltaTime) {
    //TODO Implement The Main Menu here

    sf::Event event{};

    //First Round code that is needed.
    if (mainMenuData.isFirstRound()){
        //Setup the music
        if (!config.isVolumeMuted()) {
            loadBackgroundMusic();

            //To repeat music when is playied once
            backgroundMusic.setLoop(true);

            //Dived by 10 to reduce background music volume so vi hear sound effect such as explosion
            backgroundMusic.setVolume((config.getVolume()) / 10);

            //Playes the background music
            backgroundMusic.play();
        }

        //Set the target for the GUI
        gui.setTarget(window);
        //Setup the GUI so it work.
        mainMenuMachine.setup(machine,window,event,config,gui);
        //Set the first round to false. So the second time it is not thinking it is first.
        mainMenuData.setFirstRound(false);
    }
    //If main menu state changed then do this.
    if (mainMenuMachine.getChanged()){
        //if the settings is not set to mute
        if (!config.isVolumeMuted()) {
            backgroundMusic.setVolume(config.getVolume()/10);
        }
        else{
            backgroundMusic.setVolume(0);
        }

        //Setup the GUI when it change form
        mainMenuMachine.setup(machine,window,event,config,gui);
        mainMenuMachine.setChanged(false);
    }

    // Read all events from the window
    while (window.pollEvent(event))
    {
        gui.handleEvent(event);//Pass the event to the gui elements

        // Quit when the user presses 'x', ignore all other events
        if (event.type == sf::Event::Closed || !window.isOpen()) {
            window.close();
            return 0;
        }
    }

    //Only run menu controller if settings is not waiting for input.
    if (!config.getSettingsWaitingForButton()) {
        int menuC = mainMenuMachine.eventHandler(event, config); //Pass the events to the main menu machine
        if (menuC <= 0) { return menuC; } // if menu Controller gives back a value of less then 1 something is wrong
    }
    //Clear the window of stuff.
    window.clear(sf::Color::Black);

    //Draw the gui up.
    gui.draw();

    //Switch display buffer to display what we have done.
    window.display();

    //Set the settings menu to not wait for buttons more. It get re-setted if the settings menu is still waiting for it.
    config.setSettingsWaitingForButton(false);

    //Stop the music when chancing game state
    if (machine.getState() != Machine::stateID::MainMenu){
        if (!config.isVolumeMuted()) {
            backgroundMusic.stop();
        }
    }

    return 1;

}

void StateMainMenu::loadBackgroundMusic() {

    //Reset the buffer so inloading on 2nd time work as it should.
    backgroundMusic.resetBuffer();

    //Game background music
    if (!backgroundMusicBuffer.loadFromFile("../resources/sounds/menu_music.ogg")) {
        std::cout << "backgroundMusicBuffer loads failed" << std::endl;
    }

    backgroundMusic.setBuffer(backgroundMusicBuffer);
}
