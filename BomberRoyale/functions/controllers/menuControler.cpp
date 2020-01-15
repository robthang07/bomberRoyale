#include <iostream>
#include "menuControler.h"

int MenuControler::eventHandler(Config &config, sf::Event &event,
                                 std::vector<tgui::Button::Ptr> &buttons, std::vector<std::function<int()>> &functions, bool singleLined) {

    int menuSize =  buttons.size();

    //This check for if we dont get buttons or functions
    if (buttons.empty() || functions.empty()){
        return 1; //This is a error because something is wrong. This fix make it work but not tell us the reason
    }

    //if index is 0 we just started selecting so we set it to green.
    if (index == 0){
        buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getSelectedButtonColor());
    }

    //Check if the menu is in a single lined downward.
    if (!singleLined) {

        //Move the index where it should when you push UP
        if (event.type == sf::Event::KeyReleased && event.key.code == config.getPlayer1UpBtn() && index > 1) {
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getButtonColor());
            index -= 2;
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getSelectedButtonColor());
        }

        //Move the index where it should when you push Down
        if (event.type == sf::Event::KeyReleased && event.key.code == config.getPlayer1DownBtn() && index < menuSize-2){
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getButtonColor());
            index += 2;
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getSelectedButtonColor());
        }

        //Move the index where it should when you push Left
        if (event.type == sf::Event::KeyReleased && event.key.code == config.getPlayer1LeftBtn() && index > 0){
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getButtonColor());
            index -= 1;
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getSelectedButtonColor());
        }
        //Move the index where it should when you push Top
        if (event.type == sf::Event::KeyReleased && event.key.code == config.getPlayer1RightBtn() && index < menuSize-1){
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getButtonColor());
            index += 1;
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getSelectedButtonColor());
        }
    }
    //If the menu is only in one line
    else{
        //Move the index where it should when you push UP
        if (event.type == sf::Event::KeyReleased && event.key.code == config.getPlayer1UpBtn() && index > 0) {
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getButtonColor());
            index -= 1;
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getSelectedButtonColor());
        }

        //Move the index where it should when you push Down
        if (event.type == sf::Event::KeyReleased && event.key.code == config.getPlayer1DownBtn() && index < menuSize-1){
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getButtonColor());
            index += 1;
            buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getSelectedButtonColor());
        }

    }
    //If the user press Enter
    if (event.type == sf::Event::KeyReleased && event.key.code == config.getEnterBtn()){
        buttons.at(index)->getRenderer()->setBackgroundColor(config.getDesign().getButtonColor());
        int funcReturn = functions.at(index).operator()();
        index = 0;
        return funcReturn;
    }

    //Adding the color to the btn color var
    btnColor = config.getDesign().getButtonColor();

    //Remove the func
    for (auto& btn : buttons){btn->onMousePress.disconnectAll();}

    //Implementing the function to every button
    for (int i = 0; i < buttons.size(); ++i) {
      buttons.at(i)->onMousePress.connect([&](){
          //Take every button and set to normal button color
          for(auto b: buttons){
              b->getRenderer()->setBackgroundColor(btnColor);
          }
          //Set index to 0 because we move to a next menu
          index = 0;
      });
    }



    return 1;
}