#include "menu.hpp"
#include "../game/game.hpp"

Menu::Menu(sf::RenderWindow &window, Cursor &cursor) : window {window}, pencil(window), cursor {cursor}, startAudio("./assets/sounds/joiningGame.wav", 60) {
    this->startTextColor = sf::Color::White;
    this->exitTextColor = sf::Color::White;
}

void Menu::update() {
    std::pair<int, int> cursorCoordinates {this->cursor.getCursorCoordinates()};

    this->startTextColor = sf::Color::White;
    this->exitTextColor = sf::Color::White;

    if (cursorCoordinates.first >= 330 && cursorCoordinates.first <= 470 && cursorCoordinates.second >= 260 && cursorCoordinates.second <= 290) {
        this->startTextColor = sf::Color::Red;
    } else if (cursorCoordinates.first >= 340 && cursorCoordinates.first <= 460 && cursorCoordinates.second >= 310 && cursorCoordinates.second <= 345) {
        this->exitTextColor = sf::Color::Red;
    }
}

bool Menu::checkButtonPressed(sf::Mouse::Button buttonPressed) {
    if (buttonPressed == sf::Mouse::Button::Left && this->startTextColor == sf::Color::Red) {
        this->startAudio.play();
        
        return true;
    } else if (buttonPressed == sf::Mouse::Left && this->exitTextColor == sf::Color::Red) {
        this->window.close();
    }

    return false;
}

void Menu::draw(const sf::Sprite &backgroundSprite) {
    static const std::string gameNameText = "Type Game";
    static const std::string startText = "start";
    static const std::string exitText = "exit";

    this->window.clear(sf::Color::Black);

    this->window.draw(backgroundSprite);
    this->pencil.write(gameNameText, 70, 70, sf::Color::White);
    this->pencil.write(startText, Game::HEIGHT / 2 - 25, 50, this->startTextColor);
    this->pencil.write(exitText, Game::HEIGHT / 2 + 25, 50, this->exitTextColor);

    this->cursor.draw();

    this->window.display();
}