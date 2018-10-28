#include "utils.h"
#include "asteroid.h"
#include "collision.h"

#include <SFML/Graphics.hpp>

namespace utils
{
    Rnd::Rnd()
    : m_gen( m_rd() )
    {}

    float Rnd::getFloat( float from, float to )
    {
        std::uniform_real_distribution<> dis( from, to );
        return dis( m_gen ); 
    }

    int Rnd::getInt( int from, int to )
    {
        std::uniform_int_distribution<> dis( from, to );
        return dis( m_gen ); 
    }

    bool asteroidCollisionCheck(
        const sf::Sprite& ship,
        const std::vector<std::unique_ptr<Asteroid>>& asteroids
        )
    {
        for ( const auto& a : asteroids )
        {
            if( collision::PixelPerfectTest( ship, a->sprite() ) )
            {
                return true;
            }
        }
        return false;
    }
}