#include "asteroid.h"
#include "gameLoop.h"
#include "initialise.h"
#include "log.h"
#include "ship.h"
#include "sprite.h"
#include "utils.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <vector>


int main()
{
    using namespace utils;
    INIT_MGOLOG( "xtarda.log" );
    MGOLOG( "Initialising" );
    utils::getConfiguration();
    try
    {
        GameLoop gameLoop(
            GameGlobals::instance().screenWidth,
            GameGlobals::instance().screenHeight
            );

        Sprite stars( "resources/stars.jpg", GameGlobals::instance().scaleFactor );
        gameLoop.registerDrawable( &(stars.getSprite()) );

        Ship ship( "resources/spaceship.png", GameGlobals::instance().scaleFactor );
        ship.setPosition(
            { GameGlobals::instance().screenWidth / 2.f, 0.f }
            );
        gameLoop.registerDrawable( &(ship.getSprite()) );

        std::vector<std::unique_ptr<ISprite>> asteroids;
        init::createAsteroids( gameLoop, asteroids );

        auto ground = init::createGround( gameLoop );

        sf::Font font;
        if ( !font.loadFromFile( "resources/zxspectrum.ttf" ) )
        {
            return EXIT_FAILURE;
        }
        sf::Text text( "Xtarda Rescue", font, 20 );
        text.setFillColor( sf::Color::Green );
        text.setPosition(
            sf::Vector2f(
                ( GameGlobals::instance().screenWidth -
                  text.getGlobalBounds().width) / 2,
                10
                )
            );
        gameLoop.registerDrawable( &text );

        // set up our callbacks for keypresses
        gameLoop.registerKeyHandler(
            sf::Keyboard::Up,
            [ &ship ] () { ship.adjustSpeed( -0.05f, 0 ); }
            );
        gameLoop.registerKeyHandler(
            sf::Keyboard::Down,
            [ &ship ] () { ship.adjustSpeed( 0.05f, 0 ); }
            );
        gameLoop.registerKeyHandler(
            sf::Keyboard::Right,
            [ &ship ] () { ship.adjustSpeed( 0, 0.05f ); }
            );
        gameLoop.registerKeyHandler(
            sf::Keyboard::Left,
            [ &ship ] () { ship.adjustSpeed( 0, -0.05f ); }
            );


        while( gameLoop.isWindowOpen() )
        {
            // Process events makes the callbacks specified above
            // if the keys are pressed
            gameLoop.processEvents();
            if ( !ship.landed() )
            {
                ship.move();
            }

            if ( ship.checkLanded() )
            {
                // landed
                float descentSpeed = ship.getVerticalSpeed();
                if ( descentSpeed > 0.4f )
                {
                    text.setString(
                        "Crash!! " + std::to_string( descentSpeed ) );
                }
                else
                {
                    text.setString(
                        "Landed. " + std::to_string( descentSpeed ) );
                }
                ship.setLanded( true );
            }

            // Collision checking
            if ( !ship.crashed() && asteroidCollisionCheck( ship.getSprite(), asteroids ) )
            {
                ship.setCrashed( true );
                ship.adjustAcceleration( 5.f );
                text.setString( "Crashed into asteroid" );
            }
            if( ship.crashed() && !ship.landed() )
            {
                ship.getSprite().setRotation( ship.getSprite().getRotation() + 2.f );
            }

            utils::centre( text );
            gameLoop.updateDisplay();
            for ( auto& a : asteroids )
            {
                a->move();
            }
        }
    }
    catch ( const std::exception& e )
    {
        MGOLOG( e.what() );
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#ifdef _WIN32
int WinMain()
{
    main();
}
#endif
