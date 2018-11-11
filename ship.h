#include "isprite.h"

class Ship : public ISprite
{
public:
    Ship( const std::string& filename );
    // temporary
    sf::Sprite& sprite()
    {
        return *m_sprite;
    }
    void adjustSpeed( float vertAdjust, float horizAdjust );
    void adjustAcceleration( float mult );
    void move() override;
private:
    //bool  m_landed{ false };     // TODO - use
    //bool  m_crashing{ false };   // TOOD - use
    float m_acceleration{ 0.01f };
};