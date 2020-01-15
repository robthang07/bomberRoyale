#include <iostream>
#include "mainmenuData.h"


//Constructor
MainMenuData::MainMenuData() {

    //Adding menu elements
    menuElements.emplace_back("Single Player");
    menuElements.emplace_back("MultiPlayer");
    menuElements.emplace_back("High score");
    menuElements.emplace_back("Settings");
    menuElements.emplace_back("Credits");
    menuElements.emplace_back("Exit");

}

MainMenuData::~MainMenuData() {

    //Clear the vector
    menuElements.clear();

}
