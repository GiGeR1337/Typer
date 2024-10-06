#ifndef UNTITLED3_GAME_H
#define UNTITLED3_GAME_H

#include <SFML/Graphics.hpp>
#include "Word.h"
#include <vector>
#include <string>

class Game {
public:
    Game();
    void reset();
    void handleEvent(sf::Event event, sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
    bool isGameOver() const;
    void setFont(const std::string& fontPath);
    void setFontSize(int size);

private:
    sf::Font font;
    sf::Font font1;
    sf::Texture background;
    sf::Sprite backgroundSprite;
    std::vector<Word> words;
    std::vector<std::string> wordList; //вектор для збереження слів
    sf::Clock clock;
    sf::Clock gameTimeClock;
    sf::Text missedWordsText;
    sf::Text Score;
    float spawnTimer;
    float spawnInterval;
    bool gameOver;
    int missedWords;
    int score;

    int fontSize;

    void spawnWord();
    void loadWordsFromFile(const std::string& filePath); // метод для зчитування слів з файлу
    void updateMissedWordsText();
    void updateScoreWordText();
};

#endif // UNTITLED3_GAME_H
