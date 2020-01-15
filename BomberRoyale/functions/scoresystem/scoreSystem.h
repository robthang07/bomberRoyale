#ifndef BOMBER_ROYALE_SCORESYSTEM_H
#define BOMBER_ROYALE_SCORESYSTEM_H


#include "../../objects/Player.h"

class ScoreSystem {
public:
    /**
     * Add the score for destroying a box.
     * @param player is the player you want to add the score too.
     */
    static void addDestroingBoxScore(Player& player);

    /**
     * Add the score for picking up a power up
     * @param player is the player you want to add the score too.
     */
    static void addPickingPowerupsScore(Player& player);

    /**
     * Add the score for hurting a player
     * @param player is the player you want to add the score too.
     */
    static void addHurtingAplayerScore(Player& player);

    /**
     * Add the score for killing a player
     * @param player is the player you want to add the score too.
     */
    static void addKillingPlayerScore(Player& player);

    /**
     * Add the score for being alive per sec
     * @param player is the player you want to add the score too.
     * @param deltaTime is the time that has passed since last loop
     */
    static void addBeingAlivePerSecScore(Player& player, float& deltaTime);

    /**
     * Add the score for winning
     * @param player is the player you want to add the score too.
     * @param timer is the timer that is in the game.
     */
    static void addScoresToWinner(Player& player, int timer);

private:
    /**
     * Add the score for Being last alive
     * @param player is the player you want to add the score too.
     */
    static void addBeingLastAliveScore(Player& player);

    /**
     * Add the score for every life again when winning
     * @param player is the player you want to add the score too.
     */
    static void addforEveryLifeAgainScore(Player& player);

    /**
     * Add for score for how much time again the game
     * @param player is the player you want to add the score too.
     * @param timer is the timer that is in the game.
     */
    static void addHowMuchTimeLeftScore(Player& player, int timer);


    //In game score values
    const static int destroyingAbox = 200;
    const static int pickingUpPowerups = 400;
    const static int hurtingAplayer = 3000;
    const static int killingAplayer = 10000;
    const static int beingAlivePerLoop = 1;
    const static int beingLastAlive = 50000;

    //When won score values
    const static int forEveryLifeAgain = 2500;
    const static int howMuchTimeLeft = 2;

    //Variables for addBeingAlivePerSecScore
    static float secCounter;
    static int playerCounterOverSecScore;

};


#endif //BOMBER_ROYALE_SCORESYSTEM_H
