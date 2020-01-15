#ifndef BOMBER_ROYALE_HIGHSCORE_H
#define BOMBER_ROYALE_HIGHSCORE_H

#include <string>
#include <vector>


class Highscores {
public:
    /**
     * A stats struct that containt the stats need to save
     */
    struct stats
    {
        std::string name;
        std::string score;
    };

    /**
     * Destructor is deleting the highscores that is saved.
     */
    ~Highscores();

    /**
     * Write vector of highscores to the json file
     * @param filename is the path to the file
     */
    void writeToJson(const std::string& filename);

    /**
     * Read in highscores to the vector of highscores from the json file.
     * @param filename is the path to the file
     */
    bool readFromJson(const std::string& filename);

    /**
     * Returns the highscores.
     * @return a vector of highscores
     */
    std::vector<stats*> getHighScores(){
        return vectorOfHighscores;
    }

    /**
     * Set the highscores to the vector given.
     * @param highscores is a vector over state* to have the scores you want to set it to.
     */
    void setHighscores(std::vector<stats*> highscores){
        vectorOfHighscores = highscores;
    }

    /**
     * Returns the cap on stored elements.
     * @return a int with the number of max stored scores.
     */
    int getCapOnStored(){
        return capOnStored;
    }

protected:
    std::vector<stats*> vectorOfHighscores;
    int capOnStored = 10;
};


#endif //BOMBER_ROYALE_HIGHSCORE_H
