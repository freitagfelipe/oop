#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

const int SCREEN_WIDTH = 950;
const int SCREEN_HEIGHT = 800;

const int STEP = 50;

const int PLAYER_ONE_SPAWN_Y = 725;
const int LIFE_BAR_PLAYER_ONE_POSY = SCREEN_HEIGHT - 30;
const std::vector<sf::Keyboard::Key> MOVE_KEYS_PLAYER_ONE = { sf::Keyboard::A, sf::Keyboard::D };
const sf::Keyboard::Key SHOOT_KEY_PLAYER_ONE = sf::Keyboard::S;

const int PLAYER_TWO_SPAWN_Y = 75;
const int LIFE_BAR_PLAYER_TWO_POSY = 10;
const std::vector<sf::Keyboard::Key> MOVE_KEYS_PLAYER_TWO = { sf::Keyboard::Left, sf::Keyboard::Right };
const sf::Keyboard::Key SHOOT_KEY_PLAYER_TWO = sf::Keyboard::Down;