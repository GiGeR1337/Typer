#include "Word.h"

Word::Word(const std::string& text, const sf::Font& font, float speed)
        : originalText(text), speed(speed), fontSize(35) {
    wordText.setFont(font);
    wordText.setString(text);
    wordText.setCharacterSize(24);
    wordText.setFillColor(sf::Color::White);
    wordText.setPosition(0, static_cast<float>(rand() % 600)); // Random y position
}

void Word::update(float deltaTime) {
    wordText.move(speed * deltaTime, 0); // Move horizontally
    speed += deltaTime * 10.0f; //збільшуємо швидкість
}

void Word::render(sf::RenderWindow& window) {
    window.draw(wordText);
}

const std::string& Word::getText() const {
    return originalText;
}

void Word::typedChar() {
    if (!originalText.empty()) {
        originalText.erase(originalText.begin());
        wordText.setString(originalText);
    }
}

bool Word::isCompleted() const {
    return originalText.empty();
}

bool Word::isOffScreen() const {
    return wordText.getPosition().x > 1600; // чек чи слово поза межами
}

void Word::setFont(const sf::Font& font) {
    wordText.setFont(font);
}

void Word::setFontSize(int size) {
    fontSize = size;
    wordText.setCharacterSize(fontSize);
}
