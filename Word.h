#ifndef WORD_H
#define WORD_H

#include <SFML/Graphics.hpp>

class Word {
public:
    Word(const std::string& text, const sf::Font& font, float speed);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    const std::string& getText() const;
    void typedChar();
    bool isCompleted() const;
    bool isOffScreen() const;
    void setFont(const sf::Font& font);
    void setFontSize(int size); // Метод для зміни розміру шрифту

private:
    sf::Text wordText;
    std::string originalText;
    float speed;
    int fontSize; // Розмір шрифту
};

#endif
