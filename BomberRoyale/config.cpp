#include <iostream>
#include <regex>
#include <json/json.h>
#include <fstream>
#include "config.h"

Config::Config(){

    //Read in the json settings file
    if (!readFromJson("../jsonobjects/settings.json")){
        std::cout << "Failed to read in the settings json files" << std::endl;
    }

    //Set the box variables
    boxWidth = (int) (screenWidth * boxPercent);
    boxHeight = (int) (screenHeight * boxPercent);
    boxIndentWidth = (int) (screenWidth * boxIndent);
    boxIndentHeight = (int) (screenHeight * boxIndent);

    //####Setup the Graphics####
    //Make the panel it stand on
    auto graphicsScreen = tgui::ScrollablePanel::create(tgui::Vector2f(getBoxWidth(), getBoxHeight() - getDesign().getButtonSizeHeight() - getDesign().getTabsHeight()));
    graphicsScreen->setPosition(0,getDesign().getTabsHeight());
    //graphicsScreen->getRenderer()->setBackgroundColor(sf::Color::Red);
    graphicsScreen->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    graphicsScreen->setVisible(true);
    graphicsScreen->setHorizontalScrollbarPolicy(tgui::ScrollablePanel::ScrollbarPolicy::Never);

    //Setup the graphics screen
    setupGraphics(graphicsScreen);

    //Add the panel to the map for accessing later
    settingsScreens["Graphics"] = graphicsScreen;

    //####Setup the Controls####
    //Make the panel it stand on
    auto controlsScreen = tgui::ScrollablePanel::create(tgui::Vector2f(getBoxWidth(), getBoxHeight() - getDesign().getButtonSizeHeight() - getDesign().getTabsHeight()));
    controlsScreen->setPosition(0,getDesign().getTabsHeight());
    //controlsScreen->getRenderer()->setBackgroundColor(sf::Color::Green);
    graphicsScreen->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    controlsScreen->setVisible(false);
    controlsScreen->setHorizontalScrollbarPolicy(tgui::ScrollablePanel::ScrollbarPolicy::Never);

    //Setup the controls
    setupControl(controlsScreen);

    //Add the panel to the map for accessing later
    settingsScreens["Controls"] = controlsScreen;

    //Setup the Audio
    //Make the panel it stand on
    auto audioScreen = tgui::ScrollablePanel::create(tgui::Vector2f(getBoxWidth(), getBoxHeight() - getDesign().getButtonSizeHeight() - getDesign().getTabsHeight()));
    audioScreen->setPosition(0,getDesign().getTabsHeight());
    //audioScreen->getRenderer()->setBackgroundColor(sf::Color::Yellow);
    graphicsScreen->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    audioScreen->setVisible(false);

    //Setup the audio
    setupAudio(audioScreen);

    //Add the panel to the map for accessing later
    settingsScreens["Audio"] = audioScreen;

    //Set the index to the screen i want
    int i = 0;

    for (auto map : settingsScreens) {
        //What I want to find
        if (map.first == "Graphics"){
            startIndex = i;
        }
        i++;

        //Something else, a helping variable that is used for easier accessing the settings tabs
        settingsNames.emplace_back(map.first);
    }

}

