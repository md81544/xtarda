#include "asteroid.h"
#include "exceptions.h"
#include "utils.h"

Asteroid::Asteroid(
    const std::string& filename,
    float x,
    float y,
    float speed
    )
    : m_speed( speed )
{
    if ( !m_texture.loadFromFile( filename ) )
    {
        throw mgo::XtardaFileException( "Could not load file " + filename );
    }
    m_sprite.setTexture( m_texture );
    m_sprite.setPosition( x, y );
    auto sz = m_sprite.getLocalBounds();
    m_sprite.setOrigin( sz.width / 2, sz.height / 2 );
}

// TODO remove this
sf::Sprite& Asteroid::sprite()
{
    return m_sprite;
}

sf::Vector2f Asteroid::getPosition()
{
    return m_sprite.getPosition();
}

void Asteroid::setPosition( const sf::Vector2f& v )
{
    m_sprite.setPosition( v );
}

void Asteroid::move()
{
    auto vec = m_sprite.getPosition();
    vec.x += m_speed;
    auto fr = m_sprite.getGlobalBounds();
    if ( vec.x < -fr.width || vec.x > utils::GameGlobals::Instance().screenWidth ) m_speed = -m_speed;
    m_sprite.setPosition( vec );
    m_sprite.setRotation( m_sprite.getRotation() + 1.f );
}