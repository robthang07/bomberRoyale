#ifndef BOMBER_ROYALE_MENUCONTROLER_H
#define BOMBER_ROYALE_MENUCONTROLER_H


#include "../../config.h"

class MenuControler {
public:
    /**
     * Is handling the event on selecting menu
     * @param config is the settings object that we are getting information from.
     * @param event is a object of the events that have happening.
     * @param buttons is a vector of buttons pointer to the current menu.
     * @param functions is a vector of lambdas to the currrent menu.
     * @param singleLined is bool that say if it is a single lined menu or dual line menu.
     * @return It returns a int based on witch error code it is giving.
     */
    int eventHandler(Config& config, sf::Event& event, std::vector<tgui::Button::Ptr> &buttons, std::vector<std::function<int()>> &functions, bool singleLined);

protected:
    //The index on witch menu element it is selecting.
    int index = 0;
    sf::Color btnColor;
};


#endif //BOMBER_ROYALE_MENUCONTROLER_H
