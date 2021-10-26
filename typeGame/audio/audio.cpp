#include "audio.hpp"

Audio::Audio(std::string path, int volume) {
    if (!this->soundBuffer.loadFromFile(path)) {
        std::cout << "Error: can't find " + path + "!" << std::endl;

        exit (1);
    }

    this->sound.setBuffer(this->soundBuffer);
    this->sound.setVolume(volume);
}

void Audio::play() {
    this->sound.play();
}