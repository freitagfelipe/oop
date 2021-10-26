#include "game.hpp"

Game::Game() : window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Type Game", sf::Style::Titlebar | sf::Style::Close), cursor {window}, menu {window, cursor}, endgame {window, cursor}, board(window, cursor) {
    std::srand(std::time(NULL));

    if (!this->backgroundTexture.loadFromFile("./assets/textures/background.jpeg")) {
        std::cout << "Error: failed to load background.jpeg!" << std::endl;

        exit(1);
    }

    this->backgroundSprite.setTexture(this->backgroundTexture);

    sf::FloatRect backGroundDimension = this->backgroundSprite.getLocalBounds();

    this->backgroundSprite.setOrigin(backGroundDimension.width / 2, backGroundDimension.height / 2);
    this->backgroundSprite.setPosition(Game::WIDTH / 2, Game::HEIGHT / 2);
    this->backgroundSprite.setScale(0.6, 0.6);

    this->onUpdate = [&]() {
        this->displayMenu();
    };
    
    this->window.setFramerateLimit(120);
    this->window.setMouseCursorVisible(false);
    this->gameState = INIT_SCREEN;
}

void Game::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        } else if (event.type == sf::Event::TextEntered && this->gameState == GAME_SCREEN) {
            char code = std::toupper(static_cast<char>(event.text.unicode));

            this->board.markByHit(code);
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (this->gameState == END_SCREEN) {
                if (this->endgame.checkContinue(event.mouseButton.button)) {
                    this->onUpdate = [&]() {
                        this->displayMenu();
                    };

                    this->gameState = INIT_SCREEN;
                }
            } else if (this->gameState == INIT_SCREEN) {
                if (this->menu.checkButtonPressed(event.mouseButton.button)) {
                    this->onUpdate = [&]() {
                        this->gameplay();
                    };

                    this->gameState = GAME_SCREEN;
                }
            }
        }
    }
}

void Game::displayMenu() {
    this->menu.update();
    this->menu.draw(this->backgroundSprite);
}

void Game::gameplay() {
    this->board.update();
    this->board.draw(this->backgroundSprite);

    if (board.getTotalMisses() >= 10) {
        this->onUpdate = [&]() {
            this->gameOver();
        };

        this->endgame.setScores(this->board.getBestStreak(), this->board.getTotalHits());
        this->board.lose();

        this->gameState = END_SCREEN;
    }
}

void Game::gameOver() {
    this->endgame.update();
    this->endgame.draw(this->backgroundSprite);
}

void Game::mainLoop() {
    while (this->window.isOpen()) {
        this->processEvents();
        this->onUpdate();
    }
}