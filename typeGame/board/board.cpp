#include "board.hpp"
#include "../game/game.hpp"

Board::Board(sf::RenderWindow &window, Cursor &cursor) : window {window}, pencil(window), cursor {cursor}, hitAudio("./assets/sounds/hit.wav", 10), comboBreakAudio("./assets/sounds/comboBreak.wav", 20), failAudio("./assets/sounds/failSound.wav", 20), errorAudio("./assets/sounds/missSound.wav", 20) {
    this->currentHits = 0;
    this->bestStreak = 0;
    this->totalHits = 0;
    this->totalMisses = 0;
}

void Board::update() {
    if (this->checkNewBubble()) {
        this->addNewBubble();
    }

    for (Bubble &bubble : this->bubbles) {
        bubble.update();
    }

    this->markOutsideBubbles();
    this->removeDeadBubbles();
}

bool Board::checkNewBubble() {
    static const int newBubbleTimeout {60};
    static int newBubbleTimer {0};

    newBubbleTimer--;

    if (newBubbleTimer <= 0) {
        newBubbleTimer = newBubbleTimeout;

        return true;
    }

    return false;
}

void Board::removeDeadBubbles() {
    std::vector<Bubble> alives;

    for (Bubble& bubble : this->bubbles) {
        if (bubble.getAliveStatus()) {
            alives.push_back(bubble);
        }
    }

    this->bubbles = alives;
}

void Board::markOutsideBubbles() {
    for (Bubble& bubble : this->bubbles) {
        if (bubble.getCoordinates().second > int(this->window.getSize().y) + Bubble::RADIUS) {
            this->missBubble(bubble);
        }
    }
}

void Board::missBubble(Bubble &bubble) {
    if (this->currentHits > 10) {
        this->comboBreakAudio.play();
    } else {
        this->errorAudio.play();
    }

    bubble.setAliveStatus(false);

    this->totalMisses++;

    if (this->currentHits > this->bestStreak) {
        this->bestStreak = this->currentHits;
    }

    this->currentHits = 0;
}

void Board::missBubble() {
    if (this->currentHits > 10) {
        this->comboBreakAudio.play();
    } else {
        this->errorAudio.play();
    }

    this->totalMisses++;

    if (this->currentHits > this->bestStreak) {
        this->bestStreak = this->currentHits;
    }

    this->currentHits = 0;
}

bool Board::checkHit(const Bubble &bubble) {
    std::pair<int, int> mouseCoordinates {this->cursor.getCursorCoordinates()};
    std::pair<int, int> bubbleCoordinates {bubble.getCoordinates()};

    double distance {std::sqrt(std::pow(mouseCoordinates.first - bubbleCoordinates.first, 2) + std::pow(mouseCoordinates.second - bubbleCoordinates.second, 2))};
    
    return distance <= Bubble::RADIUS;
}

void Board::markByHit(char letter) {
    for (std::vector<Bubble>::reverse_iterator rit = this->bubbles.rbegin(); rit != this->bubbles.rend(); ++rit) {
        if (this->checkHit(*rit)) {
            if (rit->getLetter() == letter) {
                rit->setAliveStatus(false);

                this->hitAudio.play();
                this->currentHits++;
                this->totalHits++;
            } else {
                this->missBubble(*rit);
            }

            return;
        }
    }

    this->missBubble();
}

void Board::addNewBubble() {
    int x = rand() % (int(this->window.getSize().x) - Bubble::RADIUS - Bubble::RADIUS + 1) + Bubble::RADIUS;
    int y = -2 * Bubble::RADIUS;
    double speed = (rand() % 5 + 1) / 2.0;
    char letter = rand() % 2 == 1 ? 'D' : 'F';
    bubbles.push_back(Bubble(x, y, letter, speed));
}

void Board::draw(const sf::Sprite &backgroundSprite) {
    this->window.clear(sf::Color::Black);

    this->window.draw(backgroundSprite);

    for (Bubble &bubble : this->bubbles) {
        bubble.draw(this->window);
    }

    this->pencil.write("Current hits: " + std::to_string(this->currentHits) + " || Misses: " + std::to_string(this->totalMisses), 10, 10, 20, sf::Color::White);

    this->cursor.draw();

    this->window.display();
}

void Board::lose() {
    this->failAudio.play();

    this->currentHits = 0;
    this->bestStreak = 0;
    this->totalHits = 0;
    this->totalMisses = 0;
    this->bubbles.clear();
}

int Board::getTotalMisses() const {
    return this->totalMisses;
}

int Board::getTotalHits() const {
    return this->totalHits;
}

int Board::getBestStreak() const {
    return this->bestStreak;
}