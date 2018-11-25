#include "asteroid.h"
#include "exceptions.h"
#include "utils.h"

Asteroid::Asteroid(
    const std::string& filename,
    float x,
    float y,
    float speed,
    float scale
    )
    : ISprite( filename, scale )
{
    m_horizontalSpeed = speed;
    m_sprite->setPosition( { x, y } );
    auto sz = m_sprite->getLocalBounds();
    m_sprite->setOrigin( sz.width / 2, sz.height / 2 );
}

void Asteroid::move()
{
    auto vec = m_sprite->getPosition();
    vec.x += m_horizontalSpeed;
    auto fr = m_sprite->getGlobalBounds();
    if ( vec.x < -fr.width ||
         vec.x > utils::GameGlobals::instance().screenWidth
        )
    {
        m_horizontalSpeed = -m_horizontalSpeed;
    }
    m_sprite->setPosition( vec );
    m_sprite->setRotation( m_sprite->getRotation() + 1.f );
}