#ifndef BOMBER_ROYALE_SCORESCREENDATA_H
#define BOMBER_ROYALE_SCORESCREENDATA_H

#include <vector>
#include "stateData.h"

class ScorescreenData : public StateData {
public:
    // Constructor
    ScorescreenData();


    //Destructor to remove all elements in vector
    ~ScorescreenData();


    /**
     * A getter function for score elements
     * @return the score screen elements in vector
     */
    std::vector<std::string>* getScoreElementsPtr() {
        return &scoreScreenElements;
    }


    /**
     * Getter function for player's score when game ends
     * @return score data which store the points
     * the player got in the game
     */
    int getScore(){
        return scoreData;
    }

    /**
     * Setter function update the player's score in game
     * @param score data which saves the current points
     * the player has gotten so far
     */
    void setScore(int score){
        this->scoreData = score;
    }

    /**
     * Set the player status to winner.
     * @param playerNumber is the number on the player
     */
    void setPlayerStatusToWinner(int playerNumber){
        winner = true;
        draw = false;
        playerNumberOfWinner = playerNumber;
    }

    /**
     * Set the player status to draw.
     */
    void setPlayerStatusToDraw(){
        winner = false;
        draw = true;
    }

    /**
     * Set the player status to lost.
     */
    void setPlayerStatusToLost(){
        winner = false;
        draw = false;
    }

    /**
     * Get if it is a draw.
     * @return a bool for draw, true == draw.
     */
    bool getDraw(){
        return draw;
    }

    /**
     * Get if it is a a winner.
     * @return a bool for draw, true == a winner.
     */
    bool getWinner(){
        return winner;
    }

    /**
     * Get the winners player number
     * @return a int with the number of the player.
     */
    int getWinnerPlayerNum(){
        return playerNumberOfWinner;
    }

protected:

    //Vector with the scorescreen buttons names
    std::vector<std::string> scoreScreenElements;

    //The score the player that won has.
    long int scoreData;

    //Player status variable
    bool winner;
    bool draw;
    int playerNumberOfWinner;
};


#endif //BOMBER_ROYALE_SCORESCREENDATA_H
