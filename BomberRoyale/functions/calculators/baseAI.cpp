#include "baseAI.h"

BaseAI::BaseAI() : Player() {

    this->isPlayer = false;

}

BaseAI::~BaseAI(){

    bombs.clear();
}



void BaseAI::Move(float deltaTime){

    if(getXspeed() == 0.0f ){
        if(getDirection()==UP){
            row = 0;
        }
        else{
            row = 2;
        }
    }

    else{
        row = 1;
        faceRight = getXspeed() > 0.0f;
    }
    animation->update(row, deltaTime, faceRight);
    rectShape.setTextureRect(animation->uvRect);

    timer -= deltaTime;

    if(timer <= 0){

        if(getDirection()==UP){
            setYspeed(-getSpeed()*deltaTime);
            setXspeed(0);
        }
        else if(getDirection()==LEFT){
            setXspeed(-getSpeed()*deltaTime);
            setYspeed(0);
        }
        else if(getDirection()==DOWN){
            setYspeed(getSpeed()*deltaTime);
            setXspeed(0);
        }
        else if(getDirection()==RIGHT){
            setXspeed(getSpeed()*deltaTime);
            setYspeed(0);
        }
        else{
            setXspeed(0);
            setYspeed(0);
        }


        findPositions();

        timer = 5;


    }

    BaseObject::Move();

    // Set position after moving, important for frames
    Player::rectShape.setPosition(getX(),getY());

    //reduces the delta time
    hitProtectiontimer -= deltaTime;

    getRectangleShape().setPosition(getX(),getY());
};

void BaseAI::Draw(sf::RenderWindow& window){
    Player::Draw(window);
};

void BaseAI::findPositions() {
    for (auto &player : playerList) {
        xArray[index] = player->getRectangleShape().getPosition().x;
        yArray[index] = player->getRectangleShape().getPosition().y;
        index++;
    }

    if (index == 4) {
        index = 0;
    }
    float totalDistance[playerList.size()];

    for (int i = 0; i < 4; i++) {
        xDistArray[i] = abs(xArray[i] - getRectangleShape().getPosition().x);
        yDistArray[i] = abs(yArray[i] - getRectangleShape().getPosition().y);
        totalDistance[i] = xDistArray[i]+yDistArray[i];
    }

    float lowestDistance = totalDistance[0];
    float xPlacementOfClosest = xArray[0];
    float yPlacementOfClosest = yArray[0];

    for(int i = 1; i < playerList.size(); i++){
        if(lowestDistance > totalDistance[i] && totalDistance[i] != 0){
            lowestDistance = totalDistance[i];
            xPlacementOfClosest = xArray[i];
            yPlacementOfClosest = yArray[i];
        }
    }


    float xDistanceToClosest = getX()-xPlacementOfClosest;
    float yDistanceToClosest = getY()-yPlacementOfClosest;

    if(abs(xDistanceToClosest) > abs(yDistanceToClosest)){
        if(xDistanceToClosest < 0){
            setDirection(RIGHT);
        }
        else{
            setDirection(LEFT);
        }
    }
    else{
        if(yDistanceToClosest < 0){
            setDirection(DOWN);
        }
        else{
            setDirection(UP);
        }
    }

};

