#ifndef GAMESTATESBACKEND_STATEPAUSESCREEN_H
#define GAMESTATESBACKEND_STATEPAUSESCREEN_H

#include <TGUI/TGUI.hpp>

#include "state.h"
#include "gamestatesdata/pausescreenData.h"
#include "../functions/controllers/menuControler.h"

class StatePauseScreen : public State {
public:
    /**
     * set insetting to false, which allows buttons to be displayed
     * and allows button select because we are not in the setting
     */
    StatePauseScreen();

    /**
     * Clear vectors when done constructing
     */
    ~StatePauseScreen() override;

    /**
     * Function to display the pause screen and running it.
     * @param machine is used to change the states
     * @param window is used to draw on and display on
     * @param config is used to get the default settings and designs
     * @param deltaTime is not used but is important for other states
     * @return int based on which error code it is given
     */
    int run(Machine& machine, sf::RenderWindow& window, Config& config, float deltaTime) override;

    /**
     * Function to get pause state data.
     * @return object of the game data
     */
    PausescreenData* getStateData() override{
        return &pausescreenData;
    };

protected:

    /**
     * Function to setup a gui for the window
     * @param machine is used to change states
     * @param window is the window we are displaying and working on
     * @param config is used to get the default setting and designs
     */
    void SetupGUI(Machine& machine, sf::RenderWindow& window, sf::Event& event, Config& config);

    //TODO: Add PauseScreen Data here
    PausescreenData pausescreenData;

    //Used to set position on the top element of the buttons
    int titleDown = 150;

    //Used to check if the we are in settings or not
    bool insettings;

    //Make a object of menu controller object
    MenuControler menuControler;

    //PauseScreen objects.
    tgui::Gui gui;

    //Vector for buttons
    std::vector<tgui::Button::Ptr> pauseScreenButtons;
    //Vector that decides which function it belongs
    std::vector<std::function<int()>> pauseScreenButtonsFunc;

};

#endif //GAMESTATESBACKEND_STATEPAUSESCREEN_H