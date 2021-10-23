#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

void loadSound(sf::SoundBuffer& soundVariable, std::string path) {
    if (!soundVariable.loadFromFile(path)) {
        std::cout << "Error loading sound!" << std::endl;

        exit(1);
    }
}