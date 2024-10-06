#include <iostream>
#include <fstream>
#include <random>
#include "Game.h"

Game::Game() : spawnTimer(0), spawnInterval(2.0f), gameOver(false), missedWords(0), fontSize(35), score(0){ // Ініціалізація fontSize
    if (!font.loadFromFile("..\\Roboto-Black.ttf"))
        std::cerr << "Error loading font\n";

    if (!font1.loadFromFile("..\\PixelifySans-VariableFont_wght.ttf"))
        std::cerr << "Error loading font\n";

    loadWordsFromFile("..\\words.txt"); // Зчитуємо слова з файлу

    if(!background.loadFromFile("..\\space.png"))
        std::cerr << "Error loading background\n";

    backgroundSprite.setTexture(background);
    backgroundSprite.setScale(
            1600 / backgroundSprite.getLocalBounds().width,
            800 / backgroundSprite.getLocalBounds().height
    );

    missedWordsText.setFont(font1);
    missedWordsText.setCharacterSize(45);
    missedWordsText.setFillColor(sf::Color(15, 0, 153));
    missedWordsText.setPosition(20, 705);
    updateMissedWordsText();

    Score.setFont(font1);
    Score.setCharacterSize(45);
    Score.setFillColor(sf::Color(15, 0, 153));
    Score.setPosition(1350, 705);
    updateScoreWordText();

    gameTimeClock.restart();
}

void Game::reset() {
    words.clear();
    score = 0;
    spawnTimer = 0;
    clock.restart();
    gameOver = false;
    missedWords = 0;
    updateMissedWordsText();
    std::cout << "Game reset. Missed words: " << missedWords << "\n";
    gameTimeClock.restart();
    updateScoreWordText();
}

void Game::handleEvent(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::TextEntered) {
        if (words.empty()) return;
        if (event.text.unicode == words.front().getText().front())  { // check if character entered
            words.front().typedChar(); // updates the state of the word
            if (words.front().isCompleted()) {
                words.erase(words.begin());
                score += 10;
                updateScoreWordText();
            }
        }
    }
}

void Game::update(sf::RenderWindow &window) {
    if (gameOver) return;

    float deltaTime = clock.restart().asSeconds();
    float gameTime = gameTimeClock.getElapsedTime().asSeconds();
    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval) {
        spawnWord();
        spawnTimer = 0;
    }

    float speedMultiplier = 1.0f + (gameTime / 60.0f);

    for (auto &word : words) {
        word.update(deltaTime * speedMultiplier);
        if (word.isOffScreen()) {
            missedWords++;
            updateMissedWordsText(); // Оновлюємо текст тут
            words.erase(words.begin());
            std::cout << "Word missed. Missed words count: " << missedWords << "\n";
            if (missedWords >= 3) {
                gameOver = true;
                std::cout << "Game Over triggered\n";
                break;
            }
        }
    }
}

void Game::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);
    for (Word &word : words) {
        word.render(window);
    }
    window.draw(missedWordsText); // Відображення тексту з кількістю пропущених слів
    window.draw(Score);
}

bool Game::isGameOver() const {
    return gameOver;
}

void Game::spawnWord() {
    if (wordList.empty()) return; // Перевірка чи вектор слів не порожній
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, wordList.size() - 1);
    std::string randomWord = wordList[distr(gen)];
    words.emplace_back(randomWord, font, 100.0f);
    words.back().setFontSize(fontSize); // Встановлення розміру шрифту
}

void Game::loadWordsFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Error opening words file\n";
        return;
    }

    std::string word;
    while (file >> word) {
        wordList.push_back(word);
    }
}

void Game::setFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font: " << fontPath << "\n";
    } else {
        for (auto &word : words) {
            word.setFont(font);
        }
    }
}

void Game::setFontSize(int size) {
    fontSize = size;
    for (auto &word : words) {
        word.setFontSize(size);
    }
}

void Game::updateMissedWordsText() {
    missedWordsText.setString("Missed Words: " + std::to_string(missedWords));
}

void Game::updateScoreWordText() {
    Score.setString("Score: " + std::to_string(score));
}
