#ifndef BOMBER_ROYALE_STATEDATA_H
#define BOMBER_ROYALE_STATEDATA_H

#include <string>

class StateData{
public:
    //TODO: implement a constructer and deconstructer for this class

    /**
     * Get the modified data string.
     * @return a string of when the data is modified
     */
    virtual std::string getModifiedData(){
        return modifidedDate;
    };

    /**
     * Set modified data string to the current time
     */
    virtual void setModifidData(){
        //TODO: Implement this function.
        //Also probably move this to a logger function
        //And probably make a change detection that call the function
        // Make it so it take now time and add it to the string
    }
    /**
     * Get if it is the first round
     * @return a bool if it is first round
     */
    virtual bool isFirstRound(){
        return firstRound;
    }
    /**
     * Set the first round
     * @param fr is a bool that set if it is first round
     */
    virtual bool setFirstRound(bool fr){
        firstRound = fr;
    }

protected:
    //A string when the data is modified
    std::string modifidedDate;

    //A bool over if it is first round.
    bool firstRound = true;

};

#endif //BOMBER_ROYALE_STATEDATA_H