bool Config::readFromJson(std::string path) {
    //Root, value to store the json text in
    Json::Value root;

    //Reader for the file
    Json::Reader reader;

    // Stream used for reading the data file.
    std::ifstream file(path);

    // Read data from file into root objects
    bool parsingSuccessful = reader.parse(file, root);

    // Check for success
    if (!parsingSuccessful) {
        return false;
    }

    //int to know which element you are on
    int i = 0;

    //For each loop. Every objects that is inside highscore
    for (Json::Value& high: root["settings"]) {

        //Game name
        if (root["settings"].getMemberNames().at(i) == "gameName"){
            gameName = high.asCString();
        }
        //Screen width
        else if (root["settings"].getMemberNames().at(i) == "screenWidth"){
            screenWidth = high.asInt();
        }
        //Screen height
        else if (root["settings"].getMemberNames().at(i) == "screenHeight"){
            screenHeight = high.asInt();
        }
        //Screen Mode
        else if (root["settings"].getMemberNames().at(i) == "screenMode"){
            screenModeBool = high.asBool();
        }
        //Volume
        else if (root["settings"].getMemberNames().at(i) == "volume"){
            volume = high.asInt();
        }
        //Mute
        else if (root["settings"].getMemberNames().at(i) == "mute"){
            muteVolume = high.asBool();
        }
        //Enter button
        else if (root["settings"].getMemberNames().at(i) == "enterBtn"){
            enterBtn = (sf::Keyboard::Key) high.asInt();
        }
        //pause button
        else if (root["settings"].getMemberNames().at(i) == "pauseBtn"){
            pauseBtn = (sf::Keyboard::Key) high.asInt();
        }
        //All the player inputs
        else if (root["settings"].getMemberNames().at(i) == "inputs"){

            //loop through every input list
            for (int j = 0; j < root["settings"]["inputs"].getMemberNames().size(); ++j) {

                //A vector to store the keys inn
                std::vector<sf::Keyboard::Key> player;

                //get every key
                player.emplace_back((sf::Keyboard::Key) root["settings"]["inputs"][std::to_string(j)]["up"].asInt());
                player.emplace_back((sf::Keyboard::Key) root["settings"]["inputs"][std::to_string(j)]["left"].asInt());
                player.emplace_back((sf::Keyboard::Key) root["settings"]["inputs"][std::to_string(j)]["down"].asInt());
                player.emplace_back((sf::Keyboard::Key) root["settings"]["inputs"][std::to_string(j)]["right"].asInt());
                player.emplace_back((sf::Keyboard::Key) root["settings"]["inputs"][std::to_string(j)]["bomb"].asInt());

                //Add key vector to the vector of key vectores
                inputList.emplace_back(player);

                //Test code for testing if we get right numbers
                //std::cout << "up: " << player.at(0) << "left: " << player.at(1) << "down: " << player.at(2) << "right: " << player.at(3) << "bomb: " << player.at(4) << std::endl;

                //Set the menu controlling buttons to the player 1s buttons
                if (j == 0){
                    player1LeftBtn = player.at(1);
                    player1RightBtn = player.at(3);
                    player1UpBtn = player.at(0);
                    player1DownBtn = player.at(2);
                    player1BombBtn = player.at(4);
                }
            }
        }

        i++;
    }

    //Set the screen mode based on the bool in the settings json
    if (screenModeBool){
        //Gir error: The requested video mode is not available, switching to a valid mode - feil i biblioteket, sånn vi har forstått det.
        screenMode = sf::Style::Fullscreen;
    }
    else{
        screenMode = sf::Style::Default;
    }

    //Close the file
    file.close();

    return true;
}

