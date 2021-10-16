#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../utils/types.hpp"
#include "../utils/constants.hpp"

struct Player {
private:
    int posX, fixedYPos, lifeBarPosY, step, life {5};
    std::vector<Stone> stones;
    sf::Sprite playerSprite, lifeSprite;
    std::vector<sf::Keyboard::Key> moveKeys;
    sf::Keyboard::Key shootKey;
    sf::Sound shotSound;
    Direction direction;

    void setPlayerSprite(sf::Texture& playerTexture) {
        this->playerSprite.setTexture(playerTexture);

        sf::FloatRect dimension = this->playerSprite.getLocalBounds();

        this->playerSprite.setScale(float(this->step) / dimension.width, float(this->step) / dimension.height);
        this->playerSprite.setOrigin(dimension.width / 2, dimension.height / 2);
    }

    void setLifeSprite(sf::Texture& lifeTexture) {
        this->lifeSprite.setTexture(lifeTexture);

        sf::FloatRect dimension = this->lifeSprite.getLocalBounds();

        this->lifeSprite.setScale(float(this->step / 2) / dimension.width, float(this->step / 2) / dimension.height);
    }

    void setSound(sf::SoundBuffer& shotSoundBuffer) {
        this->shotSound.setBuffer(shotSoundBuffer);
        this->shotSound.setVolume(30);
    }

public:
    Player(int fixedYPos, int step, Direction direction, std::vector<sf::Keyboard::Key> moveKeys, sf::Keyboard::Key shootKey, std::vector<Stone> stones, int lifeBarPosY, sf::SoundBuffer& shotSoundBuffer, sf::Texture& lifeTexture, sf::Texture& playerTexture) {
        this->fixedYPos = fixedYPos;
        this->lifeBarPosY = lifeBarPosY;
        this->step = step;
        this->posX = rand() % 15 * this->step + 25;
        this->direction = direction;
        this->moveKeys = moveKeys;
        this->shootKey = shootKey;
        this->stones = stones;
        this->setSound(shotSoundBuffer);
        this->setPlayerSprite(playerTexture);
        this->setLifeSprite(lifeTexture);
    }

    void draw(sf::RenderWindow &window) {
        this->playerSprite.setPosition(this->posX, this->fixedYPos);

        for (int i = 0; i < this->life; i++) {
            this->lifeSprite.setPosition(20 * i, this->lifeBarPosY);

            window.draw(this->lifeSprite);
        }

        window.draw(this->playerSprite);
    }

    void playerAction(sf::Keyboard::Key key, Player &otherPlayer) {
        if (std::find(this->moveKeys.begin(), this->moveKeys.end(), key) != moveKeys.end()) {
            if (key == moveKeys.at(0) && this->posX > this->step) {
                this->posX -= this->step;

                this->rotateSprite(key);
            } else if (key == moveKeys.at(1) && this->posX < SCREEN_WIDTH - this->step) {
                this->posX += this->step;

                this->rotateSprite(key);
            }
        } else if (key == this->shootKey) {
            this->shot(otherPlayer);
            this->rotateSprite(key);
        }
    }

    void rotateSprite(sf::Keyboard::Key key) {
        if (key == this->shootKey) {
            this->playerSprite.setRotation(0);
        } else if (std::find(this->moveKeys.begin(), this->moveKeys.end(), key) != moveKeys.end()) {
            if (key == this->moveKeys.at(0)) {
                this->playerSprite.setRotation(-90 * this->direction);
            } else {
                this->playerSprite.setRotation(90 * this->direction);
            }
        }
    }

    void dead() {
        this->posX = -100;
        this->fixedYPos = -100;
    }

    void shot(Player &otherPlayer) {
        bool shootCanPass = true;
        this->shotSound.play();

        if (this->posX == otherPlayer.posX) {
            for (Stone &stone : this->stones) {
                if (this->posX == stone.posX + 25) {
                    stone.posY = -100;
                    shootCanPass = false;

                    break;
                }
            }

            if (shootCanPass) {
                otherPlayer.life--;
            }
        }

        if (otherPlayer.life == 0) {
            otherPlayer.dead();
        }
    }
};