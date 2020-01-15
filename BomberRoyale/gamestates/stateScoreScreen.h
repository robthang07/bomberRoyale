#ifndef GAMESTATESBACKEND_STATESCORESCREEN_H
#define GAMESTATESBACKEND_STATESCORESCREEN_H

#include <TGUI/TGUI.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "gamestatesdata/scorescreenData.h"
#include "../functions/controllers/menuControler.h"

class StateScoreScreen : public State {
public:
    /**
     * Constructor - at the moment do nothing.
     */
    StateScoreScreen();

    /**
     * Destructor clear the buttons and function vector.
     */
    ~StateScoreScreen();

    /**
     * It runs the score state
     * @param machine is the state machine that is controlling the states.
     * @param window is the render window we are showing the game in.
     * @param config is the settings object that we are getting information from.
     * @param deltaTime is a variable with the time when the loop started, and is used to smooth out the animation if the loop use longer time to get done.
     * @return It returns a int based on witch error code it is giving.
     */
    int run(Machine& machine, sf::RenderWindow& window, Config& config, float deltaTime);

    /**
     * Get the score screen data
     * @return the score screen data object
     */
    ScorescreenData* getStateData() override{
        return &scorescreenData;
    };

protected:
    /**
     * Function to setup the gui for the window
     * @param machine is used to change states
     * @param window is the window we are displaying and working on
     * @param config is used to get the default setting and designs
     */
    void SetupGUI(Machine& machine, sf::RenderWindow& window, Config& config);

    /**
     * Loads the background music from HDD to RAM
     */
    void loadBackgroundMusic();

    //Score screen data
    ScorescreenData scorescreenData;

    //get down from title in the picture
    int titleDown = 150;

    //Make a object of menu controller object
    MenuControler menuControler;

    //ScoreScreen Objects.
    tgui::Gui gui;
    std::vector<tgui::Button::Ptr> scoreScreenButtons;
    std::vector<std::function<int()>> scoreScreenButtonsFunc;

    // ############ Background music ###########
    sf::SoundBuffer backgroundMusicBuffer;
    sf::Sound backgroundMusic;
};


#endif //GAMESTATESBACKEND_STATESCORESCREEN_H
