#include "initialise.h"

#include "asteroid.h"
#include "gameLoop.h"
#include "isprite.h"
#include "utils.h"

#include "SFML/Graphics.hpp"

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

std::unique_ptr<sf::RectangleShape> init::createGround(
    GameLoop& gameLoop
    )
{
    auto ground = std::make_unique<sf::RectangleShape>(
        sf::Vector2f(
            static_cast<float>( utils::GameGlobals::instance().screenWidth ),
            10.f
            )
        );
    ground->setFillColor( sf::Color( 94, 68, 4 ) );
    ground->setPosition(
        sf::Vector2f(
            0.f,
            utils::GameGlobals::instance().screenHeight - 10.f
            )
        );
    gameLoop.registerDrawable( ground.get() );
    return ground;
}
