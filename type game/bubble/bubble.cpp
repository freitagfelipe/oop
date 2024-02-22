#include "bubble.hpp"

Bubble::Bubble(int x, int y, char letter, double speed) {
    if (!this->bubbleTexture.loadFromFile("./assets/textures/circle.png")) {
        std::cout << "Error: failed to load circle.png!" << std::endl;

        exit(1);
    }

    this->x = x;
    this->y = y;
    this->letter = letter;
    this->speed = speed;
    this->alive = true;
    this->bubbleTexture.setSmooth(true);
}

void Bubble::update() {
    this->y += this->speed;
}

void Bubble::draw(sf::RenderWindow &window) {
    static Pencil pencil(window);

    sf::CircleShape bubble(Bubble::RADIUS);

    bubble.setTexture(&this->bubbleTexture);

    sf::FloatRect dimensions = bubble.getLocalBounds();

    bubble.setOrigin(dimensions.width / 2, dimensions.height / 2);
    bubble.setPosition(this->x, this->y);
    bubble.setFillColor(sf::Color::White);

    window.draw(bubble);

    pencil.write(std::string(1, this->letter), this->x - dimensions.width / 2 + 0.65 * Bubble::RADIUS, this->y - dimensions.height / 2 + 4, Bubble::RADIUS * 1.3, sf::Color::White);
}

void Bubble::setAliveStatus(bool status) {
    this->alive = status;
}

bool Bubble::getAliveStatus() const {
    return this->alive;
}

char Bubble::getLetter() const {
    return this->letter;
}

std::pair<int, int> Bubble::getCoordinates() const {
    return std::make_pair(this->x, this->y);
}