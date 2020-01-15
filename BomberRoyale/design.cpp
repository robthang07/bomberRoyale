#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "design.h"

//Get button size width
int Design::getButtonSizeWidth() const {
    return buttonSizeWidth;
}

//Get button size height
int Design::getButtonSizeHeight() const {
    return buttonSizeHeight;
}

//Get Texture for MainMenu background
sf::Texture Design::getMainBackground() {
    sf::Texture txtr;
    txtr.loadFromFile("../resources/background/mainMenu.png");
    return txtr;
}

//Get Texture for Pause screen background
sf::Texture Design::getPauseBackground() {
    sf::Texture txtr;
    txtr.loadFromFile("../resources/background/gamePaused.png");
    return txtr;
}

//Get Texture for score screen background
sf::Texture Design::getScoreBackground(){
    sf::Texture txtr;
    txtr.loadFromFile("../resources/background/gameOver.png");
    return txtr;
}

sf::Texture Design::getSettingsBackground(){
    sf::Texture txtr;
    txtr.loadFromFile("../resources/background/settingBackground.png");
    return txtr;
}

//Get font
sf::Font Design::getFont(){
    sf::Font font;
    font.loadFromFile("../resources/font/braeside.ttf");
    return font;
}

//Set design on the button(Color, opacity, size and text color)
void Design::setButtonDesign(tgui::Button::Ptr button) {
    button->setSize(getButtonSizeWidth(),getButtonSizeHeight());
    button->getRenderer()->setOpacity(0.55);
    //gets embedded function on tgui which allows us to get renderers and change them
    tgui::ButtonRenderer* btnRender = button->getRenderer();
    btnRender->setBackgroundColor(getButtonColor());
    btnRender->setTextColor(getTextColor());
}

/* Set design on textBox(Background color, text color, text size,
 * vertical scrollbar and padding*/
void Design::setTextBoxDesign(tgui::TextBox::Ptr textBox){
    //textBox->setSize(400,400);
    //textBox->setPosition(200,200);
    textBox->getRenderer()->setBackgroundColor(sf::Color::White);
    textBox->getRenderer()->setTextColor(getTextColor());
    textBox->setTextSize(18);
    textBox->setVerticalScrollbarPresent(true);
    textBox->getRenderer()->setPadding(padding);
}

//Set design on label(text color and size)
void Design::setLabelDesign(tgui::Label::Ptr label) {
    //label->getRenderer()->setBackgroundColor(sf::Color::Red);
    label->getRenderer()->setTextColor(sf::Color::White);
    label->setTextSize(16);
    //label->getRenderer()->setPadding(10);
    //label->getRenderer()->setBorderColor(sf::Color::White);
    //label->getRenderer()->setBorders(1);
}

//Get a button Color
const sf::Color &Design::getButtonColor() const {
    return buttonColor;
}

//Get a color for selected button
const sf::Color &Design::getSelectedButtonColor() const {
    return selectedButtonColor;
}

//Get a color for text
const sf::Color &Design::getTextColor() const {
    return textColor;
}

//Get the tabs width
int Design::getTabsWidth() {
    return tabsSizeWidth;
}

int Design::getTabsHeight() {
    return tabsSizeHeight;
}

int Design::getPadding() {
    return padding;
}
