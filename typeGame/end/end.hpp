#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../pencil/pencil.hpp"
#include "../cursor/cursor.hpp"
#include "../audio/audio.hpp"

class End {
private:
    sf::RenderWindow &window;
    Pencil pencil;
    Cursor &cursor;
    Audio audio;
    sf::Color continueTextColor;
    int bestStreak;
    int totalHits;

public:
    End(sf::RenderWindow &window, Cursor &cursor);
    void update();
    void draw(const sf::Sprite &backgroundSprite);
    void setScores(int bestStreak, int totalHits);
    bool checkContinue(sf::Mouse::Button buttonPressed);
};