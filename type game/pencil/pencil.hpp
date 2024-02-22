#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Pencil {
private:
    sf::Font font;
    sf::Text text;
    sf::RenderWindow &window;

public:
    Pencil(sf::RenderWindow &window);
    void write(std::string text, int x, int y, int size, sf::Color color);
    void write(std::string text, int y, int size, sf::Color color);
};