void Config::setup(sf::RenderWindow& window, sf::Event& event, tgui::Gui& gui, std::function<int()> settingsButtonFunction) {

    //add background
    auto backgroundPicture = tgui::Picture::create(getDesign().getSettingsBackground());
    gui.add(backgroundPicture);

    //Maybe add a try and catch here for safty check.
    //Make the box layout.
    auto box = tgui::BoxLayout::create(tgui::Layout2d(getBoxWidth(), getBoxHeight()));
    box->setPosition(getBoxIndentWidth(), getBoxIndentHeight());

    //Add the settings screen (panels) to the box layout
    for (auto map : settingsScreens) {
        box->add(map.second, map.first);
    }
    if (!tabsCreated){
        //Add the tabs for every panel.
        tabs->setSize(tgui::Layout2d(getDesign().getTabsWidth(), getDesign().getTabsHeight()));
        tabs->setPosition((getBoxWidth() / 2) - (getDesign().getTabsWidth() / 2), 0);

        //Add the tabs based on how many settingsScreens their is.
        for (auto map : settingsScreens) {
            tabs->add(map.first);
        }

        //Set the selecting the start index
        tabs->select(startIndex);

        tabsCreated = true;
    }

    //Remove the function that is connected to it
    tabs->disconnectAll();

    //Set the select tab function to it.
    //Need to disconnect then connect combo for bug with switching modes.
    tabs->connect("TabSelected", [&]() {
        //Get the selected tab
        std::string selectedTab = getTabPtr()->getSelected();
        std::vector<std::string> names = getSettingsNames();

        for (int i = 0; i < names.size(); ++i) {
            // Check after correct name on the tab you clicked.
            if (selectedTab == names.at(i)) {
                //If it find it then it loop though every panel it should do,
                //and set the correct panel visible and rest not.
                for (int j = 0; j < names.size(); ++j) {
                    gui.get(names.at(j))->setVisible(i == j);
                }
            }
        }

    });

    box->add(tabs);

    connectFunctions(window, event, gui);

    //if buttons vector is empty
    if (buttons.empty()) {
        //Make a button on the bottom.
        auto button = tgui::Button::create();
        getDesign().setButtonDesign(button);
        button->setPosition((getBoxWidth() / 2) - (100 / 2), getBoxHeight() - 40);
        button->setText("Back");

        //Add the widgets to the vector
        buttons.emplace_back(button);
    }

    //Add every button to the box
    for (auto& b : buttons) {
        box->add(b);
    }

    if (buttons.size() == buttonsFunctions.size()){
        buttonsFunctions.at(buttonsFunctions.size()-1) = settingsButtonFunction;
    }
    else {
        //Add the buttons function to the vector
        buttonsFunctions.emplace_back(settingsButtonFunction);
    }
    //Add the function to the button
    buttons.at(buttons.size()-1)->connect("pressed", settingsButtonFunction);

    //Add the box with every element to the gui.
    gui.add(box);
}

void Config::applyChanges(sf::RenderWindow &window) {

    //If graphic changes have happen apply them.
    if (graphicChanged) {
        //Reload the window.
        window.close();
        window.create(sf::VideoMode(getScreenWidth(), getScreenHeight()), getGameName(), getScreenMode());

        graphicChanged = false;
    }

    //Add the buttons numbers writed in the editboxes to the correspending button.
    for (int i = 0; i < controlEditboxes.size(); ++i) {
        std::string keyNumAsText = controlEditboxes.at(i)->getText();
        int keyNum = std::stoi(keyNumAsText);

        if (i == 0) {
            enterBtn = (sf::Keyboard::Key) keyNum;
        }
        else if (i == 1){
            pauseBtn = (sf::Keyboard::Key) keyNum;
        }
        else{
            //TODO Need to merge for fixing this
            int num = i-2;
            int playerNr = num/5; // 5 is hove many buttons
            int buttonNr = num % 5;

            inputList.at(playerNr).at(buttonNr) = (sf::Keyboard::Key) keyNum;
        }
    }

    //TODO Also must make a save function here that correspendig with settings json
    saveToJson("../jsonobjects/settings.json");
}

void Config::saveToJson(std::string path) {
    //Root, value to store the json text in.
    Json::Value root;

    //Add the values to the root file.
    root["settings"]["gameName"] = gameName;
    root["settings"]["screenWidth"] = screenWidth;
    root["settings"]["screenHeight"] = screenHeight;
    root["settings"]["screenMode"] = screenModeBool;

    //Add every input from the input list
    for (int i = 0; i < inputList.size(); ++i) {
        root["settings"]["inputs"][std::to_string(i)]["up"] = inputList.at(i).at(0);
        root["settings"]["inputs"][std::to_string(i)]["left"] = inputList.at(i).at(1);
        root["settings"]["inputs"][std::to_string(i)]["down"] = inputList.at(i).at(2);
        root["settings"]["inputs"][std::to_string(i)]["right"] = inputList.at(i).at(3);
        root["settings"]["inputs"][std::to_string(i)]["bomb"] = inputList.at(i).at(4);
    }

    root["settings"]["volume"] = volume;
    root["settings"]["mute"] = muteVolume;
    root["settings"]["enterBtn"] = enterBtn;
    root["settings"]["pauseBtn"] = pauseBtn;

    //Setting up the write builder
    Json::StreamWriterBuilder wbuilder;

    // Configure the Builder
    std::string outputConfig = Json::writeString(wbuilder, root);

    //The out put stream to file
    std::ofstream streamWriter;
    streamWriter.open(path);
    streamWriter << outputConfig;
    streamWriter.close();
}

