#include "pencil.hpp"
#include "../game/game.hpp"

Pencil::Pencil(sf::RenderWindow &window) : window {window} {
    if (!this->font.loadFromFile("./assets/font/RobotoMono-Medium.ttf")) {
        std::cout << "Error: failed to load RobotoMono-Medium.ttf!" << std::endl;

        exit(1);
    }

    this->text.setFont(this->font);
}

void Pencil::write(std::string text, int x, int y, int size, sf::Color color) {
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setPosition(x, y);
    this->text.setFillColor(color);

    this->window.draw(this->text);
}

void Pencil::write(std::string text, int y, int size, sf::Color color) {
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setFillColor(color);
    this->text.setOutlineThickness(1.5);
    this->text.setOutlineColor(sf::Color::Black);

    sf::FloatRect textRect = this->text.getLocalBounds();

    this->text.setOrigin(textRect.left + textRect.width / 2.0, textRect.top + textRect.height / 2.0);
    this->text.setPosition(Game::WIDTH / 2.0, y);

    this->window.draw(this->text);
}