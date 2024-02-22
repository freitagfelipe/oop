#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "../menu/menu.hpp"
#include "../board/board.hpp"
#include "../end/end.hpp"
#include "../cursor/cursor.hpp"

class Game {
private:
    sf::RenderWindow window;
    Cursor cursor;
    Menu menu;
    End endgame;
    Board board;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::function<void()> onUpdate;
    enum {INIT_SCREEN, GAME_SCREEN, END_SCREEN } gameState;

public:
    static const int WIDTH = 800;
    static const int HEIGHT = 600;

    Game();
    void processEvents();
    void getBackground() const;
    void displayMenu();
    void gameplay();
    void gameOver();
    void mainLoop();
};