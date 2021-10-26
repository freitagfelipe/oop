#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Cursor {
private:
    sf::RenderWindow &window;
    sf::Sprite cursorSprite;
    sf::Texture cursorTexture;
    
public:
    Cursor(sf::RenderWindow &window);
    void draw();
    std::pair<int, int> getCursorCoordinates() const;
};