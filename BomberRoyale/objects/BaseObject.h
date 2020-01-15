#ifndef BOMBER_ROYALE_OBJECT_H
#define BOMBER_ROYALE_OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>

//TODO add comments
class BaseObject {
public:
    /**Default constructor sets all simple values to zero
     */
    BaseObject(){
        x = y = xspeed = yspeed = 0;
    };

    /**Normal constructor that take in ever attribute it have
     */
    BaseObject(float x, float y, float speed);

    BaseObject(float x, float y, float xSpeed, float ySpeed);

    /**Set the destructor to default
     */
   virtual ~BaseObject() = default;

   /**The move function for every object
    */
    virtual void Move();

    /**Default draw function for every object
     * @param window is the screen the player is playing on
     */
    virtual void Draw(sf::RenderWindow &window);

    /**Getter for X value of Base Object
     *
     * @return X value of the Base Object
     */
   float getX() const;

    /**Getter for Y value of Base Object
     *
     * @return Y value of the Base Object
     */
   float getY() const;

    /**Getter for the X Speed of Base Object
     *
     * @return X speed of the base Object
     */
   float getXspeed() const;

   /**Getter for the Y Speed of Base Object
    *
    * @return Y speed of the base Object
    */
   float getYspeed() const;

    /**Setter for the X position of Base Object
     *
     * @param x is the position along the x-axis where we want the player to be
     */
   void setX(float x);

    /**Setter for the Y position of Base Object
     *
     * @param y is the position along the y-axis where we want the player to be
     */
   void setY(float y);

    /**Setter for the X speed of Base Object
     *
     * @param xspeed is the speed  along the x-axis we want the player to have
     */
   void setXspeed(float xspeed);

    /**Setter for the Y speed of Base Object
     *
     * @param yspeed is the speed  along the y-axis we want the player to have
     */
   void setYspeed(float yspeed);


private:
    // x and y position of the player
    float x, y;
    //the speeds the player can move along each axis
    float xspeed, yspeed;

};


#endif //BOMBER_ROYALE_OBJECT_H
