#pragma once

#include <SFML/Graphics.hpp>
#include "../pencil/pencil.hpp"
#include "../cursor/cursor.hpp"
#include "../audio/audio.hpp"

class Menu {
private:
    sf::RenderWindow &window;
    Pencil pencil;
    Cursor &cursor;
    Audio startAudio;
    sf::Color startTextColor;
    sf::Color exitTextColor;

public:
    Menu(sf::RenderWindow &window, Cursor &cursor);
    void update();
    bool checkButtonPressed(sf::Mouse::Button buttonPressed);
    void draw(const sf::Sprite &backgroundSprite);
};