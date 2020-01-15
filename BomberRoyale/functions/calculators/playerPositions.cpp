#include "playerPositions.h"

int PlayerPositions::setPlayerX(int playerCount, int xsize) {
    int tempPos = 0;

    // Checks which player you are
    if (playerCount == 0 || playerCount == 2){
        tempPos = config.getBoxIndentWidth()+32;
        return tempPos;
    }
    else{
        tempPos = config.getBoxIndentWidth()+480+(32-xsize);
        return  tempPos;
    }

}

int PlayerPositions::setPlayerY(int playerCount, int ysize) {
    int tempPos = 0;
    if(playerCount == 0 || playerCount == 1){
        tempPos = config.getBoxIndentHeight()+32;
        return tempPos;
    }
    else {
        tempPos = config.getBoxIndentHeight()+352+(32-ysize);
        return tempPos;
    }
}