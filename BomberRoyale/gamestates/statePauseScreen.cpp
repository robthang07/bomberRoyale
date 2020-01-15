#include <iostream>
#include <typeinfo>
#include "statePauseScreen.h"
#include "stateMainMenu.h"
#include "machine.h"


StatePauseScreen::StatePauseScreen() {
    //Set that we are not in settings
    insettings = false;
}


StatePauseScreen::~StatePauseScreen() {
    //Clear vectors in when done constructing
    pauseScreenButtons.clear();
    pauseScreenButtonsFunc.clear();
}

int StatePauseScreen::run(Machine &machine, sf::RenderWindow &window, Config& config, float deltaTime) {
    //TODO Implement The Pause Screen here

    sf::Event event;

    if (pausescreenData.isFirstRound()){
        //Set the target for the GUI
        gui.setTarget(window);
        //Setup the GUI so it work.
        SetupGUI(machine,window,event,config);
        //Set the first round to false. So the second time it is not thinking it is first.
        pausescreenData.setFirstRound(false);
    }

    while (window.pollEvent(event))
    {
        // Quit when the user presses 'x', ignore all other events
        if (event.type == sf::Event::Closed) {
            window.close();
            return 0;
        }

        //Pass the event to the gui elements
        gui.handleEvent(event);

    }

    if (!insettings) {
        menuControler.eventHandler(config, event, pauseScreenButtons, pauseScreenButtonsFunc, true);
    }
    else{
        //Only run menu controller if settings is not waiting for input.
        if (!config.getSettingsWaitingForButton()) {
            //gets button and functions settings from config
            auto buttons = config.getButtons();
            auto functions = config.getButtonsFunctions();
            menuControler.eventHandler(config, event, buttons, functions, true);
        }
    }

    //Clear window
    window.clear();

    //Draw the gui up.
    gui.draw();

    //Switch display buffer to display what we have done.
    window.display();

    //Set the settings menu to not wait for buttons more. It get re-setted if the settings menu is still waiting for it.
    config.setSettingsWaitingForButton(false);

    return 1;

}

void StatePauseScreen::SetupGUI(Machine& machine, sf::RenderWindow& window, sf::Event& event, Config& config) {
    //If button is not made then
    if(pauseScreenButtons.empty()) {
        //Creating Buttons adding value and design
        auto pauseElementPtr = pausescreenData.getPauseElementsPtr();

        for (const auto &i : *pauseElementPtr) {
            //create button and get its settings and design from config
            auto button = tgui::Button::create();
            button->setText(i);
            config.getDesign().setButtonDesign(button);
            pauseScreenButtons.push_back(button);
        }
    }

    if (pauseScreenButtonsFunc.empty()){
        //Resume
        pauseScreenButtonsFunc.emplace_back([&](){
            machine.setState(Machine::stateID::GameScreen);
            auto gameData = (GamescreenData *) machine.getStateData();
            gameData->setSettingsChanged(true);
            gameData->setReturnedToGame(true);
            return 1;
        });

        //Settings
        pauseScreenButtonsFunc.emplace_back([&](){
            //Remove widgets when going into setting
            gui.removeAllWidgets();
            insettings = true;
            config.setup(window, event, gui, [&](){ config.applyChanges(window); gui.removeAllWidgets(); insettings = false; SetupGUI(machine,window,event,config); return 1; });
            return 1;
        });
        //Main Menu
        pauseScreenButtonsFunc.emplace_back([&](){ machine.setState(Machine::stateID::MainMenu); auto data = (MainMenuData *) machine.getStateData(); data->setFirstRound(true); return 1;});

        //Functionality to the buttons when they are pressed
        for (int i = 0; i < pauseScreenButtons.size(); ++i) {
            //Error correction for if a they are not equal in size not connect them that are more.
            if (i < pauseScreenButtonsFunc.size()) {
                pauseScreenButtons.at(i)->connect("pressed", pauseScreenButtonsFunc.at(i));
            }
        }

    }

    //add background
    auto backgroundPicture = tgui::Picture::create(config.getDesign().getPauseBackground());
    gui.add(backgroundPicture);

    //Make the box layout.
    auto box = tgui::BoxLayout::create(tgui::Layout2d(config.getBoxWidth(), config.getBoxHeight()));
    box->setPosition(config.getBoxIndentWidth(), config.getBoxIndentHeight());

    //Manually place the buttons at specific position
    for (int j = 0; j < pauseScreenButtons.size(); ++j) {

        pauseScreenButtons[j]->setPosition((config.getBoxWidth() / 2) - (config.getDesign().getButtonSizeWidth()/2),
                                               ((config.getBoxHeight()-titleDown) / pauseScreenButtons.size() - pauseScreenButtons.size()*5) * (j) + titleDown);

        box->add(pauseScreenButtons.at(j));
    }

    //Add the box layout to the gui.
    gui.add(box);

}