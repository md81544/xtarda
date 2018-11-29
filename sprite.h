#include "isprite.h"

// General sprite class, does nothing other than
// get displayed at the moment (for the star backdrop)

class Sprite: public ISprite
{
public:
    Sprite( const std::string& filename, float scale )
    : ISprite( filename, scale )
    {}
    void move() override {};
};