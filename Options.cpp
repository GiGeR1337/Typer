#include <iostream>
#include "Options.h"

Options::Options(float width, float height) : fontSize(35), visible(false){ // початковий розмір шрифту
    if (!font11.loadFromFile("..\\Roboto-Black.ttf"))
        std::cerr << "Error loading font\n";

    if (!font22.loadFromFile("..\\PixelifySans-VariableFont_wght.ttf"))
        std::cerr << "Error loading font\n";

    if (!font33.loadFromFile("..\\TacOne-Regular.ttf"))
        std::cerr << "Error loading font\n";

    if (!font44.loadFromFile("..\\Jersey10-Regular.ttf"))
        std::cerr << "Error loading font\n";

    panel.setSize(sf::Vector2f(400, 750));
    panel.setFillColor(sf::Color(134, 41, 227, 150));
    panel.setPosition((width - panel.getSize().x) - 1190, (height - panel.getSize().y) / 2);

    OptionTitle.setFont(font11);
    OptionTitle.setString("Options");
    OptionTitle.setCharacterSize(50);
    OptionTitle.setPosition(110, 60);

    font1.setFont(font11);
    font1.setString("Font1");
    font1.setCharacterSize(35);
    font1.setPosition(65, 200);

    font2.setFont(font22);
    font2.setString("Font2");
    font2.setCharacterSize(37);
    font2.setPosition(255, 200);

    font3.setFont(font33);
    font3.setString("Font3");
    font3.setCharacterSize(43);
    font3.setPosition(65, 325);

    font4.setFont(font44);
    font4.setString("Font4");
    font4.setCharacterSize(45);
    font4.setPosition(255, 325);

    plus.setFont(font11);
    plus.setString("+");
    plus.setCharacterSize(35);
    plus.setPosition(300, 550);

    minus.setFont(font11);
    minus.setString("-");
    minus.setCharacterSize(35);
    minus.setPosition(100, 550);

    WordSize.setFont(font11);
    WordSize.setString(std::to_string(fontSize)); // Встановлюємо початкове значення
    WordSize.setCharacterSize(35);
    WordSize.setPosition(200, 550);
}

void Options::draw(sf::RenderWindow &window) {
    if (visible) {
        window.draw(panel);
        window.draw(OptionTitle);
        window.draw(font1);
        window.draw(font2);
        window.draw(font3);
        window.draw(font4);
        window.draw(plus);
        window.draw(minus);
        window.draw(WordSize);
    }
}

void Options::toggleVisibility() {
    visible = !visible;
}

bool Options::isVisible() const {
    return visible;
}

void Options::update(sf::RenderWindow &window) {
    if (visible) {
        updateButtonColor(font1, window);
        updateButtonColor(font2, window);
        updateButtonColor(font3, window);
        updateButtonColor(font4, window);
        updateButtonColor(plus, window);
        updateButtonColor(minus, window);

        updateWordSizeText();
    }
}

void Options::updateButtonColor(sf::Text &buttonText, sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (buttonText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonText.setFillColor(sf::Color::Red);
    } else {
        buttonText.setFillColor(sf::Color::White);
    }
}

void Options::handleEvent(sf::Event event, sf::RenderWindow &window, Game &game) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (font1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                game.setFont("..\\Roboto-Black.ttf");
                std::cout << "font1" << std::endl;
            } else if (font2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                game.setFont("..\\PixelifySans-VariableFont_wght.ttf");
                std::cout << "font2" << std::endl;
            } else if (font3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                game.setFont("..\\TacOne-Regular.ttf");
                std::cout << "font3" << std::endl;
            } else if (font4.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                game.setFont("..\\Jersey10-Regular.ttf");
                std::cout << "font4" << std::endl;
            } else if (plus.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                if(fontSize < 45){
                    fontSize++;
                    game.setFontSize(fontSize);
                    updateWordSizeText();
                    std::cout << "+" << std::endl;
                    std::cout << "Font size increased: " << fontSize << std::endl;
                }
            } else if (minus.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                if (fontSize > 20) { // Мінімальний розмір шрифту 20
                    fontSize--;
                    game.setFontSize(fontSize);
                    updateWordSizeText();
                    std::cout << "-" << std::endl;
                    std::cout << "Font size increased: " << fontSize << std::endl;
                }
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            game.setFont("..\\Roboto-Black.ttf");
            std::cout << "font1" << std::endl;
        } else if (event.key.code == sf::Keyboard::Num2) {
            game.setFont("..\\PixelifySans-VariableFont_wght.ttf");
            std::cout << "font2" << std::endl;
        } else if (event.key.code == sf::Keyboard::Num3) {
            game.setFont("..\\TacOne-Regular.ttf");
            std::cout << "font3" << std::endl;
        } else if (event.key.code == sf::Keyboard::Num4) {
            game.setFont("..\\Jersey10-Regular.ttf");
            std::cout << "font4" << std::endl;
        } else if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal) {
            if (fontSize < 45) {
                fontSize++;
                game.setFontSize(fontSize);
                updateWordSizeText();
                std::cout << "+" << std::endl;
                std::cout << "Font size increased: " << fontSize << std::endl;
            }
        } else if (event.key.code == sf::Keyboard::Subtract || event.key.code == sf::Keyboard::Hyphen) {
            if (fontSize > 20) { // Мінімальний розмір шрифту 20
                fontSize--;
                game.setFontSize(fontSize);
                updateWordSizeText();
                std::cout << "-" << std::endl;
                std::cout << "Font size decreased: " << fontSize << std::endl;
            }
        }
    }
}

void Options::updateWordSizeText() {
    WordSize.setString(std::to_string(fontSize));
}

