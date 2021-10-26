#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../pencil/pencil.hpp"

class Bubble {
private:
    sf::Texture bubbleTexture;
    int x;
    double y;
    char letter;
    double speed;
    bool alive;

public:
    static const int RADIUS {30};

    Bubble(int x, int y, char letter, double speed);
    void update();
    void draw(sf::RenderWindow &window);
    void setAliveStatus(bool status);
    bool getAliveStatus() const;
    char getLetter() const;
    std::pair<int, int> getCoordinates() const;
};