void Config::setupGraphics(tgui::ScrollablePanel::Ptr &panel) {
    //The amount of elements in the vertical line.
    // 2 x the object count for better showing if less then 5
    int objectAddedToScreen = 2 * 2;
    // The height on the objects
    int objectsHeight = getDesign().getButtonSizeHeight();
    //clearing between objects on the same line
    int resBoxesClearence = 20;

    //#### Screen Resolution ####
    //Label for displaying screen resolution text
    auto screenResolutionLab = tgui::Label::create("Screen Resolution:");
    screenResolutionLab->setPosition(0, getBoxHeight() / objectAddedToScreen);
    screenResolutionLab->setSize(getBoxWidth(), objectsHeight);
    screenResolutionLab->getRenderer()->setPadding(getDesign().getPadding());
    getDesign().setLabelDesign(screenResolutionLab);
    panel->add(screenResolutionLab);

    //Edit box that will take in the screen width
    screenWidthBox = tgui::EditBox::create();
    screenWidthBox->setPosition(getBoxWidth() / 2, getBoxHeight() / objectAddedToScreen);
    screenWidthBox->setSize(getBoxWidth() / 4 - resBoxesClearence, objectsHeight);
    screenWidthBox->setText(std::to_string(screenWidth));
    panel->add(screenWidthBox);

    //Edit box that will take in the screen width
    screenHeightBox = tgui::EditBox::create();
    screenHeightBox->setPosition(getBoxWidth() / 2 + getBoxWidth() / 4, getBoxHeight()/objectAddedToScreen);
    screenHeightBox->setSize(getBoxWidth() / 4 - resBoxesClearence, objectsHeight);
    screenHeightBox->setText(std::to_string(screenHeight));
    panel->add(screenHeightBox);

    //#### Screen Mode ####
    //Label for displaying screen mode text
    auto screenModeLab = tgui::Label::create("Screen Mode:");
    screenModeLab->setPosition(0, getBoxHeight() / objectAddedToScreen * 2);
    screenModeLab->setSize(getBoxWidth(), objectsHeight);
    screenModeLab->getRenderer()->setPadding(getDesign().getPadding());
    getDesign().setLabelDesign(screenModeLab);
    panel->add(screenModeLab);

    //Check box for choosing the full screen or not
    auto screenModeCheck = tgui::CheckBox::create("Full Screen");
    screenModeCheck->setPosition(getBoxWidth() / 2, (getBoxHeight() / objectAddedToScreen * 2) + getDesign().getPadding());
    screenModeCheck->setChecked(screenModeBool);

    //If checked set full screen
    screenModeCheck->onCheck.connect([&](){
       screenMode = sf::Style::Fullscreen;
       screenModeBool = true;
       graphicChanged = true;
    });

    //If unchecked set default
    screenModeCheck->onUncheck.connect([&](){
        screenMode = sf::Style::Default;
        screenModeBool = false;
        graphicChanged = true;
    });

    panel->add(screenModeCheck);

}

