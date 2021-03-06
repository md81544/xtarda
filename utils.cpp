#include "utils.h"
#include "asteroid.h"
#include "collision.h"
#include "isprite.h"
#include "log.h"
#include "readconfig.h"

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>

namespace utils
{

Rnd::Rnd()
: m_gen( m_rd() )
{}

float Rnd::getFloat( float from, float to )
{
    std::uniform_real_distribution<> dis(
        static_cast<double>(from), static_cast<double>(to) );
    return static_cast<float>( dis( m_gen ) ); 
}

int Rnd::getInt( int from, int to )
{
    std::uniform_int_distribution<> dis( from, to );
    return dis( m_gen ); 
}

void getConfiguration()
{
    std::string configFile = "xtarda.cfg";
    try
    {
        mgo::config::Reader cfg( configFile );
        GameGlobals::instance().screenWidth =
            static_cast<int>( cfg.readLong( "ScreenWidth", 1200 ) );
        GameGlobals::instance().screenHeight =
            static_cast<int>( cfg.readLong( "ScreenHeight", 800 ) );
        GameGlobals::instance().scaleFactor =
            cfg.readFloat( "ScaleFactor", 1.f );
    }
    catch ( const std::exception& e )
    {
        MGOLOG( e.what() );
    }
}

bool asteroidCollisionCheck(
    const sf::Sprite& ship,
    const std::vector<std::unique_ptr<ISprite>>& asteroids
    )
{
    for ( const auto& a : asteroids )
    {
        if( collision::PixelPerfectTest( ship, a->getSprite() ) )
        {
            return true;
        }
    }
    return false;
}

void centre( sf::Text& sp )
{
    float width = sp.getLocalBounds().width;
    auto v2f = sp.getPosition();
    v2f.x = ( utils::GameGlobals::instance().screenWidth - width ) / 2;
    sp.setPosition( v2f );
}

std::string toStringRounded( float num, int decimalPlaces )
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(decimalPlaces) << num;
    return oss.str();
}

} // namespace utils