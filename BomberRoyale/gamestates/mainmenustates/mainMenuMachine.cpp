#include <iostream>
#include <functional>
#include "mainMenuMachine.h"
#include "../gamestatesdata/gamescreenData.h"
#include "../../jsonobjects/highscores.h"
#include "../../jsonobjects/credits.h"

MainMenuMachine::MainMenuMachine() {
    //Start inn the main menu
    currentState = stateID::MainMenu;

    //Set the changed to false
    changed = false;

}

MainMenuMachine::~MainMenuMachine() {
    //Remove every button and functions from the vectors for deconstructions
    mainmenuButtons.clear();
    mainmenuButtonsFunc.clear();
    highscoreButtons.clear();
    highscoreButtonsFunc.clear();
    settingsButtons.clear();
    settingsButtonsFunc.clear();
    creditsButtons.clear();
    creditsButtonsFunc.clear();

    std::cout << "Main Menu Machine destructor called." << std::endl;
}

int MainMenuMachine::eventHandler(sf::Event event, Config config){

    //Take the current state and use it to sett the corresponding menu, functions
    switch (currentState){
        case stateID::MainMenu:{
            return menuControler.eventHandler(config,event,mainmenuButtons,mainmenuButtonsFunc,false);
        }
        case stateID::Highscore:{
            return menuControler.eventHandler(config,event,highscoreButtons, highscoreButtonsFunc,false);
        }
        case stateID::Settings:{
            auto buttons = config.getButtons();
            auto functions = config.getButtonsFunctions();
            return menuControler.eventHandler(config,event,buttons,functions,false);
        }
        case stateID::Credits:{
            return menuControler.eventHandler(config,event,creditsButtons,creditsButtonsFunc,false);
        }
    }
}

int MainMenuMachine::setup(Machine &machine, sf::RenderWindow& window, sf::Event& event, Config& config, tgui::Gui& gui){
    //Remove every widget from gui
    gui.removeAllWidgets();

    //Then setup based on current state
    switch (currentState){
        case stateID::MainMenu:{
            setupMainMenu(machine,window,config, gui);
            break;
        }
        case stateID::Highscore:{
            setupHighScore(machine,window,config,gui);
            break;
        }
        case stateID::Settings:{
            //Setup the settings
            config.setup(window, event, gui,[&]() { config.applyChanges(window); setState(stateID::MainMenu); setChanged(true); return 1; });

            break;
        }
        case stateID::Credits:{
            setupCredits(machine,window,config,gui);
            break;
        }
        default:{
            std::cout << "Menu setup did not initialize correctly." << std::endl;
            return -2;
        }
    }
    //Everything fine return 1. If break everything is fine.
    return 1;
}


void MainMenuMachine::setupMainMenu(Machine &machine, sf::RenderWindow& window, Config& config, tgui::Gui& gui) {
    //Add background picture
    auto backgroundPicture = tgui::Picture::create(config.getDesign().getMainBackground());
    gui.add(backgroundPicture);

    //Get a ptr to the menu elements
    if (mainmenuButtons.empty()) {
        auto menuElementsPtr = data->getMenuElementsPtr();

        //Making the buttons and pushing them to the a vector for storing them.
        for (const auto &i : *menuElementsPtr) {
            auto button = tgui::Button::create();
            config.getDesign().setButtonDesign(button);
            button->setText(i);

            mainmenuButtons.push_back(button);
        }
    }
    //Maybe add a try and catch here for safty check.
    //Make the box layout.
    auto box = tgui::BoxLayout::create(tgui::Layout2d(config.getBoxWidth(), config.getBoxHeight()));
    box->setPosition(config.getBoxIndentWidth(), config.getBoxIndentHeight());

    //Take the buttons: set posision and add them to the boxLayout.
    for (int i = 0; i < mainmenuButtons.size(); ++i) {
        if (!(i % 2)){
            mainmenuButtons.at(i)->setPosition(
                    ((config.getBoxWidth() / 2) - (mainmenuButtons.at(i)->getSize().x) - (config.getBoxWidth()*0.05)),
                    ((((config.getBoxHeight()-titleDown) / (mainmenuButtons.size() / 2)) * (i/2)) + titleDown));

            box->add(mainmenuButtons.at(i));
        }
        else {
            mainmenuButtons.at(i)->setPosition(
                    ((config.getBoxWidth() / 2) + (config.getBoxWidth()*0.05)),
                    (((config.getBoxHeight() - titleDown) / (mainmenuButtons.size() / 2)) * (i/2) + titleDown));

            box->add(mainmenuButtons.at(i));
        }
    }

    //Maybe make a function that find every so it can set them up if we swap them.
    //Set the buttons functions they are going to run.
    //if (mainmenuButtonsFunc.empty()) {

        gameMachine = &machine;
        mainmenuButtonsFunc.clear();
        //Single player
        mainmenuButtonsFunc.emplace_back([&]() { gameMachine->setState(Machine::stateID::GameScreen); auto a = (GamescreenData *) gameMachine->getStateData();
            a->setSinglePlayer(true); a->setFirstRound(true); return 1;});
        //Multi player
        mainmenuButtonsFunc.emplace_back([&]() { gameMachine->setState(Machine::stateID::GameScreen); auto a = (GamescreenData *) gameMachine->getStateData();
            a->setSinglePlayer(false); a->setFirstRound(true); return 1;});
        //HighScore
        mainmenuButtonsFunc.emplace_back([&]() { setState(MainMenuMachine::stateID::Highscore); setChanged(true); return 1;});
        //Settings
        mainmenuButtonsFunc.emplace_back([&]() { setState(MainMenuMachine::stateID::Settings); setChanged(true); return 1;});
        //Credits
        mainmenuButtonsFunc.emplace_back([&]() { setState(MainMenuMachine::stateID::Credits); setChanged(true); return 1;});
        //Exit
        mainmenuButtonsFunc.emplace_back([&]() {
            config.applyChanges(window); window.close(); return 0; });


    //Add the functions to the buttons
    for (int i = 0; i < mainmenuButtons.size(); ++i) {
        //Connect the function to the button
        mainmenuButtons.at(i)->disconnectAll();
    }
        //Add the functions to the buttons
        for (int i = 0; i < mainmenuButtons.size(); ++i) {
            //Connect the function to the button
            mainmenuButtons.at(i)->connect("pressed", mainmenuButtonsFunc.at(i));
        }


    //Add the box layout to the gui.
    gui.add(box);
}

