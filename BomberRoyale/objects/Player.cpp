#include "Player.h"

int Player::nextPlayerCount = 0;

Player::Player() : BaseObject(){

    this->speed = 10;
    row = 1;
    faceRight = true;

    //Set the player count and increase the number
    this->playerCount = nextPlayerCount;
    nextPlayerCount++;

    //Check if player next counter  equal 4 if then rest it.
    if (nextPlayerCount == 4) {
        nextPlayerCount = 0;
    }

    //Player load the character rectShape
    loadSprite();

    //Make a player ps object for easier placement
    PlayerPositions ps;
    //Set the position on the player
    setX(ps.setPlayerX(playerCount,sizeX));
    setY(ps.setPlayerY(playerCount,sizeY));

    //Set the speed of the player
    setSpeed(30);

    //Set the hp of the character
    setHp(3);

}

Player::Player(Config &config) : BaseObject() {

    //Set the player count and increase the number
    this->playerCount = nextPlayerCount;
    playerCount = nextPlayerCount++;
    
    //Check if player next counter  equal 4 if then rest it.
    if (nextPlayerCount == 4) {
        nextPlayerCount = 0;
    }

    //Player load the character rectShape
    loadSprite();

    //Make a player ps object for easier placement
    PlayerPositions ps;
    //Set the position on the player
    setX(ps.setPlayerX(playerCount,sizeX));
    setY(ps.setPlayerY(playerCount,sizeY));

    //Load in the player inputs
    playerInput = config.getInputs(playerCount);

    //Set the speed of the player
    setSpeed(100);

    //Set the hp of the character
    setHp(3);

    this->isPlayer = true;

}


Player::~Player(){
    delete texture;
    delete animation;

    //Clear the bomb list
    bombs.clear();
}

void Player::Move(float deltaTime) {
    //Set the character x and y -speed
    moveInput(deltaTime);

    //Inherits move funtion from BaseObject
    //Move the player as it should
    BaseObject::Move();

    //sets the position of the rectShape on top of the player
    rectShape.setPosition(getX(),getY());

    //reduces the delta time
    hitProtectiontimer -= deltaTime;
}

void Player::Draw(sf::RenderWindow &window) {
    //draw rectShape on window
    window.draw(rectShape);
}

void Player::loadSprite() {

    texture = new sf::Texture();

    //load texture from file and set it on the rectShape
    //Chose which texture to load based on the playerCount
    if (playerCount == 0){
        texture->loadFromFile("../resources/characters/ninjaDone.png");
    }
    else if (playerCount == 1){
        texture->loadFromFile("../resources/characters/ninjaYellow.png");
    }
    else if (playerCount == 2){
        texture->loadFromFile("../resources/characters/ninjaBlue.png");
    }
    else if (playerCount == 3){
        texture->loadFromFile("../resources/characters/ninjaRed.png");
    }

    //set the rectShape's texture to the texture we loaded
    animation = new Animation(texture, sf::Vector2u(10, 4), 0.08f);
    rectShape.setSize(sf::Vector2f(sizeX,sizeY));
    rectShape.setTexture(texture);

    /*
    //Auto scale the image to the size we want.
    sf::Vector2u cSize = texture.getSize();
    rectShape.scale((float) sizeX / cSize.x , (float) sizeY / cSize.y);*/
}


void Player::moveInput(float deltaTime){

    //Check if the player is moving
    if (sf::Keyboard::isKeyPressed(playerInput[0]) ||
        sf::Keyboard::isKeyPressed(playerInput[1]) ||
        sf::Keyboard::isKeyPressed(playerInput[2]) ||
        sf::Keyboard::isKeyPressed(playerInput[3])) {

        //if player move up
        if (sf::Keyboard::isKeyPressed(playerInput[0])) {
                setYspeed(-getSpeed() * deltaTime);
                setXspeed(0);

        }
        //if player move left
        if (sf::Keyboard::isKeyPressed(playerInput[1])) {
            setXspeed(-getSpeed() * deltaTime);
            setYspeed(0);
        }
        //if player move down
        if (sf::Keyboard::isKeyPressed(playerInput[2])) {
            setYspeed(getSpeed() * deltaTime);
            setXspeed(0);
        }
        //if player move right
        if (sf::Keyboard::isKeyPressed(playerInput[3])) {
            setXspeed(getSpeed() * deltaTime);
            setYspeed(0);
        }
    }
    else {
        //if not move set x and y speed to zero
        setXspeed(0);
        setYspeed(0);
    }


    if(getXspeed() == 0.0f ){
        if(sf::Keyboard::isKeyPressed(playerInput[0])){
            row = 0;
        }
        else{
            row = 2;
        }
    }

    else{
        row = 1;
        if(getXspeed() > 0.0f){
            faceRight = true;
        }
        else{
            faceRight = false;
        }
    }
    animation->update(row, deltaTime, faceRight);
    rectShape.setTextureRect(animation->uvRect);
}


void Player::hitExplosives(float &deltaTime) {


    //Sets player to hit and reduces his/her HP.
    if (!getPlayerHit()) {
        //set playerHit to true for same hit protection
        playerHit = true;
        //Remove 1 hp
        hp--;

        //Check if player is killed
        if (hp == 0){
            //if it is flag it dead
            dead = true;
        }

        //Write that it hit a explosion
        std::cout<<("Player hit explosive")<<std::endl;
        //Set the timer to
        sethitProtectionTimer(hitProtectiontimeReset);
    }

    //waits till given time to make player vulnerable again
    if(hitProtectiontimer <= 0){
        playerHit = false;
    }

}