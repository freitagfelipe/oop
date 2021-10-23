#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

void loadTexture(sf::Texture& texture, std::string path) {
    if (!texture.loadFromFile(path)) {
        std::cout << "Error loading texture" << std::endl;

        exit(1);
    }
}