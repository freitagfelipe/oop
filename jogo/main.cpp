#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include "./entitys/player.hpp"
#include "./enviroment/terrain.hpp"
#include "./utils/texture.hpp"
#include "./utils/sound.hpp"
#include "./utils/constants.hpp"
#include "./utils/types.hpp"

int main() {
    std::srand(std::time(NULL));

    sf::Texture playerOneTexture, playerTwoTexture, enemyTexture, terrainTexture, rockTexture, lifeTexture;
    sf::SoundBuffer playerOneShotSoundBuffer, playerTwoShotSoundBuffer;

    std::string wichMap = rand() % 2 == 1 ? "./assets/tile_one.png" : "./assets/tile_two.png";

    loadTexture(playerOneTexture, "./assets/shooter_green.png");
    loadTexture(playerTwoTexture, "./assets/shooter_red.png");
    loadTexture(rockTexture, "./assets/rock.png");
    loadTexture(lifeTexture, "./assets/life.png");
    loadTexture(terrainTexture, wichMap);
    loadSound(playerOneShotSoundBuffer, "./sounds/shot_green.wav");
    loadSound(playerTwoShotSoundBuffer, "./sounds/shot_red.wav");

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");

    Terrain board(STEP, terrainTexture, rockTexture);
    Player playerOne(PLAYER_ONE_SPAWN_Y, STEP, UP, MOVE_KEYS_PLAYER_ONE, SHOOT_KEY_PLAYER_ONE, board.getRockPositions(), LIFE_BAR_PLAYER_ONE_POSY, playerOneShotSoundBuffer, lifeTexture, playerOneTexture);
    Player playerTwo(PLAYER_TWO_SPAWN_Y, STEP, DOWN, MOVE_KEYS_PLAYER_TWO, SHOOT_KEY_PLAYER_TWO, board.getRockPositions(), LIFE_BAR_PLAYER_TWO_POSY, playerTwoShotSoundBuffer, lifeTexture, playerTwoTexture);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                playerOne.playerAction(event.key.code, playerTwo);
                playerTwo.playerAction(event.key.code, playerOne);
            }
        }

        window.clear();

        board.draw(window);
        playerOne.draw(window);
        playerTwo.draw(window);

        window.display();
    }

    return 0;
}