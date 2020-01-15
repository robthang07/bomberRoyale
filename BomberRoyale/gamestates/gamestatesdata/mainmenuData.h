#ifndef BOMBER_ROYALE_MAINMENUDATA_H
#define BOMBER_ROYALE_MAINMENUDATA_H

#include <SFML/Graphics.hpp>
#include "stateData.h"

class MainMenuData : public StateData {
public:

    /**
     * Constructor for this class, adds menu elements
     * needed to the menuElements vector
     */
    MainMenuData();


    /**
     * Destructor to remove all elements in vector
     */
    ~MainMenuData();


    /**
     * Vector which stores strings of menu elements
     * needed in the main menu
     * @return pointer of vectors of strings
     */
    std::vector<std::string>* getMenuElementsPtr(){
        return &menuElements;
    }

protected:
    //TODO: Add data main menu need here

    //Vector to store menu elements in string
    std::vector<std::string> menuElements;

};

#endif //BOMBER_ROYALE_MAINMENUDATA_H
