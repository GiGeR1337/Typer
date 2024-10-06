#ifndef UNTITLED3_MENU_H
#define UNTITLED3_MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Options.h"

class menu {
public:
    menu(float width, float height);
    void draw(sf::RenderWindow &window);
    void handleEvent(sf::Event event, sf::RenderWindow &window);
    bool isPlayPressed() const;
    void update(sf::RenderWindow &window);
    void reset();

private:
    sf::Font font;
    sf::Text playButton;
    sf::Text optionsButton;
    sf::RectangleShape PlayShape;
    sf::RectangleShape OptionsShape;
    sf::Texture background;
    sf::Sprite backgroundSprite;
    bool playPressed = false;

    Options optionsPanel;

    void updateButtonColor(sf::RectangleShape &rectangleShape, sf::Text &buttonText, sf::RenderWindow &window);
};

#endif // UNTITLED3_MENU_H
