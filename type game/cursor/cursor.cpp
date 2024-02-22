#include "cursor.hpp"

Cursor::Cursor(sf::RenderWindow &window) : window {window} {
    if (!this->cursorTexture.loadFromFile("./assets/textures/cursor.png")) {
        std::cout << "Error: failed to load cursor.png!" << std::endl;

        exit(1);
    }

    window.setMouseCursorVisible(false);

    this->cursorTexture.setSmooth(true);
    this->cursorSprite.setTexture(this->cursorTexture);

    sf::FloatRect dimension = this->cursorSprite.getLocalBounds();

    this->cursorSprite.setOrigin(dimension.width / 2, dimension.height / 2);
    this->cursorSprite.setScale(0.7, 0.7);
}

void Cursor::draw() {
    this->cursorSprite.setPosition(sf::Mouse::getPosition(this->window).x, sf::Mouse::getPosition(this->window).y);

    window.draw(this->cursorSprite);
}

std::pair<int, int> Cursor::getCursorCoordinates() const {
    return std::make_pair(sf::Mouse::getPosition(this->window).x, sf::Mouse::getPosition(this->window).y);
}