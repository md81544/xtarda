#pragma once

#include "readconfig.h"

#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <vector>

class ISprite;

namespace utils
{

struct GameGlobals
{
    static GameGlobals& instance()
    {
        static GameGlobals globals;
        return globals;
    }

    int   screenWidth { 1280 };
    int   screenHeight{  800 };
    float scaleFactor { 1.f };
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

void getConfiguration();

bool asteroidCollisionCheck(
    const sf::Sprite& ship,
    const std::vector<std::unique_ptr<ISprite>>& asteroids
    );

void centre( sf::Text& sp );

} // namespace utils
