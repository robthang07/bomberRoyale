#ifndef BOMBER_ROYALE_PAUSESCREENDATA_H
#define BOMBER_ROYALE_PAUSESCREENDATA_H

#include <vector>
#include "stateData.h"

class PausescreenData : public StateData {
public:
    //TODO: implement a constructer, deconstructer, getter, setteer for this class
    /**
     * Default constructor with no parameters that adds some elements to the pausescreen class
     */
    PausescreenData();

    /**
     * getter for pointer of string vector that returns the different elements
     * @return the 3 eleements in the string vector
     */
    std::vector<std::string>* getPauseElementsPtr(){
        return &pauseScreenElements;
    }

protected:
    //TODO: Add data pause screen need here
    //vector of strings that are used to set the names of the buttons in the pause screen
    std::vector<std::string> pauseScreenElements;
};


#endif //BOMBER_ROYALE_PAUSESCREENDATA_H
