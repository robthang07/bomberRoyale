#include <iostream>
#include <memory>
#include <SFML/Window.hpp>
#include "stateGameScreen.h"
#include "machine.h"
#include "../layers/map.h"
#include "../layers/layers.h"
#include "../objects/object.h"
#include "../objects/sprite.h"
#include "../functions/detectors/collision.h"
#include "../functions/calculators/bombPlacement.h"
#include "../functions/scoresystem/scoreSystem.h"
#include "stateScoreScreen.h"
#include "../jsonobjects/highscores.h"

StateGameScreen::StateGameScreen(){
    //Load the map in
    loadMap();

    // Loads background music from HDD to RAM
    loadBackgroundMusic();
};


StateGameScreen::~StateGameScreen() {
    //Clear the objects list
    objects.clear();
    //Clear the walls list
    walls.clear();
    //Clear the powerups list
    powerups.clear();
    //Clear the player list
    players.clear();
}


int StateGameScreen::run(Machine &machine, sf::RenderWindow &window, Config& config, float deltaTime) {

    //A event object os
    sf::Event event{};

    // Process events from the OS
    while (window.pollEvent(event))
    {
        //make it so it is either only switch statment or only if statments.
        switch (event.type)
        {
            //If window is closed
            case sf::Event::Closed:
                window.close();
                return 0;

            //If the key is released
            case sf::Event::KeyReleased:
                // Reload map on F5
                if (event.key.code == sf::Keyboard::F5) {
                    //Load the map in
                    loadMap();
                }
                break;

            case sf::Event::KeyPressed:
                //maybe change this to relased, or do something so players can hold space,
                for(auto& p : players) {
                    //Check if the is dead
                    // this key will need this if you take it inside the player
                    if (!p->getDead()) {
                    if (sf::Keyboard::isKeyPressed(p->getPlayerInput()[p->getPlayerInput().size() - 1]) && p->getIsPlayer()) {

                            bool bombOnSamePlace = false;

                            auto bombUnderPlayer = bombPlacement::CheckBombPlacment(p, config);

                            for (auto &dp : players) {
                                for (auto &b : dp->getBombs()) {
                                    if (b->getX() == bombUnderPlayer.x && b->getY() == bombUnderPlayer.y) {
                                        bombOnSamePlace = true;
                                    }
                                }
                            }

                            if (p->getBombs().size() >= p->getMaxBomb() || bombOnSamePlace) {
                                // std::cout<<"Too many bombs"<<std::endl;
                            } else {
                                //Bomb placement
                                bombPlacement::Bombplacement(p, p->getBombs(), config);
                            }
                        }
                    }
                }


                //Check if pause button is pressed
                if (sf::Keyboard::isKeyPressed(config.getPauseBtn())) {
                    machine.setState(Machine::stateID::PauseScreen);

                    if (!config.isVolumeMuted()) {
                        backgroundMusic.pause();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
                    for (auto& p : players){
                        if (p->getPlayerNumber() != 0){
                            p->setDead();
                        }
                    }
                }
                break;

            default:
                // Ignore the other events
                break;

        }
    }
    //Clear the window with a black color
    window.clear(sf::Color::Black);


    //If first round do this
    if (gamescreenData.isFirstRound()) {

        if (!config.isVolumeMuted()) {
            loadBackgroundMusic();

            //To repeat music when is playied once
            backgroundMusic.setLoop(true);

            //Dived by 10 to reduce background music volume so vi hear sound effect such as explosion
            backgroundMusic.setVolume((config.getVolume()) / 10);

            //Playes the background music
            backgroundMusic.play();
        }

        players.clear();

        //create 1 player and 3 bots if you hit single player
        if (gamescreenData.getSinglePlayer()) {

            players.emplace_back(std::make_shared<Player>(config));

            auto listAI = new std::list<std::shared_ptr<BaseAI>>;

                for (int i = 0; i < 3; ++i) {

                    auto bi = std::make_shared<BaseAI>();
                    players.emplace_back(bi);
                    listAI->emplace_back(bi);
                }

                //Do something
                for( auto& AI : *listAI){
                    AI->setPlayerList(players);
                }

            }

            //create 2 players and 2 bots if you hit multiplayer
        else {
                auto listAI = new std::list<std::shared_ptr<BaseAI>>;
                for (int i = 0; i < 2; ++i) {
                    players.emplace_back(std::make_shared<Player>(config));
                }

                for (int i = 0; i < 2; ++i) {
                    auto bi = std::make_shared<BaseAI>();
                    players.emplace_back(bi);
                    listAI->emplace_back(bi);
                }
                for( auto& AI: *listAI){
                    AI->setPlayerList(players);
                }
            }

        //Load the map in
        loadMap();

        //User interface, setup or update
        setupUserInterface(window, config);
        //set first round to false
        gamescreenData.setFirstRound(false);
    }

    else {
        //Update the User Interface
        updateUserInterface(window, deltaTime);
    }

    //When retruning from pause screen
    if (gamescreenData.getReturnedToGame()){

        if (!config.isVolumeMuted()) {
            backgroundMusic.setVolume(config.getVolume());
            backgroundMusic.play();
        }
        gamescreenData.setReturnedToGame(false);
    }

    //Add the player inputs to the right player when settings changed.
    if (gamescreenData.getSettingsChanged()){
        for(auto& p : players){
           p->setPlayerInput(config.getInputs(p->getPlayerNumber()));
        }
    }

    for ( auto &AI : players) {
        if (!AI->getDead()) {
            if (!AI->getIsPlayer()) {

                bool bombOnSamePlace = false;

                auto bombUnderPlayer = bombPlacement::CheckBombPlacment(AI, config);

                for (auto &dp : players) {
                    for (auto &b : dp->getBombs()) {
                        if (b->getX() == bombUnderPlayer.x && b->getY() == bombUnderPlayer.y) {
                            bombOnSamePlace = true;
                        }
                    }
                }

                if (AI->getBombs().size() >= AI->getMaxBomb() || bombOnSamePlace) {
                    // std::cout<<"Too many bombs"<<std::endl;
                } else {
                    //Bomb placement
                    bombPlacement::Bombplacement(AI, AI->getBombs(), config);


                }
            }
        }
    }

    //BaseAI::findDirection(players);

    //A for loop that go through every object
    for (auto& object : objects) {
        //Process object
        object->process(deltaTime);
        //Draw object
        object->draw(window, config);

        //Cast the object to a rectShape so we can use it with intersect
        std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(object);

        //Check for collision between player and objects which are now sprites
       for(auto &p : players) {
           if (!p->getDead()) {
               collision1.Detection(p, sprite, config);
           }
       }
    }

    //A for loop that go through every wall
    for (auto& wall : walls){
        //Process object
        wall->process(deltaTime);

        wall->draw(window,config);
        //Cast the object to a rectShape so we can use it with intersect
        std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(wall);

        //Check for collision between player and objects which are now sprites
        for(auto &p : players) {
            if (!p->getDead()) {
                collision1.Detection(p, sprite, config);
            }
        }
    }

    //int that check if one player is left
    int playersLeft = 0;

    //Check if the bomb it want to remove is in after each other and not jumping to what ever
    bool stopedRemovingInRow;

    //Bombs to remove in a vector
    std::vector<std::shared_ptr<Bomb>> bombsToRemove;

    //run through each payer to draw their respective bombs
    for(auto &p : players) {

        //Reset the variables for checking each player
        stopedRemovingInRow = false;
        bombsToRemove.clear();

        //draw all the bombs and remove the bomb.
        for (auto &o : p->getBombs()) {

            //Move the bomb
            o->Move();

            //if the bomb is tagged for the removing
            if (o->checkFlagedForRemoving() && !stopedRemovingInRow) {
                //remove the bomb
                bombsToRemove.emplace_back(o);
            }
            else {
                //Since we now draw it, we are not removing it.
                stopedRemovingInRow = true;
                //Draw the bomb
                o->Draw(window);
                //Check if the bomb has exploded
                for (auto& currentP : players) {
                    //If player is not the current player
                    if (p != currentP) {
                        //Take in every player inn for checking if them is in the explosion range.
                        o->checkForExplosion(window, deltaTime, objects, walls, *p, *currentP, powerups,config);
                    }
                }
            }
        }

        for (auto& rem : bombsToRemove){
            p->getBombs().remove(rem);
        }

        //If player not dead do something with it
        if (!p->getDead()) {
            //Move the character
            p->Move(deltaTime);

            //Draw the character
            p->Draw(window);

            //Add being alive score per sec to the player
            ScoreSystem::addBeingAlivePerSecScore(*p, deltaTime);

            //Add one for every not dead player
            playersLeft++;
        }

    }

    //stores what to remove, then removes them after
    std::list<std::shared_ptr<BasePowerUps>> removeListForPowerups;

    //draw all the powerups
    for (auto& po : powerups){
        po->Draw(window);

        //see for every player if they have picked up any powerups
        for(auto& p : players) {
            if (p->getRectangleShape().getGlobalBounds().intersects(po->getSprite().getGlobalBounds())) {
                //If picked up modify the player with that power
                po->modifyPlayer(p);
                //Add the power up for removal since used up.
                removeListForPowerups.emplace_back(po);
                //Since the player picked it up add the score for picking up a power up
                ScoreSystem::addPickingPowerupsScore(*p);
            }
        }
    }
    //remove all added power ups
    for (auto& rem : removeListForPowerups){
        powerups.remove(rem);
    }

    //Check if the game is done
    if (playersLeft <= 1 || timer <= 0){
        //Stop the music
        backgroundMusic.pause();

        //1 player won or lost
        if (playersLeft == 1) {
            for (auto &p : players) {
                if (!p->getDead()) {

                    //Add the scores you get for winning the game
                    ScoreSystem::addScoresToWinner(*p, timer);

                    //Set the machine to score screen since game is over
                    machine.setState(Machine::stateID::ScoreScreen);

                    //Set the score and first round data for the score screen
                    auto scoreData = (ScorescreenData *) machine.getStateData();
                    scoreData->setScore(p->getScore());
                    scoreData->setFirstRound(true);

                    //Check if the player won or lost
                    if (gamescreenData.getSinglePlayer()){
                        if (p->getPlayerNumber() == 0){
                            scoreData->setPlayerStatusToWinner(p->getPlayerNumber());
                        }
                        else{
                            scoreData->setPlayerStatusToLost();
                        }
                    }
                    else{
                        //Will need to fix this to work with config number for number of players
                        if (p->getPlayerNumber() == 0 || p->getPlayerNumber() == 1){
                            scoreData->setPlayerStatusToWinner(p->getPlayerNumber());
                        }
                        else{
                            scoreData->setPlayerStatusToLost();
                        }
                    }

                    // If the player winner do this
                    if (scoreData->getWinner()) {

                        //Save the highscore if better then the 10 saved.
                        Highscores highscores;

                        //Read the file
                        if (highscores.readFromJson("../jsonobjects/highscore.json")) {

                            //Get out the scores.
                            auto scores = highscores.getHighScores();

                            //Check if the score of the playeer is bigger then the lowest score or if all scores is not filed in.
                            if (p->getScore() > (long int) std::stoi(scores.at(scores.size() - 1)->score) ||
                                scores.size() < highscores.getCapOnStored()) {

                                //A iterator we use to access the correct score.
                                auto it = scores.begin();

                                //Get the number of the highest score it is better then from the top
                                for (int i = 0; i < scores.size(); ++i) {
                                    //If the score is lower then the player score break it, because we found it.
                                    if (std::stoi(scores.at(i)->score) < p->getScore()) {
                                        break;
                                    }
                                    //Advance the iterater by one to we get the higheste number it is bigger then
                                    std::advance(it, 1);
                                }

                                //Only do this if the list is fulled out
                                if (scores.size() == highscores.getCapOnStored()) {
                                    //Erase the highest one it is bigger then.
                                    scores.erase(it);
                                }

                                //Get raw time
                                time_t rawtime;
                                //Stuct pointer to the time struct
                                struct tm * timeinfo;
                                //A char buffer to store values from
                                char buffer[80];

                                //Take raw time and set it to the time and date we want.
                                time (&rawtime);
                                timeinfo = localtime(&rawtime);

                                //Formate it and save it to a string
                                strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
                                std::string str(buffer);

                                //Make a new element and set it in on the same posision
                                Highscores::stats stats;
                                stats.name = str;
                                stats.score = std::to_string(p->getScore());

                                //Set it in in the list on the position we want
                                scores.insert(it, &stats);

                                //Set the scores we have changed on back again
                                highscores.setHighscores(scores);

                                //Write the new scores to the json file
                                highscores.writeToJson("../jsonobjects/highscore.json");

                            }
                        }
                    }
                }
            }
        }
        //Draw
        else{
            //Set the machine to score screen since game is over
            machine.setState(Machine::stateID::ScoreScreen);

            //Set the score and first round data for the score screen
            auto scoreData = (ScorescreenData *) machine.getStateData();
            scoreData->setScore(0);
            scoreData->setFirstRound(true);
            scoreData->setPlayerStatusToDraw();
        }
    }

    //Display what is on the window
    window.display();

    return 1;
}

void StateGameScreen::setupUserInterface(sf::RenderWindow &window, Config &config) {

    //Colors for the player gui
    sf::Color p1guiColor = sf::Color(56,35,71);
    sf::Color p2guiColor = sf::Color(218,141,8);
    sf::Color p3guiColor = sf::Color::Blue;
    sf::Color p4guiColor = sf::Color::Red;

    //Set the target that get the gui
    gui.setTarget(window);

    //Clear it so it work on rematch and mode switch
    gui.removeAllWidgets();

    //Set timer to resetTime when rematch or mode switch happend
    timer = resetTime;

    //Make a box to contain the gui in.
    auto box = tgui::BoxLayout::create();
    box->setPosition(0, 0);
    box->setSize(config.getScreenWidth(), config.getBoxIndentHeight());
    gui.add(box);

    //Make the timer label
    //Need "00:00" for getting right size. It is only a placeholder
    timerGui = tgui::Label::create("00:00");
    config.getDesign().setLabelDesign(timerGui);
    timerGui->setPosition((config.getScreenWidth() / 2) - (timerGui->getSize().x / 2), 0);
    box->add(timerGui);

    //Clear the player score so it is will run correctly after switching mode
    playerScoresGui.clear();

    //make player 1 label
    auto player1GUI = tgui::Label::create();
    player1GUI->setPosition(config.getBoxIndentWidth(), config.getBoxIndentHeight() / 2);
    player1GUI->setSize(tgui::Layout2d(config.getBoxWidth() / 2, config.getBoxIndentHeight() / 2));
    config.getDesign().setLabelDesign(player1GUI);
    player1GUI->getRenderer()->setBackgroundColor(p1guiColor);
    box->add(player1GUI);

    //add it to the score vector
    playerScoresGui.push_back(player1GUI);

    //make player 2 label
    auto player2GUI = tgui::Label::create();
    player2GUI->setPosition(config.getScreenWidth() / 2, config.getBoxIndentHeight() / 2);
    player2GUI->setSize(tgui::Layout2d(config.getBoxWidth() / 2, config.getBoxIndentHeight() / 2));
    config.getDesign().setLabelDesign(player2GUI);
    player2GUI->getRenderer()->setBackgroundColor(p2guiColor);
    box->add(player2GUI);

    //add it to the score vector
    playerScoresGui.push_back(player2GUI);

    //make player 3 label
    auto player3GUI = tgui::Label::create();
    player3GUI->setPosition(config.getBoxIndentWidth(), config.getBoxHeight() + config.getBoxIndentHeight());
    player3GUI->setSize(tgui::Layout2d(config.getBoxWidth() / 2, config.getBoxIndentHeight() / 2));
    config.getDesign().setLabelDesign(player3GUI);
    player3GUI->getRenderer()->setBackgroundColor(p3guiColor);
    gui.add(player3GUI);

    //add it to the score vector
    playerScoresGui.push_back(player3GUI);

    //make player 4 label
    auto player4GUI = tgui::Label::create();
    player4GUI->setPosition(config.getScreenWidth() / 2, config.getBoxHeight() + config.getBoxIndentHeight());
    player4GUI->setSize(tgui::Layout2d(config.getBoxWidth() / 2, config.getBoxIndentHeight() / 2));
    config.getDesign().setLabelDesign(player4GUI);
    player4GUI->getRenderer()->setBackgroundColor(p4guiColor);
    gui.add(player4GUI);

    //add it to the score vector
    playerScoresGui.push_back(player4GUI);

    //Draw the gui
    gui.draw();

}

void StateGameScreen::updateUserInterface(sf::RenderWindow &window, float deltaTime) {

    //#### Time ####

    //Adding the time to the timer.
    timer -= deltaTime;

    //Taking the time the timer is giving in sec and make it work with min
    int timeInSec = (int) timer;
    int timeInMin = 0;

    //Every time it more then 60 sec add a min to the time and remove 60 sec
    while (timeInSec >= 60) {
        timeInSec -= 60;
        timeInMin++;
    }

    //formatting the time so it is shown as a normal timer
    std::string time = "";

    //Add zeroes so it is 2 numbers in both places
    if (timeInMin < 10) { time += "0"; }
    time += std::to_string(timeInMin);
    time += ":";
    if (timeInSec < 10) { time += "0"; }
    time += std::to_string(timeInSec);

    //Set the formatted time on the label
    timerGui->setText(time);

    //#### Score ####
    //Add the score to the players

    int i = 0;
    for (auto &p : players){
        //If It is a player
        if ((!gamescreenData.getSinglePlayer() && i<=1) || i == 0) {
            playerScoresGui.at(i)->setText(
                    "|P" + std::to_string(i+1) + "| Hp: " + std::to_string(p->getHp())
                    + " Score: " + std::to_string(p->getScore()));
        }
        //else it is a AI
        else {
            //Add the score to the 2 player.
            playerScoresGui.at(i)->setText(
                    "|AI" + std::to_string(i+1) + "| Hp: " + std::to_string(p->getHp())
                    + " Score: " + std::to_string(p->getScore()));
        }
        i++;
    }
    gui.draw();

}

void StateGameScreen::loadMap() {
    //Clear the objects list
    objects.clear();
    //Clear the walls list
    walls.clear();
    //Clear the powerup list
    powerups.clear();

    // Load map information from JSON into object list
    if (!map.loadFromFile("../map/newmap.json")) {
        std::cout << "Failed to load map data." << std::endl;
    }

    // Move objects from map object to Game list
    objects.splice(objects.begin(), map.getObjects());

    // Move walls from map walls to Game list
    walls.splice(walls.begin(), map.getWalls());
}

void StateGameScreen::loadBackgroundMusic() {
    //Reset the buffer so inloading on 2nd time work as it should.
    backgroundMusic.resetBuffer();

    //Game background music
    if (!backgroundMusicBuffer.loadFromFile("../resources/sounds/background_music.ogg")) {
        std::cout << "backgroundMusicBuffer loads failed" << std::endl;
    }

    backgroundMusic.setBuffer(backgroundMusicBuffer);
}