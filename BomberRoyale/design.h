#ifndef BOMBER_ROYALE_DESIGN_H
#define BOMBER_ROYALE_DESIGN_H

#include <TGUI/TGUI.hpp>


class Design {

public:
    /**
     * Function to get a background for mainMenu.
     * @return Texture for main menu;
     */
    sf::Texture getMainBackground();

    /**
     * Function to get a background for pause background.
     * @return Texture for pause background;
     */
    sf::Texture getPauseBackground();

    /**
     * Function to get a background for score background.
     * @return Texture for score background;
     */
    sf::Texture getScoreBackground();

    /**
     * Function to get a background for settings background.
     * @return Texture for settings background;
     */
    sf::Texture getSettingsBackground();

    /**
     * function to get font
     * @return font
     */
    sf::Font getFont();

    /**
    * Function to get button width
     * @return int buttonSizeWidth;
    */
    int getButtonSizeWidth() const;

    /**
    * Function to get button width and height
    * @return int buttonSizeHeight;
    */
    int getButtonSizeHeight() const;

    /**
     * Function to get a button design, so everyone can
     * have the same button design.
     * @param button is the object that is set design on.
     */
    void setButtonDesign(tgui::Button::Ptr button);

    /**
     * Function to get a color for button.
     * @return buttonColor
     */
    const sf::Color &getButtonColor() const;

    /**
     * Function to get a color for selected button
     * @return selected button
     */
    const sf::Color &getSelectedButtonColor() const;

    /**
     * function to get a color for text
     * @return textColor
     */
    const sf::Color &getTextColor() const;

    /**
     * Set design on textbox, incase textbox is used multiple times.
     * @param textBox the object that is set design on.
     */
    void setTextBoxDesign(tgui::TextBox::Ptr textBox);

    /**
     * Set design on label, in case label is used multiple times
     * @param label the object that is set design on
     */
    void setLabelDesign(tgui::Label::Ptr label);

    /**
     * Get the tabs width
     * @return a int with the tabs width
     */
    int getTabsWidth();

    /**
     * Get the tabs height.
     * @return a int with the tabs height.
     */
    int getTabsHeight();

    /**
     * Get the Padding size.
     * @return a int with the padding size.
     */
    int getPadding();

private:
    //Standard text values
    int padding = 10;

    //Standard tabs sizes
    int tabsSizeWidth = 300;
    int tabsSizeHeight = 30;

    //Standard buttonSize
    int buttonSizeWidth = 100;
    int buttonSizeHeight = 40;

    //Colors for button, selected button and text color
    sf::Color buttonColor = sf::Color::Cyan;
    sf::Color selectedButtonColor = sf::Color::White;
    sf::Color textColor = sf::Color::Black;



};


#endif //BOMBER_ROYALE_DESIGN_H