#pragma once

#include <SFML/Graphics.hpp>

struct Stone {
    int posX, posY;
    sf::Sprite stoneSprite;
};

enum Direction { UP = 1, DOWN = -1 };