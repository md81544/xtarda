#include "isprite.h"

class Ship : public ISprite
{
public:
    Ship( const std::string& filename )
    :   ISprite( filename )
    {
        m_verticalSpeed = 0.2f;
    }

    // temporary
    sf::Sprite& sprite()
    {
        return *m_sprite;
    }

    void adjustSpeed( float vertAdjust, float horizAdjust )
    {
        m_verticalSpeed   += vertAdjust;
        m_horizontalSpeed += horizAdjust;
    }

    void adjustAcceleration( float mult )
    {
        m_acceleration *= mult;
    }

    void move()
    {
        m_sprite->move( { m_horizontalSpeed, m_verticalSpeed } );
        m_verticalSpeed += m_acceleration;
    }

private:
    bool m_landed{ false };     // TODO - use
    bool m_crashing{ false };   // TOOD - use
    float m_acceleration{ 0.01f };
};