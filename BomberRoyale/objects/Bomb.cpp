#include "Bomb.h"
#include "sprite.h"
#include "powerups/powerUpHP.h"
#include "powerups/powerUpSpeed.h"
#include "powerups/bombPU.h"
#include <random>
#include "Player.h"
#include "powerups/powerUpBombPower.h"
#include "../functions/scoresystem/scoreSystem.h"


Bomb::Bomb() : BaseObject() {
    //Setter seed to generator to our seed
    generator.seed(seed);

    loadSprite();
    loadSoundEffects();
}

Bomb::Bomb(float x, float y, float xspeed, float yspeed) : BaseObject(x, y, xspeed, yspeed){
    //Setter seed to generator to our seed
    generator.seed(seed);

    loadSprite();
    loadSoundEffects();
}

void Bomb::Move() { }; //If the bomb is going to move make it here

void Bomb::Draw(sf::RenderWindow &window) {
    //Check if the explosion is active
    if (!explosion.activated) {
        //Draw bomb in the position it stand in.
        bombSprite.setPosition(getX(), getY());
        window.draw(bombSprite);
    }
    else {
        //Draw the middle explosion part
        window.draw(explosion.Middle);

        //Make a pointer to point on a vector on one of the ways
        std::vector<sf::Sprite>* VecToDrawPtr {};

        //Draw every way of the explosion
        for (int i = 0; i < 4; ++i) {
            //Set the pointer to the correct way at the time
            if (i == Explosion::way::LEFT){
                VecToDrawPtr = &explosion.Left;
            }
            else if(i == Explosion::way::RIGHT){
                VecToDrawPtr = &explosion.Right;
            }
            else if(i == Explosion::way::UP){
                VecToDrawPtr = &explosion.Up;
            }
            else if(i == Explosion::way::DOWN){
                VecToDrawPtr = &explosion.Down;
            }

            //Draw every element in te vector
            for (auto& ex : *VecToDrawPtr){
                window.draw(ex);
            }
        }
    }
}

void Bomb::loadSprite() {
    //###### BOMB
    //load texture from file and set it on the rectShape
    texture.loadFromFile("../resources/bomb/bomb.png");
    bombSprite.setTexture(texture);
    //Scale the bombSprite so it can fit to the player rectShape
    sf::Vector2u cSize = texture.getSize();
    bombSprite.scale((float) sizeX / cSize.x, (float) sizeY / cSize.y);

    //###### Explosion Middle
    //load texture from file and set it on the rectShape
    explosionTextureMiddel.loadFromFile("../resources/bomb/exMiddle.png");
    explosionSpriteMiddel.setTexture(explosionTextureMiddel);
    //Scale the explosion Middle so it can fit to the player rectShape
    sf::Vector2u dSize = explosionTextureMiddel.getSize();
    explosionSpriteMiddel.scale((float) sizeX / dSize.x , (float) sizeY/ dSize.y);

    //###### Explosion Side horizontally
    //load texture from file and set it on the rectShape
    explosionTextureSide.loadFromFile("../resources/bomb/exSide.png");
    explosionSpriteSideHorisontally.setTexture(explosionTextureSide);
    //Scale the explosion Middle so it can fit to the player rectShape
    sf::Vector2u eSize = explosionTextureSide.getSize();
    explosionSpriteSideHorisontally.scale((float) sizeX / eSize.x , (float) sizeY/ eSize.y);

    //###### Explosion End right
    //load texture from file and set it on the rectShape
    explosionTextureEnd.loadFromFile("../resources/bomb/exEnd.png");
    explosionSpriteEndRigth.setTexture(explosionTextureEnd);
    //Scale the explosion Middle so it can fit to the player rectShape
    sf::Vector2u fSize = explosionTextureEnd.getSize();
    explosionSpriteEndRigth.scale((float) sizeX / fSize.x , (float) sizeY/ fSize.y);

    //Explosion rectShape SIDE vertical - need to rotation because of original png
    explosionSpriteSideVertical = explosionSpriteSideHorisontally;
    explosionSpriteSideVertical.rotate(90);

    //Explosion rectShape END LEFT - need to rotation because of original png
    explosionSpriteEndLeft = explosionSpriteEndRigth;
    explosionSpriteEndLeft.rotate(180);

    //Explosion rectShape END UP - need to rotation because of original png
    explosionSpriteEndUp = explosionSpriteEndRigth;
    explosionSpriteEndUp.rotate(270);

    //Explosion rectShape END DOWN  - need to rotation because of original png
    explosionSpriteEndDown = explosionSpriteEndRigth;
    explosionSpriteEndDown.rotate(90);

}

