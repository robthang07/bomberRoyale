#include "scoreSystem.h"

float ScoreSystem::secCounter = 0;
int ScoreSystem::playerCounterOverSecScore = 0;

void ScoreSystem::addDestroingBoxScore(Player &player) {
    player.setScore(player.getScore() + destroyingAbox);
}

void ScoreSystem::addPickingPowerupsScore(Player &player) {
    player.setScore(player.getScore() + pickingUpPowerups);
}

void ScoreSystem::addHurtingAplayerScore(Player &player) {
    player.setScore(player.getScore() + hurtingAplayer);
}

void ScoreSystem::addKillingPlayerScore(Player &player) {
    player.setScore(player.getScore() + killingAplayer);
}

void ScoreSystem::addBeingAlivePerSecScore(Player &player, float& deltaTime) {
    //Add 1 for each player this run on.
    playerCounterOverSecScore += 1;

    //Check if this is the first player
    if (playerCounterOverSecScore == 1) {
        //Add the time to the copy of the timer
        secCounter += deltaTime;
    }

    //Check if the timer is more then 1;
    if (secCounter > 1){
        //add the score for a sec
        player.setScore(player.getScore() + beingAlivePerLoop);
    }

    //4 is hard coded here at the moment because we do not have a number in config to fix it
    //but it is always 4 players because rest is AI and players.
    if (playerCounterOverSecScore == 4){
        //Reset the counter to zero
        playerCounterOverSecScore = 0;

        //Check if the timer is more then 1
        if (secCounter > 1) {
            //Remove a sec from the time
            secCounter -= 1;
        }
    }
}

void ScoreSystem::addScoresToWinner(Player &player, int timer) {
    addBeingLastAliveScore(player);
    addforEveryLifeAgainScore(player);
    addHowMuchTimeLeftScore(player,timer);
}

void ScoreSystem::addBeingLastAliveScore(Player &player) {
    player.setScore(player.getScore() + beingLastAlive);
}

void ScoreSystem::addforEveryLifeAgainScore(Player &player) {
    player.setScore(player.getScore() + forEveryLifeAgain * player.getHp());
}

void ScoreSystem::addHowMuchTimeLeftScore(Player &player, int timer) {
    player.setScore(player.getScore() + howMuchTimeLeft * timer);
}