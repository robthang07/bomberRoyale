#ifndef BOMBER_ROYALE_MAINMENUMACHINE_H
#define BOMBER_ROYALE_MAINMENUMACHINE_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "../../config.h"
#include "../machine.h"
#include "../gamestatesdata/mainmenuData.h"
#include "../../functions/controllers/menuControler.h"

class MainMenuMachine {
public:
    //The states the main menu can be in.
    enum class stateID { MainMenu, Highscore, Settings, Credits};

    /**
     * Constructor is setting the changed to false and setting the current state to main menu.
     */
    MainMenuMachine();

    /**
     * Destructor is clearing the button and buttons functions vectors.
     */
    ~MainMenuMachine();

    /**
     * Set the current state on main menu machine, and it is also set the changed bool to true.
     * @param state is the state you want to set the main menu state to.
     */
    void setState(stateID state){
        this->currentState = state;
        this->changed = true;
    }

    /**
     * Get the current state set on the main menu machine
     * @return a main menu state
     */
    stateID getState(){
        return currentState;
    }

    /**
     * Set the data pointer to the Main Menu data.
     * @param data is the main menu data you want to set it to.
     */
    void setDataPtr(MainMenuData* data){
        this->data = data;
    }

    /**
     * Get if it is changed or not.
     * @return a boolan that is true if it is changed.
     */
    bool getChanged(){
        return changed;
    }

    /**
     * Set the changed bool
     * @param changed is what you want to set it to.
     */
    void setChanged(bool changed){
        this->changed = changed;
    }

    /**
     * Get the menu buttons.
     * @return a vector of button pointers to the menu buttons.
     */
    std::vector<tgui::Button::Ptr> getMenuButtons(){
        return mainmenuButtons;
    }

    /**
     * Setup the main menu of the current state on the main menu machine.
     * @param machine is the state machine of the game. Not the main menu.
     * @param window is the render window we are showing the game in.
     * @param config is the settings object that we are getting information from.
     * @param deltaTime is a variable with the time when the loop started, and is used to smooth out the animation if the loop use longer time to get done.
     * @return It returns a int based on witch error code it is giving.
     */
    int setup(Machine &machine, sf::RenderWindow& window, sf::Event& event, Config& config, tgui::Gui& gui);

    /**
     * Is handing the event based on witch the current state is.
     * @param event is a object of the events that have happening.
     * @param config is the settings object that we are getting information from.
     * @return It returns a int based on witch error code it is giving.
     */
    int eventHandler(sf::Event event, Config config);

protected:
    //Current state.
    stateID currentState;
    //If state changed
    bool changed;
    //Title push down because of img
    int titleDown = 150;

    Machine* gameMachine;

    //Data on the main menu state in the main FSM.
    MainMenuData* data;

    //Main Menu buttons
    std::vector<tgui::Button::Ptr> mainmenuButtons;
    std::vector<std::function<int()>> mainmenuButtonsFunc;

    //states buttons
    std::vector<tgui::Button::Ptr> highscoreButtons;
    std::vector<std::function<int()>> highscoreButtonsFunc;

    //Settings buttons
    std::vector<tgui::Button::Ptr> settingsButtons;
    std::vector<std::function<int()>> settingsButtonsFunc;

    //Credits buttons
    std::vector<tgui::Button::Ptr> creditsButtons;
    std::vector<std::function<int()>> creditsButtonsFunc;

    //Make a object of menu controller object
    MenuControler menuControler;

    //Setup the main menu layout.
    void setupMainMenu(Machine &machine, sf::RenderWindow& window, Config& config, tgui::Gui& gui);
    //Setup the high score layout.
    void setupHighScore(Machine &machine, sf::RenderWindow& window, Config& config, tgui::Gui& gui);
    //Setup the credits layout.
    void setupCredits(Machine &machine, sf::RenderWindow& window, Config& config, tgui::Gui& gui);
};


#endif //BOMBER_ROYALE_MAINMENUMACHINE_H
