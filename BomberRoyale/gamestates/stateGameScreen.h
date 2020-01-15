#ifndef GAMESTATESBACKEND_STATEGAMESCREEN_H
#define GAMESTATESBACKEND_STATEGAMESCREEN_H


// Auby
#include <list>
#include <SFML/Graphics.hpp>
#include <TGUI/Gui.hpp>
#include "../layers/map.h"
#include "../functions/detectors/collision.h"
#include "state.h"
#include "gamestatesdata/gamescreenData.h"
#include "../objects/Player.h"
#include "../objects/Bomb.h"
#include "../objects/object.h"
#include "../objects/BaseObject.h"
#include "../config.h"


#include "../objects/powerups/powerUpHP.h"
#include "../objects/powerups/powerUpSpeed.h"
#include "../objects/powerups/bombPU.h"
#include "../objects/BaseObject.h"
#include "../functions/calculators/baseAI.h"
#include "../functions/detectors/collision.h"


class Object;

class StateGameScreen : public State{
public:
    /**
     * The constructor is loading in the map, and placing the objects in a object vector.
     */
    StateGameScreen();

    /**
     * The destructor is clearing the vectors and lists used.
     */
    ~StateGameScreen() override;

    /**
     * It runs the game state
     * @param machine is the state machine that is controlling the states.
     * @param window is the render window we are showing the game in.
     * @param config is the settings object that we are getting information from.
     * @param deltaTime is a variable with the time when the loop started, and is used to smooth out the animation if the loop use longer time to get done.
     * @return It returns a int based on witch error code it is giving.
     */
    int run(Machine& machine, sf::RenderWindow& window, Config& config, float deltaTime) override;

    /**
     * It get the Game State Data.
     * @return a object of Game State Data
     */
    GamescreenData* getStateData() override{
        return &gamescreenData;
    };

protected:
    /**
     * Set up the User Interface
     * @param window is the Render Window we are going to add the User Interface.
     * @param config is the settings object that we are getting information from.
     */
    void setupUserInterface(sf::RenderWindow& window, Config& config);
    /**
     * Update the User Interface
     * @param window is the Render Window we are going to add the User Interface.
     * @param deltaTime is used to update the time
     */
    void updateUserInterface(sf::RenderWindow& window, float deltaTime);

    /**
     * Load in the map.
     */
    void loadMap();

    /**
     * Loads the background music from HDD to RAM
     */
    void loadBackgroundMusic();


    //A object of the Game Screen Data
    GamescreenData gamescreenData;

    //list of all players in the game
    std::list<std::shared_ptr<Player>> players;

    //A list with the active bombs
    //std::list<std::shared_ptr<Bomb>> bombs;

    //A list over powerOPS
    std::list<std::shared_ptr<BasePowerUps>> powerups;

    // Map oriented objects
    // List of game objects. Should of course be put somewhere else in a bigger game
    std::list<std::shared_ptr<Object>> objects;
    //List of wall elements
    std::list<std::shared_ptr<Object>> walls;
    //A object of the map.
    Map map;

    //Interface layout variables
    //A object of gui that have every gui element in it.
    tgui::Gui gui;
    //A label with the time
    tgui::Label::Ptr timerGui;
    //A vector with labels pointers for every player score
    std::vector<tgui::Label::Ptr> playerScoresGui;

    collision collision1;

    //Interface data var
    float timer;
    float resetTime = 5 * 60;

    float AI_timer = 5;

    // ############ Background music ###########
    sf::SoundBuffer backgroundMusicBuffer;
    sf::Sound backgroundMusic;
};

#endif //GAMESTATESBACKEND_STATEGAMESCREEN_H