void Config::setupControl(tgui::ScrollablePanel::Ptr &panel) {
    // The height on the objects
    int objectsHeight = getDesign().getButtonSizeHeight();
    //clearing between objects on the same line
    int resBoxesClearence = 30;

    //#### Enter button ####
    //Label for displaying the text for the enter editbox
    auto controlsEnterLab = tgui::Label::create("Enter Button:");
    controlsEnterLab->setPosition(0, getBoxHeight() * 0.1);
    controlsEnterLab->setSize(getBoxWidth() / 4 + resBoxesClearence, objectsHeight);
    controlsEnterLab->getRenderer()->setPadding(getDesign().getPadding());
    getDesign().setLabelDesign(controlsEnterLab);
    panel->add(controlsEnterLab);

    //Edit box for the enter menu
    auto controlsEnterBox = tgui::EditBox::create();
    controlsEnterBox->setPosition(getBoxWidth() / 4, getBoxHeight() * 0.1);
    controlsEnterBox->setSize(getBoxWidth() / 4 - resBoxesClearence, objectsHeight);
    controlsEnterBox->setText(std::to_string(getEnterBtn()));
    panel->add(controlsEnterBox, "Enter");

    //Add the editbox to the vector that should own every editbox
    controlEditboxes.emplace_back(controlsEnterBox);

    //#### Pause button ####
    //The label for the pause edit box
    auto controlsPauseLab = tgui::Label::create("Pause Button:");
    controlsPauseLab->setPosition(getBoxWidth() / 4 * 2, getBoxHeight() * 0.1);
    controlsPauseLab->setSize(getBoxWidth() / 4 + resBoxesClearence, objectsHeight);
    controlsPauseLab->getRenderer()->setPadding(getDesign().getPadding());
    getDesign().setLabelDesign(controlsPauseLab);
    panel->add(controlsPauseLab);

    //The editbox for the pause button
    auto controlsPauseBox = tgui::EditBox::create();
    controlsPauseBox->setPosition(getBoxWidth() / 4 * 3,getBoxHeight() * 0.1);
    controlsPauseBox->setSize(getBoxWidth() / 4 - resBoxesClearence, objectsHeight);
    controlsPauseBox->setText(std::to_string(getPauseBtn()));
    panel->add(controlsPauseBox);

    //Add the editbox to the vector that should own every editbox
    controlEditboxes.emplace_back(controlsPauseBox);

    //#### Player Buttons ####
    //Buttons names - test one for now to the config is saved in a vector - will be changed when we read in
    std::vector<std::string> buttonsPlayers {"Up", "Left", "Down", "Right", "Bomb"};

    //Add every button name to a label and add it to panel
    for (int i = 0; i < buttonsPlayers.size(); ++i) {
        auto playerButtonsNames = tgui::Label::create(buttonsPlayers.at(i));
        playerButtonsNames->setPosition(getBoxWidth() / 6 * (i + 1), getBoxHeight() * 0.3);
        playerButtonsNames->setSize(getBoxWidth() / 6, objectsHeight);
        getDesign().setLabelDesign(playerButtonsNames);
        panel->add(playerButtonsNames);
    }

    //TODO Make it so it place them on what is need, needd to merge first
    //The player numbers should also be a read in from the config file - maybe?
    int antallPlayers = 4;

    for (int k = 0; k < antallPlayers; ++k) {

        //Add player nr
        auto player = tgui::Label::create("P" + std::to_string(k+1));
        player->setPosition(0, getBoxHeight() * ((float) k / 10 + 0.4));
        player->setSize(getBoxWidth() / 6, objectsHeight);
        player->getRenderer()->setPadding(getDesign().getPadding());
        getDesign().setLabelDesign(player);
        panel->add(player);

        //Add a box per button on the player(s)
        for (int j = 0; j < buttonsPlayers.size(); ++j) {
            auto playerButtonBox = tgui::EditBox::create();
            playerButtonBox->setPosition(getBoxWidth() / 6 * (j + 1), getBoxHeight() * ((float) k/10 + 0.4));
            playerButtonBox->setSize(getBoxWidth() / 6-resBoxesClearence, objectsHeight);
            playerButtonBox->setText(std::to_string(inputList.at(k).at(j)));
            panel->add(playerButtonBox, "Pl");

            //Add the editbox to the vector that should own every editbox
            controlEditboxes.emplace_back(playerButtonBox);
        }
    }
}