void MainMenuMachine::setupHighScore(Machine &machine, sf::RenderWindow& window, Config& config, tgui::Gui& gui) {
    //Make a highscore objects to read in the data
    Highscores highscores;
    bool wasRead = highscores.readFromJson("../jsonobjects/highscore.json");

    /* //Test code for writing to the json file.
    highscores.getHighScores().at(9)->name = "TWA";
    highscores.getHighScores().at(9)->score = "00020022";
    highscores.writeToJson("../jsonobjects/highscore.json");
    */

    //Add background picture
    auto backgroundPicture = tgui::Picture::create(config.getDesign().getSettingsBackground());
    gui.add(backgroundPicture);

    //Maybe add a try and catch here for safty check.
    //Make the box layout.
    auto box = tgui::BoxLayout::create(tgui::Layout2d(config.getBoxWidth(), config.getBoxHeight()));
    box->setPosition(config.getBoxIndentWidth(), config.getBoxIndentHeight());

    //Make a text box
    auto textBox = tgui::TextBox::create();
    textBox->setReadOnly(true);
    //chatBox->setVerticalScrollbarPresent(true);
    textBox->setSize(tgui::Layout2d(config.getBoxWidth(),config.getBoxHeight()-config.getDesign().getButtonSizeHeight()));
    config.getDesign().setTextBoxDesign(textBox);
    textBox->setPosition(0, 0);

    //Check if the highscore was read;
    if (wasRead){
        //If read save the info as a string and set it in the text box
        std::string strHighscores;

        auto h =  highscores.getHighScores();
        int nr = 1;
        for (auto b: h){
            strHighscores += std::to_string(nr) + ". \t" +  b->name + ": " + b->score + "\n";
            nr++;
        }

        textBox->setText(strHighscores);
    }
    else{
        //Else set that it was not found / broken file.
        textBox->setText("Did not read in the highscores from the file.\nJSON file was not found, or the file is broken.");
    }

    box->add(textBox);

    //Add button functions to a vector
    if (highscoreButtonsFunc.empty()){
        highscoreButtonsFunc.emplace_back([&](){ setState(stateID::MainMenu); setChanged(true); return 1; });
    }
    //Add the buttons to a vector so we dont need to remake them
    if (highscoreButtons.empty()){
        //Make a button on the bottom.
        auto button = tgui::Button::create();
        config.getDesign().setButtonDesign(button);
        button->setPosition((config.getBoxWidth()/2)-(config.getDesign().getButtonSizeWidth()/2),config.getBoxHeight()-config.getDesign().getButtonSizeHeight());
        button->setText("Main Menu");
        button->connect("pressed", highscoreButtonsFunc.at(0));
        box->add(button);

        //add button to vector
        highscoreButtons.emplace_back(button);
    }
    //if the buttons is made just add them back in the new boxlayout
    else{
        box->add(highscoreButtons.at(0));
    }

    gui.add(box);
}

void MainMenuMachine::setupCredits(Machine &machine, sf::RenderWindow &window, Config &config, tgui::Gui &gui) {
    //TODO Add the json code for getting credits from json file
    Credits credits;
    credits.readFromJson("../jsonobjects/credits.json");

    //Add background picture
    auto backgroundPicture = tgui::Picture::create(config.getDesign().getSettingsBackground());
    gui.add(backgroundPicture);

    //Maybe add a try and catch here for safty check.
    //Make the box layout.
    auto box = tgui::BoxLayout::create(tgui::Layout2d(config.getBoxWidth(), config.getBoxHeight()));
    box->setPosition(config.getBoxIndentWidth(), config.getBoxIndentHeight());

    //Make a text box
    auto textBox = tgui::TextBox::create();
    textBox->setReadOnly(true);
    //chatBox->setVerticalScrollbarPresent(true);
    config.getDesign().setTextBoxDesign(textBox);
    textBox->setSize(tgui::Layout2d(config.getBoxWidth(),config.getBoxHeight()-config.getDesign().getButtonSizeHeight()));
    textBox->setPosition(0, 0);
    textBox->setText(credits.getText());

    box->add(textBox);

    //Add buttons function to vector
    if (creditsButtonsFunc.empty()){
        creditsButtonsFunc.emplace_back([&](){ setState(stateID::MainMenu); setChanged(true); return 1; });
    }

    //add button to vector
    if (creditsButtons.empty()){
        //Make a button on the bottom.
        auto button = tgui::Button::create();
        config.getDesign().setButtonDesign(button);
        button->setPosition((config.getBoxWidth()/2)-(config.getDesign().getButtonSizeWidth()/2),config.getBoxHeight()-config.getDesign().getButtonSizeHeight());
        button->setText("Main Menu");
        button->connect("pressed", creditsButtonsFunc.at(0));
        box->add(button);

        creditsButtons.emplace_back(button);
    }
    else{
        box->add(creditsButtons.at(0));
    }

    gui.add(box);
}