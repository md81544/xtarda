#include "asteroid.h"
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
        // TODO - better exception type
        throw std::runtime_error( "Could not load texture" );
    }
    m_sprite.setTexture( m_texture );
    m_sprite.setPosition( x, y );
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
    // TODO: remove hard-coded numbers:
    auto fr = m_sprite.getGlobalBounds();
    if ( vec.x < -fr.width || vec.x > utils::GameGlobals::Instance().screenWidth ) m_speed = -m_speed;
    m_sprite.setPosition( vec );
}