void Config::setupAudio(tgui::ScrollablePanel::Ptr &panel) {
    //The amount of elements in the vertical line.
    // 2 x the object count for better showing if less then 5
    int objectAddedToScreen = 2 * 2;
    // The height on the objects
    int objectsHeight = getDesign().getButtonSizeHeight();

    //#### Sound Volume ####
    auto audioVolumeLab = tgui::Label::create("Screen Volume:");
    audioVolumeLab->setPosition(0, getBoxHeight() / objectAddedToScreen);
    audioVolumeLab->setSize(getBoxWidth(), objectsHeight);
    audioVolumeLab->getRenderer()->setPadding(getDesign().getPadding());
    getDesign().setLabelDesign(audioVolumeLab);
    panel->add(audioVolumeLab);

    audioVolumeSlider = tgui::Slider::create(0,10);
    audioVolumeSlider->setValue(volume);
    audioVolumeSlider->setPosition(getBoxWidth() / 2, getBoxHeight() / objectAddedToScreen);
    audioVolumeSlider->setSize(getBoxWidth()/2-20, objectsHeight/2); // -20 just so it is all showed.
    audioVolumeSlider->setStep(1);
    audioVolumeSlider->onValueChange.connect([&](){
        volume = (int) audioVolumeSlider->getValue();

    });
    panel->add(audioVolumeSlider);



    //#### Sound mute ####
    //Label for displaying screen mode text
    auto audioMuteLab = tgui::Label::create("Audio Mode:");
    audioMuteLab->setPosition(0, getBoxHeight() / objectAddedToScreen * 2);
    audioMuteLab->setSize(getBoxWidth(), objectsHeight);
    audioMuteLab->getRenderer()->setPadding(getDesign().getPadding());
    getDesign().setLabelDesign(audioMuteLab);
    panel->add(audioMuteLab);

    //Check box for choosing the mute or not
    auto audioMuteCheck = tgui::CheckBox::create("Mute");
    audioMuteCheck->setPosition(getBoxWidth() / 2, (getBoxHeight() / objectAddedToScreen * 2) + getDesign().getPadding());
    audioMuteCheck->setChecked(muteVolume);

    //If checked set full screen
    audioMuteCheck->onCheck.connect([&](){
        muteVolume = true;
    });

    //If unchecked set default
    audioMuteCheck->onUncheck.connect([&](){
        muteVolume = false;
    });

    panel->add(audioMuteCheck);

}

void Config::connectFunctions(sf::RenderWindow& window, sf::Event& event, tgui::Gui& gui) {
    // #### Graphics ####
    //The function for screen width box
    screenWidthBox->onTextChange.connect([&](){
        try {
            //Get the text in the box at the moment
            std::string str = screenWidthBox->getText();

            //A regex over what we want to remove from it.
            std::regex regex("[a-zA-z]");

            //Check the string remove everything that is not in the regex
            str = std::regex_replace(str, regex, "");

            //Set the screen width
            screenWidth = std::stoi(str);

            //Set that a change have happen
            graphicChanged = true;
        }
        catch (...){}
    });


    //The function for screen height box
    screenHeightBox->onTextChange.connect([&](){
        try {
            //Get the text in the box at the moment
            std::string str = screenHeightBox->getText();

            //A regex over what we want to remove from it.
            std::regex regex("[a-zA-z]");

            //Check the string remove everything that is not in the regex
            str = std::regex_replace(str, regex, "");

            //Set the screen width
            screenHeight = std::stoi(str);

            //Set that a change have happen
            graphicChanged = true;
        }
        catch (...){}
    });

    //Add the function to every button in the editbox vector
    for (auto& editbox : controlEditboxes) {
        //Remove the function it had.
        editbox->onMousePress.disconnectAll();

        //Add the function on new.
        editbox->onMousePress.connect([&]() {

            //Set the color at the editbox that show it wait for a button click
            editbox->getRenderer()->setBackgroundColor(sf::Color::Blue);
            gui.draw();
            window.display();

            //While we wait for a button click
            while (event.type != event.KeyReleased) {
                //Update the event to the current event
                window.pollEvent(event);

                //Set the edit box to the button pressed.
                editbox->setText(std::to_string(event.key.code));

            }

            //Set the color back to standard
            editbox->getRenderer()->setBackgroundColor(sf::Color::White);
            gui.draw();
            window.display();

            //Set that it is waiting for a button click
            settingsWaitingForButton = true;

        });

    }
}