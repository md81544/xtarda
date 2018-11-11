#include "exceptions.h"
#include "isprite.h"

#include <memory>

ISprite::ISprite( const std::string& filename )
{
    if ( !m_texture.loadFromFile( filename ) )
    {
        throw mgo::XtardaFileException( "Could not load file " + filename );
    }
    m_sprite = std::make_unique<sf::Sprite>( m_texture );
}

void ISprite::draw( sf::RenderWindow& window )
{
    window.draw( *m_sprite );
}

float ISprite::getVerticalSpeed()
{
    return m_verticalSpeed;
}

float ISprite::getHorizontalSpeed()
{
    return m_horizontalSpeed;
}

void  ISprite::setVerticalSpeed( float s)
{
    m_verticalSpeed = s;
}

void  ISprite::setHorizontalSpeed( float s)
{
    m_horizontalSpeed = s;
}

void ISprite::setPosition( sf::Vector2f pos )
{
    m_sprite->setPosition( pos );
}

sf::Vector2f ISprite::getPosition()
{
    return m_sprite->getPosition();
}
