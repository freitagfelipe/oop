#include "end.hpp"
#include "../game/game.hpp"

End::End(sf::RenderWindow &window, Cursor &cursor) : window {window}, pencil(window), cursor {cursor}, audio("./assets/sounds/continue.wav", 60) {
    this->bestStreak = 0;
    this->totalHits = 0;
    this->continueTextColor = sf::Color::White;
}

void End::update() {
    std::pair<int, int> cursorCoordinates {this->cursor.getCursorCoordinates()};

    this->continueTextColor = sf::Color::White;

    if (cursorCoordinates.first >= 280 && cursorCoordinates.first <= 520 && cursorCoordinates.second >= 540 && cursorCoordinates.second <= 570) {
        this->continueTextColor = sf::Color::Red;
    }
}

bool End::checkContinue(sf::Mouse::Button buttonPressed) {
    if (buttonPressed == sf::Mouse::Button::Left && this->continueTextColor == sf::Color::Red) {
        this->audio.play();

        return true;
    }

    return false;
}

void End::draw(const sf::Sprite &backgroundSprite) {
    static const std::string gameOverText = "Game over";
    std::string totalHitsText = "Total hits: " + std::to_string(this->totalHits);
    std::string bestStreakText = "Streak: " + std::to_string(this->bestStreak);
    std::string continueText = "continue";

    this->window.clear(sf::Color::Black);

    this->window.draw(backgroundSprite);
    this->pencil.write(gameOverText, 50, 50, sf::Color::White);
    this->pencil.write(totalHitsText, Game::HEIGHT / 2 - 50, 35, sf::Color::White);
    this->pencil.write(bestStreakText, Game::HEIGHT / 2 - 15, 35, sf::Color::White);
    this->pencil.write(continueText, Game::HEIGHT - 50, 50, this->continueTextColor);

    this->cursor.draw();

    this->window.display();
}

void End::setScores(int bestStreak, int totalHits) {
    this->bestStreak = bestStreak;
    this->totalHits = totalHits;
}