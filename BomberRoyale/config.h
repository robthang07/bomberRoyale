#ifndef GAMESTATESBACKEND_CONF_H
#define GAMESTATESBACKEND_CONF_H

#include <string>
#include <TGUI/TGUI.hpp>

#include "design.h"

class Config{
public:
    /**
     * standard constructor that takes no parameters
     */
    Config();

    /**
     * standard destructor
     */
    ~Config() = default;

    /**
     * Get the game name.
     * @return a string width the game name.
     */
    std::string getGameName(){
        return gameName;
    }

    /**
     * Get the screen width.
     * @return the screen width as a int.
     */
    int getScreenWidth(){
        return screenWidth;
    }

    /**
     * Get the screen height.
     * @return the screen height as a int.
     */
    int getScreenHeight(){
        return screenHeight;
    }

    /**
     * Get the settings menu buttons
     * @return a vector with button pointers to the different buttons on the settings menu.
     */
    std::vector<tgui::Button::Ptr> getButtons(){
        return buttons;
    }

    /**
     * Get the functions of the settings menu buttons
     * @return a vector with lambda functions that is corresponding to the buttons on the settings menu.
     */
    std::vector<std::function<int()>> getButtonsFunctions(){
        return buttonsFunctions;
    }

    /**
     * Get the names of the settings screen.
     * @return a vector of strings with the names of the different settings screens.
     */
    std::vector<std::string>& getSettingsNames(){
        return settingsNames;
    }

    /**
     * Get the Tab pointer.
     * @return a tab pointer.
     */
    tgui::Tabs::Ptr getTabPtr(){
        return tabs;
    }

    /**
     * Get the Screen Mode
     * @return a int that tells it witch Screen Mode it is.
     */
    int getScreenMode(){
        return screenMode;
    };

    /**
     * Get if the setting menu is waiting for a button.
     * @return a bool witch is true if the settings menu is waiting for a button.
     */
    bool getSettingsWaitingForButton(){
        return settingsWaitingForButton;
    };

    /**
     * Set the settings menu to wait for a button
     * @param givenButton is a bool that set it true if given true.
     */
    void setSettingsWaitingForButton(bool givenButton){
        settingsWaitingForButton = givenButton;
    }

    /**
     * Get the box width.
     * @return the box width as a int.
     */
    int getBoxWidth(){
        return boxWidth;
    }

    /**
     * Get the box height.
     * @return the box height as a int.
     */
    int getBoxHeight(){
        return boxHeight;
    }

    /**
     * Get the box indent width.
     * @return the box indent width as a int.
     */
    int getBoxIndentWidth(){
        return boxIndentWidth;
    }

    /**
     * Get the box indent height.
     * @return the box indent height as a int.
     */
    int getBoxIndentHeight(){
        return boxIndentHeight;
    }

    /**
     * Get the Pause button.
     * @return the pause button as a sf::Keyboard::Key
     */
    sf::Keyboard::Key getPauseBtn(){
        return pauseBtn;
    }

    /**
     * Get the Enter button.
     * @return the Enter button as a sf::Keyboard::Key
     */
    sf::Keyboard::Key getEnterBtn(){
        return enterBtn;
    }

    /**
     * Get the Player 1 Left button.
     * @return the player 1 left button as a sf::Keyboard::Key
     */
    sf::Keyboard::Key getPlayer1LeftBtn(){
        return player1LeftBtn;
    }

    /**
     * Get the Player 1 right button.
     * @return the player 1 right button as a sf::Keyboard::Key
     */
    sf::Keyboard::Key getPlayer1RightBtn(){
        return player1RightBtn;
    }

    /**
     * Get the Player 1 up button.
     * @return the player 1 up button as a sf::Keyboard::Key
     */
    sf::Keyboard::Key getPlayer1UpBtn(){
        return player1UpBtn;
    }

    /**
    * Get the Player 1 down button.
    * @return the player 1 down button as a sf::Keyboard::Key
    */
    sf::Keyboard::Key getPlayer1DownBtn(){
        return player1DownBtn;
    }

    /**
    * Get the Player 1 bomb button.
    * @return the player 1 bomb button as a sf::Keyboard::Key
    */
    sf::Keyboard::Key getPlayer1BombBtn(){
        return player1BombBtn;
    }

    /**
     * Get the inputs list for the player
     * @param playerNr the number on the current player
     * @return all the player inputs of the current player as a std::vector<sf::keyboard>
     */
    std::vector<sf::Keyboard::Key> getInputs(int playerNr) {

        return inputList[playerNr];
    }

