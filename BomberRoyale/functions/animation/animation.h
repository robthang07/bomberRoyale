#ifndef BOMBER_ROYALE_ANIMATION_H
#define BOMBER_ROYALE_ANIMATION_H

#include <SFML/Graphics.hpp>


class Animation {
public:
    //Default contructor
    Animation() = default;

    /**
     * Animation constructor
     * @param texture is used to get the size of the image, so imagecount can count the frames.
     * @param imageCount is used to count the frames on the image.
     * @param switchTime is used to decide when to change frame
     */
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

    //Animation destructor
    ~Animation();

    /**
     * A function to run the animation smoothly
     * @param row is used to decide which row we are on-
     * @param deltaTime used as a clock
     * @param faceRight is used to check if the player is faced right or not.
     */
    void update(int row, float deltaTime,bool faceRight);

    sf::IntRect uvRect;

private:
    //used to count how many "frames" there are on a picture.
    sf::Vector2u imageCount;
    //Used to figure out where the current frame it is on
    sf::Vector2u currentImage;


    float totalTime;
    //This decides how many seconds it will used to change frame
    float switchTime;
};


#endif //BOMBER_ROYALE_ANIMATION_H