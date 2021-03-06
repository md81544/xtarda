#include "ship.h"
#include "utils.h"

Ship::Ship( const std::string& filename, float scale )
:   ISprite( filename, scale )
{
    m_verticalSpeed = 0.2f;
    m_sprite->setOrigin( { 30.f, 23.f } );
}

void Ship::adjustSpeed( float vertAdjust, float horizAdjust )
{
    if ( m_landed ) return;
    m_verticalSpeed   += vertAdjust;
    m_horizontalSpeed += horizAdjust;
}

void Ship::adjustAcceleration( float mult )
{
    m_acceleration *= mult;
}

void Ship::move()
{
    m_sprite->move( { m_horizontalSpeed, m_verticalSpeed } );
    m_verticalSpeed += m_acceleration;
}

bool Ship::checkLanded()
{
    auto v = m_sprite->getPosition();
    if ( v.y >= utils::GameGlobals::instance().screenHeight -
            m_sprite->getLocalBounds().height + 10
        )
    {
        return true;
    }
    return false;
}
