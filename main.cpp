#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include "Options.h"

#include <filesystem>

enum class GameState {
    Menu,
    Playing,
    GameOver
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Main Menu", sf::Style::Titlebar | sf::Style::Close);

    menu mainMenu(window.getSize().x, window.getSize().y);
    Options optionsMenu(window.getSize().x, window.getSize().y);
    Game game;

    GameState gameState = GameState::Menu;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameState == GameState::Menu) {
                mainMenu.handleEvent(event, window);
                optionsMenu.handleEvent(event, window, game);
                if (mainMenu.isPlayPressed()) {
                    gameState = GameState::Playing;
                    game.reset();
                }
            } else if (gameState == GameState::Playing) {
                game.handleEvent(event, window);
                if (game.isGameOver()) {
                    gameState = GameState::GameOver;
                }

            } else if (gameState == GameState::GameOver) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    gameState = GameState::Menu;
                    mainMenu.reset();
                }
            }
        }

        window.clear();

        if (gameState == GameState::Menu) {
            mainMenu.update(window);
            mainMenu.draw(window);
            optionsMenu.update(window);
            optionsMenu.draw(window);
        } else if (gameState == GameState::Playing) {
            game.update(window);
            game.draw(window);
        } else if (gameState == GameState::GameOver) {

            //GameOver плашка
            sf::Font font;
            if (!font.loadFromFile("..\\Jersey10-Regular.ttf"))
                std::cerr << "Error loading font\n";
            sf::Text gameOverText;
            sf::RectangleShape gameOverShape;
            gameOverShape.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
            gameOverShape.setPosition(0, 0);
            gameOverShape.setFillColor(sf::Color::Black);
            gameOverText.setFont(font);
            gameOverText.setString("Game Over! Press 'Enter' to return to Menu, noob!");
            gameOverText.setCharacterSize(70);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, window.getSize().y / 2 - gameOverText.getGlobalBounds().height / 2);

            window.draw(gameOverShape);
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
