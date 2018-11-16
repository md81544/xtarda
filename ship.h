#include "isprite.h"

class Ship : public ISprite
{
public:
    Ship( const std::string& filename );
    void adjustSpeed( float vertAdjust, float horizAdjust );
    void adjustAcceleration( float mult );
    void move() override;
    void setLanded( bool landed ) { m_landed = landed; }
    bool landed() { return m_landed; }
    void setCrashed( bool crashed ) { m_crashed = crashed; }
    bool crashed() { return m_crashed; }
private:
    bool  m_landed{ false };     // TODO - use
    bool  m_crashed{ false };   // TOOD - use
    float m_acceleration{ 0.01f };
};