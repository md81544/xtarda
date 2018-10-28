#pragma once

#include <random>

namespace utils
{
class GameGlobals
{
public:
    static GameGlobals& Instance()
    {
        static GameGlobals globals;
        return globals;
    }
    int screenWidth = 800;
    int screenHeight = 600;
private:
    GameGlobals(){}
};

class Rnd
{
public:
    Rnd();
    float   getFloat( float from, float to );
    int     getInt( int from, int to );
private:
    std::random_device m_rd;
    std::mt19937 m_gen;
};
}