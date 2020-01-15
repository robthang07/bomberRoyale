#include "collision.h"

void collision::Detection(std::shared_ptr<Player>& player, std::shared_ptr<Sprite>& sprite, Config& config) {

    // The x and y size of all tiles for objects in the game
    int pxlSize = 32;

    // Player size less then 32 size then we need to find the indent we need to the right and bottom
    int indentX = pxlSize - player->getSizeX();
    int indentY = pxlSize - player->getSizeY();

    //the x position of the player in relation to where the map actually starts, not the window
    int trueX = (int) player->getX()-config.getBoxIndentWidth();
    //the y position of the player in relation to where the map actually starts, not the window
    int trueY = (int) player->getY()-config.getBoxIndentHeight();

    //This statement checks if the global bounds of the object is overlapping with the global bounds of the player
    if(sprite->getSprite().getGlobalBounds().intersects(player->getRectangleShape().getGlobalBounds()) && player->getX() > 0) {
        //checks if the speed of the player is non-0 which means it is moving along the x axis
        if(player->getXspeed()!=0) {


            /* Check which side of the x-tile is the rest, which side is empty
            * modX is equal to the offset of the pixel the player is on
            * modX will always be be between 0-31
            */
            int modX = trueX % pxlSize;

            //Checks the tile where the player is, this tile will always be the left-most tile the player is on
            int tileX = (trueX - modX) / pxlSize;

            /* checks if modX is greater than 15 and this will mean the majority of the player rectShape will be on the right side of the tile
            *we assume that when the majority of a player is on either side of the tile that he/she came from there before the intersection and will
            *therefore be pushed back when they intersect
            *if the player has mod <= 15 the player can just set the x position to the tile they are on
            *if the player happens to be on the right side we need to reset him to the tile he resides on + 1 as the tile the get functions return is on during the intersect would be the tile we intersect
            *it is necessary to add the indent of the play screen to the end so the player gets sent to the true position it needs to be in
            */
            if (modX > 15) {
                //If the player move right
                if (player->getXspeed() > 0) {
                    //indentX is added to add the character to the right position.
                    player->setX((tileX + 1) * pxlSize + config.getBoxIndentWidth()+indentX);
                }
                //Else the player move left
                else{
                    player->setX((tileX + 1) * pxlSize + config.getBoxIndentWidth());
                }
            }
            else {
                //If the player move right
                if (player->getXspeed() > 0){
                    //indentX is added to add the character to the right position.
                    player->setX(tileX * pxlSize  + config.getBoxIndentWidth()+indentX);
                }
                    //Else the player move left
                else{
                    player->setX(tileX * pxlSize  + config.getBoxIndentWidth());
                }
            }
        }


        //if the xSpeed is 0, the ySpeed must be non-0 and assume the player was moving either down or up into a wall/object/bomb
        else {
            /* Check which side of the y-tile is the rest, which side is empty
            * modY is equal to the offset of the pixel the player is on
            * modY will always be be between 0-31
            */
            int modY = trueY % pxlSize;

            //Checks the tile where the player is, this tile will always be the top-most tile the player is on
            int tileY = (trueY - modY) / pxlSize;


            /* checks if modY is greater than 15 and this will mean the majority of the player rectShape will be on the bottom of the tile
            *we assume that when the majority of a player is on either side of the tile that he/she came from there before the intersection and will
            *therefore be pushed back when they intersect
            *if the player has mod <= 15 the player can just set the Y position to the tile they are on
            *if the player happens to be on the bottom side we need to reset him to the tile he resides on + 1 as the tile the get functions return is on during the intersect would be the tile we intersect
            *it is necessary to add the indent of the play screen to the end so the player gets sent to the true position it needs to be in
            */
            if (modY > 15) {
                //If the player move down
                if (player->getYspeed() > 0) {
                    //indentX is added to add the character to the bottom position.
                    player->setY((tileY + 1) * pxlSize + config.getBoxIndentHeight() + indentY);
                }
                else{
                    player->setY((tileY + 1) * pxlSize + config.getBoxIndentHeight());
                }
            }
            else {
                //If the player move down
                if (player->getYspeed() > 0) {
                    //indentX is added to add the character to the bottom position.
                    player->setY(tileY * pxlSize + config.getBoxIndentHeight() + indentY);
                }
                else{
                    player->setY(tileY * pxlSize + config.getBoxIndentHeight());
                }
            }
        }


        //setting the position of the rectShape over the position of the newly placed player
        player->getRectangleShape().setPosition(player->getX(), player->getY());

    }
}