    /**
     * Setup the settings menu for the user
     * @param gui take a tgui::gui element to set the menu on.
     * @param settingsButtonFunction is a function that is hold to the last setting button, the back button.
     */
    void setup(sf::RenderWindow& window, sf::Event& event, tgui::Gui& gui, std::function<int()> settingsButtonFunction);

    /**
     * Apply the changes that is changed in the settings menu
     * @param window is the render window it will set the changes on.
     */
    void applyChanges(sf::RenderWindow &window);

    /**
     * Get the design
     * @return the design class
     */
    Design getDesign(){
        return design;
    }

    /**
     * User can set game volume in setting
     * This function returns user's volume
     */
    const int getVolume() {
        //Setting volume range is between 0 and 10.
        //sf::Sounds volume range is between 0 and 100.
        int volumeParameterToSF_Sound = volume * 10;
        return volumeParameterToSF_Sound;
    }

    /**
     * User can set game volume to mute
     * @return Whether user has muted the volume. True:Mute False:Not
     */
    const bool isVolumeMuted() {
        return muteVolume;
    }

protected:
    /**
     * Setup the Graphics
     * @param panel is where it is going to add the elements.
     */
    void setupGraphics(tgui::ScrollablePanel::Ptr& panel);

    /**
     * Setup the Controls
     * @param panel is where it is going to add the elements.
     */
    void setupControl(tgui::ScrollablePanel::Ptr& panel);

    /**
     * Setup the Audio
     * @param panel is where it is going to add the elements.
     */
    void setupAudio(tgui::ScrollablePanel::Ptr& panel);

    /**
     * Connect the functions to every settings elements on every panel
     */
    void connectFunctions(sf::RenderWindow& window, sf::Event& event, tgui::Gui& gui);

    /**
     * Read the settings from the Json file
     * @param path is the path to the file it is going to save it.
     */
    bool readFromJson(std::string path);

    /**
     * Save the settings to the Json file
     * @param path is the path to the file it is going to save it.
     */
    void saveToJson(std::string path);


    //#####Core#####

    //GameName
    std::string gameName = "Bomber Royale";

    //Screen
    int screenWidth = 680;
    int screenHeight = 520;
    int screenMode = sf::Style::Default;
    bool screenModeBool = false;

    //####Settings Screen####
    //Button and functions vector
    std::vector<tgui::Button::Ptr> buttons;
    std::vector<std::function<int()>> buttonsFunctions;

    //The startIndex over witch tab it is going to focusing on.
    int startIndex = 0;
    //The settings tabs
    tgui::Tabs::Ptr tabs = tgui::Tabs::create();
    //If tabs created
    bool tabsCreated = false;
    //The Settings Screens saved in a map.
    std::map<std::string, tgui::Panel::Ptr> settingsScreens;
    //Settings names taken from the settings screen for easier accessing.
    std::vector<std::string> settingsNames;

    //bool to check if the graphic have changed any
    bool graphicChanged = false;
    //Edit ptr to the graphics boxes
    tgui::EditBox::Ptr screenWidthBox;
    tgui::EditBox::Ptr screenHeightBox;

    //vector of pointers for every edit box on the control screen
    std::vector<tgui::EditBox::Ptr> controlEditboxes;
    bool settingsWaitingForButton;

    //audio slider ptr
    tgui::Slider::Ptr audioVolumeSlider;


    //#####Design#####

    Design design;

    //Box layout values
    float boxPercent = 0.8;
    float boxIndent = (1 - boxPercent) / 2;

    //Box layout sizes
    int boxWidth;
    int boxHeight;
    int boxIndentWidth;
    int boxIndentHeight;

    //#####KeyBindings#####

    //Core buttons
    sf::Keyboard::Key pauseBtn = sf::Keyboard::Escape;
    sf::Keyboard::Key enterBtn = sf::Keyboard::Return;

    //Player moments
    sf::Keyboard::Key player1LeftBtn = sf::Keyboard::Left;
    sf::Keyboard::Key player1RightBtn = sf::Keyboard::Right;
    sf::Keyboard::Key player1UpBtn = sf::Keyboard::Up;
    sf::Keyboard::Key player1DownBtn = sf::Keyboard::Down;
    sf::Keyboard::Key player1BombBtn = sf::Keyboard::Space;

    std::vector<std::vector<sf::Keyboard::Key>> inputList;

    //##### Sound effect #####
    int volume = 10; //Volume range is between 0 and 10.
    bool muteVolume = false;

};

#endif //GAMESTATESBACKEND_CONF_H
