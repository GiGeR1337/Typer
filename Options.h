#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML/Graphics.hpp>
#include "Game.h"

class Options {
public:
    Options(float width, float height);
    void draw(sf::RenderWindow &window);
    void toggleVisibility();
    bool isVisible() const;
    void update(sf::RenderWindow &window);
    void handleEvent(sf::Event event, sf::RenderWindow &window, Game &game);

private:
    sf::Font font11;
    sf::Font font22;
    sf::Font font33;
    sf::Font font44;

    sf::RectangleShape panel;
    sf::Text OptionTitle;

    sf::Text font1;
    sf::Text font2;
    sf::Text font3;
    sf::Text font4;

    sf::Text plus;
    sf::Text minus;
    sf::Text WordSize;

    int fontSize; // Ініціалізація в заголовковому файлі

    bool visible = false;
    void updateButtonColor(sf::Text &buttonText, sf::RenderWindow &window);
    void updateWordSizeText();
};

#endif
