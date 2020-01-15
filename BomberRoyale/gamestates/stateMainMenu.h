#ifndef GAMESTATESBACKEND_STATEMAINMENU_H
#define GAMESTATESBACKEND_STATEMAINMENU_H

#include <TGUI/TGUI.hpp>

#include "state.h"
#include "gamestatesdata/mainmenuData.h"
#include "mainmenustates/mainMenuMachine.h"

class StateMainMenu : public State {
public:
    /**
     * Constructor set a main menu data object pointer to the main menu machine.
     */
    StateMainMenu();
    /**
     * Destructor - do nothing at the moment.
     */
    ~StateMainMenu();

    /**
     * It runs the main menu state
     * @param machine is the state machine that is controlling the states.
     * @param window is the render window we are showing the game in.
     * @param config is the settings object that we are getting information from.
     * @param deltaTime is a variable with the time when the loop started, and is used to smooth out the animation if the loop use longer time to get done.
     * @return It returns a int based on witch error code it is giving.
     */
    int run(Machine& machine, sf::RenderWindow& window, Config& config, float deltaTime);

    /**
     * Get the main menu data
     * @return the main menu data object
     */
    MainMenuData* getStateData() override{
        MainMenuData* data = &mainMenuData;
        return data;
    };

protected:
    /**
     * Loads the background music from HDD to RAM
     */
    void loadBackgroundMusic();

    //TODO Add MainMenu Data here
    MainMenuData mainMenuData;

    //MainMenu objects.
    tgui::Gui gui;

    //MainMenu Machine
    MainMenuMachine mainMenuMachine;

    // ############ Background music ###########
    sf::SoundBuffer backgroundMusicBuffer;
    sf::Sound backgroundMusic;
};


#endif //GAMESTATESBACKEND_STATEMAINMENU_H
