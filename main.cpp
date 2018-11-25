#include "asteroid.h"
#include "gameLoop.h"
#include "ship.h"
#include "utils.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>


int main()
{
    using namespace utils;
    try
    {
        GameLoop gameLoop( GameGlobals::screenWidth, GameGlobals::screenHeight );
        std::vector<std::unique_ptr<ISprite>> asteroids;

        Ship ship( "resources/spaceship.png" );
        ship.setPosition(
            { GameGlobals::screenWidth / 2.f, 0.f }
            );
        gameLoop.registerDrawable( &(ship.getSprite()) );

        Rnd rnd;
        for ( int n = 0; n < 36; ++n )
        {
            std::string filename =
                "resources/asteroid" +
                std::to_string( rnd.getInt(1,4) ) + ".png";
            asteroids.push_back( std::make_unique<Asteroid>(
                    filename,
                    static_cast<float>( rnd.getInt(
                        100,
                        GameGlobals::screenWidth - 100
                        )),                       // x
                    100.f + n * 15.f,             // y
                    rnd.getFloat( -2.5f, 2.5f )   // speed
                    )
                );
            gameLoop.registerDrawable( &(asteroids.back()->getSprite()) );
        }

        sf::RectangleShape ground(
            sf::Vector2f(
                static_cast<float>( GameGlobals::screenWidth ),
                10.f
                )
            );
        ground.setFillColor( sf::Color( 94, 68, 4 ) );
        ground.setPosition(
            sf::Vector2f(
                0.f,
                GameGlobals::screenHeight - 10.f
                )
            );
        gameLoop.registerDrawable( &ground );

        sf::Font font;
        if ( !font.loadFromFile( "resources/zxspectrum.ttf" ) )
        {
            return EXIT_FAILURE;
        }
        sf::Text text( "Xtarda Rescue", font, 20 );
        text.setFillColor( sf::Color::Green );
        text.setPosition(
            sf::Vector2f(
                ( GameGlobals::screenWidth -
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
        std::cout << e.what() << std::endl;
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
