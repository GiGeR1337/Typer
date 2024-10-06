#include "Menu.h"
#include <iostream>

menu::menu(float width, float height) : optionsPanel(width, height){
    if (!font.loadFromFile("..\\Roboto-Black.ttf")) {
        std::cerr << "Error loading font\n";
    }

    if(!background.loadFromFile("..\\backGround.png")){
        std::cerr << "Error loading background\n";
    }

    backgroundSprite.setTexture(background);
    backgroundSprite.setScale(
            width / backgroundSprite.getLocalBounds().width,
            height / backgroundSprite.getLocalBounds().height
    );

    // Кнопка Play
    playButton.setFont(font);
    playButton.setString("Play");
    playButton.setCharacterSize(50);

    PlayShape.setPosition(width / 2 - 100, height / 2 - 70);
    PlayShape.setSize(sf::Vector2f(250, 100));

    playButton.setPosition(
            PlayShape.getPosition().x + (PlayShape.getSize().x - playButton.getGlobalBounds().width) / 2,
            PlayShape.getPosition().y + (PlayShape.getSize().y - playButton.getGlobalBounds().height) / 2
    );

    //Кнопка Options
    optionsButton.setFont(font);
    optionsButton.setString("Options");
    optionsButton.setCharacterSize(50);

    OptionsShape.setPosition(width / 2 - 100, height / 2 + 50);
    OptionsShape.setSize(sf::Vector2f(250, 100));
    optionsButton.setPosition(
            OptionsShape.getPosition().x + (OptionsShape.getSize().x - optionsButton.getGlobalBounds().width) / 2,
            OptionsShape.getPosition().y + (OptionsShape.getSize().y - optionsButton.getGlobalBounds().height) / 2
    );
}

void menu::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);
    window.draw(PlayShape);
    window.draw(playButton);
    window.draw(OptionsShape);
    window.draw(optionsButton);

    optionsPanel.draw(window);
}

void menu::handleEvent(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (PlayShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                std::cout << "Play button pressed\n";
                playPressed = true;
            }

            if (OptionsShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                std::cout << "Options button pressed\n";
                optionsPanel.toggleVisibility();
            }
        }
    }
}

bool menu::isPlayPressed() const {
    return playPressed;
}

void menu::update(sf::RenderWindow &window) {
    updateButtonColor(PlayShape, playButton, window);
    updateButtonColor(OptionsShape, optionsButton, window);

    optionsPanel.update(window);
}

void menu::reset() {
    playPressed = false;
}

void menu::updateButtonColor(sf::RectangleShape &rectangleShape, sf::Text &buttonText, sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (rectangleShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        rectangleShape.setFillColor(sf::Color(59, 61, 221, 235));
        buttonText.setFillColor(sf::Color(234, 234, 234));
    } else {
        rectangleShape.setFillColor(sf::Color(48, 48, 213, 235));
        buttonText.setFillColor(sf::Color::White);
    }
}
