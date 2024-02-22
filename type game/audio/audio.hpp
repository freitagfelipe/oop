#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class Audio {
private:
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;

public:
    Audio(std::string path, int volume);
    void play();
};