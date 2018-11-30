#include "initialise.h"

#include "asteroid.h"
#include "gameLoop.h"
#include "isprite.h"
#include "utils.h"

void init::createAsteroids(
    GameLoop& gameLoop,
    std::vector<std::unique_ptr<ISprite>>& vec
)
{
    utils::Rnd rnd;
    for ( int n = 0; n < 36; ++n )
    {
        std::string filename =
            "resources/asteroid" +
            std::to_string( rnd.getInt(1,4) ) + ".png";
        vec.push_back( std::make_unique<Asteroid>(
                filename,
                static_cast<float>( rnd.getInt(
                        100,
                        utils::GameGlobals::instance().screenWidth - 100
                        )
                    ),                         // x
                100.f + n * 15.f,              // y
                rnd.getFloat( -2.5f, 2.5f ),   // speed
                rnd.getFloat( -5.f, 5.f ),   // rotation
                utils::GameGlobals::instance().scaleFactor
                )
            );
        gameLoop.registerDrawable( &(vec.back()->getSprite()) );
    }
}
