#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include "../utils/types.hpp"
#include "../utils/constants.hpp"

struct Terrain {
private:
    int step;
    sf::Sprite tileSprite, stoneSprite;
    std::vector<Stone> stones;

    void setTileSprite(sf::Texture &tileTexture) {
        this->tileSprite.setTexture(tileTexture);

        sf::FloatRect dimension = this->tileSprite.getLocalBounds();

        this->tileSprite.setScale(float(this->step) / dimension.width, float(this->step) / dimension.height);
    }

    void setStoneSprite(sf::Texture &stoneTexture) {
        this->stoneSprite.setTexture(stoneTexture);

        sf::FloatRect dimension = this->stoneSprite.getLocalBounds();

        this->stoneSprite.setScale(float(this->step) / dimension.width, float(this->step) / dimension.height);
    }

    void setStone() {
        Stone stone;

        stone.stoneSprite = this->stoneSprite;

        for (int i = 0; i < 10; i++) {
            stone.posX = rand() % 15 * this->step;
            stone.posY = rand() % 7 * this->step + 150; 
            
            stone.stoneSprite.setPosition(stone.posX, stone.posY);

            this->stones.push_back(stone);
        }
    }

public:
    Terrain(int step, sf::Texture &tileTexture, sf::Texture &stoneTexture) {
        this->step = step;
        this->setTileSprite(tileTexture);
        this->setStoneSprite(stoneTexture);
        this->setStone();
    }

    void draw(sf::RenderWindow &window) {
        for (int i = 0; i < SCREEN_WIDTH / step; i++) {
            for (int j = 0; j < SCREEN_HEIGHT / step; j++) {
                this->tileSprite.setPosition(i * this->step, j * this->step);

                window.draw(this->tileSprite);
            } 
        }
        
        for (Stone stone : this->stones) {
            window.draw(stone.stoneSprite);
        }
    }

    std::vector<Stone> getRockPositions() {
        return this->stones;
    }
};