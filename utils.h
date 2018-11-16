#pragma once

#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <vector>

class ISprite;

namespace utils
{

struct GameGlobals
{
    static const int screenWidth { 1280 };
    static const int screenHeight{  800 };
};

class Rnd
{
public:
    Rnd();
    float getFloat( float from, float to );
    int   getInt( int from, int to );
private:
    std::random_device m_rd;
    std::mt19937 m_gen;
};

bool asteroidCollisionCheck(
    const sf::Sprite& ship,
    const std::vector<std::unique_ptr<ISprite>>& asteroids
    );

void centre( sf::Text& sp );

} // namespace utils
