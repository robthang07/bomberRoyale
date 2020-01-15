#include "BaseObject.h"

//Constructor that takes in the players starting position and speeds and sets them
BaseObject::BaseObject(float x, float y, float speed) {
    setX(x);
    setY(y);
    setXspeed(speed);
    setYspeed(speed);
}

BaseObject::BaseObject(float x, float y, float xSpeed, float ySpeed) {
    setX(x);
    setY(y);
    setXspeed(xSpeed);
    setYspeed(ySpeed);
}

//moves by adding the value of the speeds to the positions
void BaseObject::Move(){
    y += yspeed;
    x += xspeed;
}

//Setters
void BaseObject::setX(float x) {
    this->x = x;
}

void BaseObject::setY(float y) {
    this->y = y;
}

void BaseObject::setXspeed(float xspeed) {
    this->xspeed = xspeed;
}

void BaseObject::setYspeed(float yspeed) {
    this->yspeed = yspeed;
}

//Getters
float BaseObject::getX() const {
    return x;
}

float BaseObject::getY() const {
    return y;
}

float BaseObject::getXspeed() const {
    return xspeed;
}

float BaseObject::getYspeed() const {
    return yspeed;
}

void BaseObject::Draw(sf::RenderWindow &window) {

}



