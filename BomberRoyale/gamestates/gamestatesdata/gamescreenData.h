#ifndef BOMBER_ROYALE_GAMESCREENDATA_H
#define BOMBER_ROYALE_GAMESCREENDATA_H

#include "stateData.h"

class GamescreenData : public StateData{
public:
    //TODO: implement a constructer, deconstructer, getter, setteer for this class
    /**
     * getter that returns if the game is singleplayer or multiplayer
     * @return true if we want to play singleplayer and false if we want to play multiplayer
     */
    bool getSinglePlayer(){
        return singlePlayer;
    }
    /**
     * sets the value of singleplayer to whether we want the game to be singleplayer or multiplayer
     * @param val is the state we want the game to be in
     */
    void setSinglePlayer(bool val){
         singlePlayer = val;
    }

    /**
     * Getter that returns if the settings have changed between pause and game screen.
     * @return true if the settings changed in the pause screen.
     */
    bool getSettingsChanged(){
        return settingsChanged;
    }

    /**
     * Sets the value of settingschange to whether the settings changed or not.
     * @param changed is the bool we sett if it have changed or not.
     */
    void setSettingsChanged(bool changed){
        this->settingsChanged = changed;
    }


    bool getReturnedToGame(){
        return returnedToGame;
    }

    void setReturnedToGame(bool returned){
        this->returnedToGame = returned;
    }

protected:

    //TODO: Add data gamescreen need here
    //boolean that tells the game whether it plays single player or multiplayer
    bool singlePlayer = true;
    //boolan that tells if the settings changed in pause screen.
    bool settingsChanged = true;
    //boolan that tells if returned from settings
    bool returnedToGame = false;

};


#endif //BOMBER_ROYALE_GAMESCREENDATA_H