void Bomb::checkForExplosion(sf::RenderWindow &window, float &delta, std::list<std::shared_ptr<Object>>& objects, std::list<std::shared_ptr<Object>>& walls, Player &player, Player& diffplayer, std::list<std::shared_ptr<BasePowerUps>>& powerups, Config& config) {

    //Draw away the time for the bomb to explode
    timer -= delta;

    if (!explosion.activated) {
        if (timer < 0) {
            if (explosion.Left.empty()) {

                //Add the middle part
                explosionSpriteMiddel.setPosition(getX(),getY());
                explosion.Middle = explosionSpriteMiddel;

                //Next if statement checks the volume is muted by user
                if (!config.isVolumeMuted()) {
                    //Next if statement to prevent explosion sound not plays more than one time
                    if (!explosionSoundPlayed) {
                        explosionSound.setVolume(config.getVolume()); //Volume configuration in settings
                        explosionSound.play();
                        explosionSoundPlayed = true; //To play sound once
                    }
                }

                //Check if player is dead or not
                if (!player.getDead()) {
                    //Check if the player is hit by the middle part.
                    if (explosion.Middle.getGlobalBounds().intersects(player.getRectangleShape().getGlobalBounds())) {
                        //Set the player hit by explosion
                        player.hitExplosives(delta);
                    }
                }

                //Check if different player is dead
                if (!diffplayer.getDead()) {
                    //Check if different player is hit by the middle part.
                    if (explosion.Middle.getGlobalBounds().intersects(
                            diffplayer.getRectangleShape().getGlobalBounds())) {
                        //if the different player is not hit protected add hurting score to the player
                        if (!diffplayer.getPlayerHit()) {
                            //Add score for hurting a player
                            ScoreSystem::addHurtingAplayerScore(player);
                        }

                        //Set the different player to hit by explosion
                        diffplayer.hitExplosives(delta);

                        //Check if different player is dead
                        if (diffplayer.getDead()) {
                            //Add score for killing a player
                            ScoreSystem::addKillingPlayerScore(player);
                        }
                    }
                }

                //Make the Explosion part
                sf::Sprite explosionPart;

                //Bool for checking if the element hitted the last vectore
                bool hitLast {};

                //Bool for checking if the element hit a wall
                bool hitWall {};

                //A temp posision
                int tempPosion {};

                //The remove object vector
                std::vector<std::shared_ptr<Object>> removeObjectsVector;

                //The four ways, left, right, up, down
                //Check for every way the explosion has.
                for (int j = 0; j < explosion.numberOfways; ++j) {

                    //Re-set the hit last and hit wall variable to false when checking for new way.
                    hitLast = false;
                    hitWall = false;

                    //Loop through as long as the range of the bomb power is.
                    for (int i = 0; i < player.getBombPower(); ++i) {

                        //set posision based on which way.
                        if (j == Explosion::way::LEFT) {
                            //find the position you are setting the element
                            tempPosion = (int) getX() - (i + 1) * 32;

                            explosionPart = explosionSpriteSideHorisontally;
                            explosionPart.setPosition(tempPosion, getY());
                        }
                        else if (j == Explosion::way::RIGHT){
                            //find the position you are setting the element
                            tempPosion = (int) getX() + (i + 1) * 32;

                            explosionPart = explosionSpriteSideHorisontally;
                            explosionPart.setPosition(tempPosion, getY());
                        }
                        else if (j == Explosion::way::UP){
                            //find the position you are setting the element
                            tempPosion = (int) getY() - (i + 1) * 32;

                            explosionPart = explosionSpriteSideVertical;

                            //+32 because rotating the rectShape in loading
                            explosionPart.setPosition(getX()+sizeX, tempPosion);
                        }
                        else if (j == Explosion::way::DOWN){
                            //find the position you are setting the element
                            tempPosion = (int) getY() + (i + 1) * 32;

                            explosionPart = explosionSpriteSideVertical;

                            //+32 because rotating the rectShape in loading
                            explosionPart.setPosition(getX()+sizeX, tempPosion);
                        }

                        //Check if player is dead
                        if (!player.getDead()) {
                            //Check if the player is hit by the explosionPart
                            if (explosionPart.getGlobalBounds().intersects(
                                    player.getRectangleShape().getGlobalBounds())) {
                                //Set the player to hit by explosion
                                player.hitExplosives(delta);
                            }
                        }

                        //Check if different player is dead
                        if (!diffplayer.getDead()) {
                            //Check if different player is hit by the explosionPart
                            if (explosionPart.getGlobalBounds().intersects(
                                    diffplayer.getRectangleShape().getGlobalBounds())) {

                                //if the different player is not hit protected add hurting score to the player
                                if (!diffplayer.getPlayerHit()) {
                                    //Add score for hurting a player
                                    ScoreSystem::addHurtingAplayerScore(player);
                                }

                                //Set the differnt player to hit by explosion
                                diffplayer.hitExplosives(delta);

                                //Check if different player is dead
                                if (diffplayer.getDead()) {
                                    //Add score for killing a player
                                    ScoreSystem::addKillingPlayerScore(player);
                                }
                            }
                        }

                        //Clear the objects vector for the next way.
                        removeObjectsVector.clear();

                        for (auto& wall : walls){
                            //Cast the wall to a rectShape for getting access to the elements you want.
                            std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(wall);

                            //Check if wall is hit by the explosion part
                            if (sprite->getSprite().getGlobalBounds().intersects(explosionPart.getGlobalBounds())) {
                                hitWall = true;
                            }
                        }

                        //If the explosion part hit the wall it is no reason to check if it hit a object
                        if (!hitWall) {
                            //Cast the object to a rectShape so we can use it with intersect
                            for (auto &ob : objects) {
                                //Cast the object to a rectShape for getting access to the elements you want.
                                std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(ob);

                                //TODO Remove this test code some time
                                //Check if the middle explosion part is coliding with a object
                                if (sprite->getSprite().getGlobalBounds().intersects(
                                        explosion.Middle.getGlobalBounds())) {
                                    removeObjectsVector.emplace_back(ob);
                                }

                                //Check if object is hit by the explosion part
                                if (sprite->getSprite().getGlobalBounds().intersects(explosionPart.getGlobalBounds())) {
                                    hitLast = true;
                                    //Push the remove objects in to the vector
                                    removeObjectsVector.emplace_back(ob);
                                }
                            }

                            //loop through every remove object in the remove vector
                            for (auto &rem : removeObjectsVector){
                                //Remove the objects from the map based on the objects in the remove object
                                objects.remove(rem);

                                //Spawn the powerups
                                spawnPowerUp(rem,powerups);

                                //Add score for destroing a box
                                ScoreSystem::addDestroingBoxScore(player);
                            }
                        }
                        //If the bomb part hit a wall stop checking for more and not draw it.
                        if (hitWall){
                            break;
                        }
                        //if it hit last before intersect or it is last bombPower in range
                        else if (hitLast || i == (player.getBombPower()-1)) {
                            //Add last rectShape based on which way here
                            if (j == Explosion::way::LEFT){
                                explosionPart = explosionSpriteEndLeft;

                                //+both since rotated 360
                                explosionPart.setPosition(tempPosion+sizeX,getY()+sizeY);

                                explosion.Left.emplace_back(explosionPart);
                            }
                            else if (j == Explosion::way::RIGHT){
                                explosionPart = explosionSpriteEndRigth;

                                //+ nothing since not rotated
                                explosionPart.setPosition(tempPosion,getY());

                                explosion.Right.emplace_back(explosionPart);
                            }
                            else if (j == Explosion::way::UP){
                                explosionPart = explosionSpriteEndUp;

                                //+sizeY since rotated 90
                                explosionPart.setPosition(getX(),tempPosion+sizeY);

                                explosion.Up.emplace_back(explosionPart);
                            }
                            else if (j == Explosion::way::DOWN){
                                explosionPart = explosionSpriteEndDown;

                                //+sizex since rotated 270
                                explosionPart.setPosition(getX()+sizeX,tempPosion);

                                explosion.Down.emplace_back(explosionPart);
                            }

                            //Then break the loop for done
                            break;
                        }
                        else {
                            //Add the current way part based on which way
                            if (j == Explosion::way::LEFT){
                                explosion.Left.emplace_back(explosionPart);
                            }
                            else if (j == Explosion::way::RIGHT){
                                explosion.Right.emplace_back(explosionPart);
                            }
                            else if (j == Explosion::way::UP){
                                explosion.Up.emplace_back(explosionPart);
                            }
                            else if (j == Explosion::way::DOWN){
                                explosion.Down.emplace_back(explosionPart);
                            }
                        }
                    }
                }

                //TODO TEST Code remove some time
                //Write out the size of the ways it explode - Test code
                std::cout << "Left: " << explosion.Left.size()
                          << " Right: " << explosion.Right.size()
                          << " Up: " << explosion.Up.size()
                          << " Down: " << explosion.Down.size()
                          << std::endl;
            }

            //Set the explosion activated, set the time for active and the remove object.
            explosion.activated = true;
            explosion.timeActivated = baseTimeForExplosion;
            explosion.remove = false;
        }
    }
    else{
        //Set down the timer of visible.
        explosion.timeActivated -= delta;

        //Check if player is dead
        if(!player.getDead()) {
            //Check if player hit the middle explosion part.
            if (player.getRectangleShape().getGlobalBounds().intersects(explosion.Middle.getGlobalBounds())) {
                //Set the player to hit by explosion
                player.hitExplosives(delta);
            }
        }

        //Check if differnt player is dead
        if (!diffplayer.getDead()) {
            //Check if different player hit the middle explosion part.
            if (diffplayer.getRectangleShape().getGlobalBounds().intersects(explosion.Middle.getGlobalBounds())) {
                //if the different player is not hit protected add hurting score to the player
                if (!diffplayer.getPlayerHit()) {
                    //Add score for hurting a player
                    ScoreSystem::addHurtingAplayerScore(player);
                }

                //Set the different player to hit by explosion
                diffplayer.hitExplosives(delta);

                //Check if different player is dead
                if (diffplayer.getDead()) {
                    //Add score for killing a player
                    ScoreSystem::addKillingPlayerScore(player);
                }
            }
        }


        //A pointer to the current pointer
        std::vector<sf::Sprite>* currentWayPtr{};

        //Loop through every way of the explosion
        for (int i = 0; i < explosion.numberOfways; ++i) {
            //set correct vector based on the I number
            if (i == Explosion::way::LEFT) {
                currentWayPtr = &explosion.Left;
            }
            else if (i == Explosion::way::RIGHT){
                currentWayPtr = &explosion.Right;
            }
            else if (i == Explosion::way::UP){
                currentWayPtr = &explosion.Up;
            }
            else if (i == Explosion::way::DOWN){
                currentWayPtr = &explosion.Down;
            }
            //Loop through the current vector
            for (auto& part : *currentWayPtr){
                //Check if player is dead
                if (!player.getDead()) {
                    //if not then check
                    //if player hits any of the vector part
                    if (player.getRectangleShape().getGlobalBounds().intersects(part.getGlobalBounds())) {
                        //Set the player hit by explosion
                        player.hitExplosives(delta);
                    }
                }
                //Check if different player is dead.
                if (!diffplayer.getDead()) {
                    //if it is not check if it is hit by explosion
                    if (diffplayer.getRectangleShape().getGlobalBounds().intersects(part.getGlobalBounds())) {
                        //if the different player is not hit protected add hurting score to the player
                        if (!diffplayer.getPlayerHit()) {
                            //Add score for hurting a player
                            ScoreSystem::addHurtingAplayerScore(player);
                        }

                        //Set the different player to hit by explosion
                        diffplayer.hitExplosives(delta);

                        //Check if different player is dead
                        if (diffplayer.getDead()) {
                            //Add score for killing a player
                            ScoreSystem::addKillingPlayerScore(player);
                        }
                    }
                }
            }
        }

        //If time is less then zero
        if (explosion.timeActivated < 0){
            // then deActivate it and flag it for removable
            explosion.activated = false;
            explosion.remove = true;
        }
    }
}

