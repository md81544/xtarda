#include "exceptions.h"
#include "isprite.h"

#include <memory>

ISprite::ISprite( const std::string& filename, float scale )
{
    if ( !m_texture.loadFromFile( filename ) )
    {
        throw mgo::XtardaFileException( "Could not load file " + filename );
    }
    if ( scale != 1.f )
    {
        m_texture.setSmooth( true );
    }
    m_sprite = std::make_unique<sf::Sprite>( m_texture );
    m_sprite->setScale( scale, scale );
}

ISprite::ISprite( const sf::Image& img, float scale )
{
    if ( !m_texture.loadFromImage( img ) )
    {
        throw mgo::XtardaGeneralException( "Could not load image" );
    }
    m_sprite = std::make_unique<sf::Sprite>( m_texture );
    m_sprite->setScale( scale, scale );
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
