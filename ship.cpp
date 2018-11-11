#include "ship.h"

Ship::Ship( const std::string& filename )
:   ISprite( filename )
{
    m_verticalSpeed = 0.2f;
}

void Ship::adjustSpeed( float vertAdjust, float horizAdjust )
{
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