void Bomb::spawnPowerUp(std::shared_ptr<Object> &object, std::list<std::shared_ptr<BasePowerUps>> &powerups) {
    //Cast the object to a rectShape
    std::shared_ptr<Sprite> sprite = std::static_pointer_cast<Sprite>(object);

    //Generate the numbers for the object
    int spawn = spawnChances(generator);
    int witchToSpawn = different(generator);

    //Chose if to spawn and what to spawn.
    if (spawn > 1){
        //Powerup HP
        if (witchToSpawn == 1){
            powerups.emplace_back(std::make_shared<powerUpHP>(sprite->getSprite().getGlobalBounds().left, sprite->getSprite().getGlobalBounds().top, 0,0));
        }
        //Powerup Speed
        else if (witchToSpawn == 2){
            powerups.emplace_back(std::make_shared<powerUpSpeed>(sprite->getSprite().getGlobalBounds().left, sprite->getSprite().getGlobalBounds().top, 0,0));
        }
        //Powerup bomb power
        else if (witchToSpawn == 3){
            powerups.emplace_back(std::make_shared<PowerUpBombPower>(sprite->getSprite().getGlobalBounds().left, sprite->getSprite().getGlobalBounds().top, 0,0));
        }
        //Powerup max bomb
        else if (witchToSpawn == 4){
            powerups.emplace_back(std::make_shared<bombPU>(sprite->getSprite().getGlobalBounds().left, sprite->getSprite().getGlobalBounds().top, 0,0));
        }
    }
}

void Bomb::loadSoundEffects() {
    //Explosion sound
    if (!explosionSoundBuffer.loadFromFile("../resources/sounds/explosion.ogg")) {
        std::cout << "Explosion sound loads failed" << std::endl;
    }
    explosionSound.setBuffer(explosionSoundBuffer);
}