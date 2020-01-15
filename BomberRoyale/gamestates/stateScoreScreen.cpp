#include <iostream>

#include "stateScoreScreen.h"
#include "stateMainMenu.h"
#include "machine.h"

StateScoreScreen::StateScoreScreen() {
    //Load in the music
    loadBackgroundMusic();
}

StateScoreScreen::~StateScoreScreen() {
    //clear vectors
    scoreScreenButtons.clear();
    scoreScreenButtonsFunc.clear();

}

int StateScoreScreen::run(Machine &machine, sf::RenderWindow &window, Config& config, float deltaTime) {

    //Check if it is the first round in the looping
    if (scorescreenData.isFirstRound()) {
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


        gui.setTarget(window); //Set the target for the GUI
        SetupGUI(machine, window,config); //Setup the GUI so it work.
        scorescreenData.setFirstRound(false); //Set the first round to false. So the second time it is not thinking it is first.
    }

    sf::Event event;

    while (window.pollEvent(event)) {
        //Quit when the user press 'x', ignore all other events
        if (event.type == sf::Event::Closed) {
            window.close();
            return 0;
        }
        gui.handleEvent(event); //Pass the event to the gui elements
    }

    //Controller for the menu buttons
    menuControler.eventHandler(config,event,scoreScreenButtons,scoreScreenButtonsFunc,true);

    window.clear();

    gui.draw(); //Draw the gui up.
    window.display(); //Switch display buffer to display what we have done.

    //Stop the music when chancing game state
    if (machine.getState() != Machine::stateID::ScoreScreen){
        if (!config.isVolumeMuted()) {
            backgroundMusic.pause();
        }
    }

    return 1;
}

void StateScoreScreen::SetupGUI(Machine& machine, sf::RenderWindow &window, Config &config) {
    //Check if buttons is made
    if (scoreScreenButtons.empty()) {
        auto scoreElementPtr = scorescreenData.getScoreElementsPtr();

        for (const auto &i : *scoreElementPtr) {
            auto button = tgui::Button::create();
            button->setText(i);
            config.getDesign().setButtonDesign(button);

            scoreScreenButtons.push_back(button);
        }
    }

    if (scoreScreenButtonsFunc.empty()){
        scoreScreenButtonsFunc.emplace_back([&]() { machine.setState(Machine::stateID::GameScreen); auto a = (GamescreenData *) machine.getStateData(); a->setFirstRound(true); return 1;});
        scoreScreenButtonsFunc.emplace_back([&]() { machine.setState(Machine::stateID::MainMenu); auto a = (MainMenuData *) machine.getStateData(); a->setFirstRound(true); return 1; });

        //Functionality to the buttons when they are pressed
        for (int i = 0; i < scoreScreenButtons.size(); ++i) {
            //Error correction for if a they are not equal in size not connect them that are more.
            if (i < scoreScreenButtonsFunc.size()) {
                scoreScreenButtons.at(i)->connect("pressed", scoreScreenButtonsFunc.at(i));
            }
        }
    }

    //Remove all the widgets so it not overflow with data
    gui.removeAllWidgets();

    //add background
    auto backgroundPicture = tgui::Picture::create(config.getDesign().getScoreBackground());
    gui.add(backgroundPicture);

    //Make the box layout.
    auto box = tgui::BoxLayout::create(tgui::Layout2d(config.getBoxWidth(), config.getBoxHeight()));
    box->setPosition(config.getBoxIndentWidth(), config.getBoxIndentHeight());

    //Add the score
    auto scoreBG = tgui::Label::create();
    scoreBG->setPosition(0, titleDown);
    scoreBG->setSize(tgui::Layout2d((config.getBoxWidth()/2)- config.getDesign().getButtonSizeWidth(), config.getBoxHeight()-titleDown));
    scoreBG->getRenderer()->setBackgroundColor(sf::Color::Black);
    scoreBG->getRenderer()->setOpacity(0.5);
    box->add(scoreBG);

    //Add the score
    auto score = tgui::Label::create();
    score->setPosition(0, titleDown);
    //score->setMaximumTextWidth((config.getBoxWidth()/2)-config.getDesign().getButtonSizeWidth());
    score->setSize(tgui::Layout2d((config.getBoxWidth()/2)- config.getDesign().getButtonSizeWidth(), config.getBoxHeight()-titleDown));
    config.getDesign().setLabelDesign(score);

    //Set the text
    if (scorescreenData.getDraw()){
        score->setText("Status: Draw");
    }
    else{
        if (scorescreenData.getWinner()){
            score->setText("Status: Winner, player " + std::to_string(scorescreenData.getWinnerPlayerNum()+1) + "\n\nScore:\n" + std::to_string(scorescreenData.getScore()));
        }
        else {
            score->setText("Status: Lost\n\nBetter luck next time :)");
        }
    }

    box->add(score);


    //Manually place the buttons at specific position
    for (int j = 0; j < scoreScreenButtons.size(); ++j) {
        scoreScreenButtons[j]->setPosition((config.getBoxWidth() / 2) - (config.getDesign().getButtonSizeWidth()/2),
                ((config.getBoxHeight()-titleDown) / scoreScreenButtons.size() - scoreScreenButtons.size()*5 ) * (j) + titleDown);
        box->add(scoreScreenButtons.at(j));
    }

    gui.add(box); //Add the box layout to the gui.
}

void StateScoreScreen::loadBackgroundMusic() {
    //Reset the buffer so inloading on 2nd time work as it should.
    backgroundMusic.resetBuffer();

    //Game background music
    if (!backgroundMusicBuffer.loadFromFile("../resources/sounds/score_screen_music.ogg")) {
        std::cout << "backgroundMusicBuffer loads failed" << std::endl;
    }

    backgroundMusic.setBuffer(backgroundMusicBuffer);
}