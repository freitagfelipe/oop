#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include "../bubble/bubble.hpp"
#include "../pencil/pencil.hpp"
#include "../cursor/cursor.hpp"
#include "../audio/audio.hpp"

class Board {
private:
    sf::RenderWindow &window;
    std::vector<Bubble> bubbles;
    Pencil pencil;
    Cursor &cursor;
    Audio hitAudio;
    Audio comboBreakAudio;
    Audio failAudio;
    Audio errorAudio;
    int currentHits;
    int bestStreak;
    int totalHits;
    int totalMisses;

public:
    Board(sf::RenderWindow &window, Cursor &cursor);
    void update();
    bool checkNewBubble();
    void removeDeadBubbles();
    void markOutsideBubbles();
    bool checkHit(const Bubble &bubble);
    void markByHit(char letter);
    void addNewBubble();
    void missBubble(Bubble &bubble);
    void missBubble();
    void draw(const sf::Sprite &backgroundSprite);
    void lose();
    int getTotalMisses() const;
    int getTotalHits() const;
    int getBestStreak() const;
};