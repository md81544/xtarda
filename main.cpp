#include "asteroid.h"
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
    GameGlobals::Instance().screenWidth = 1280;
    GameGlobals::Instance().screenHeight = 800;
    try
    {
        bool landed = false;
        bool crashing = false;
        sf::RenderWindow window(
            sf::VideoMode(
                GameGlobals::Instance().screenWidth,
                GameGlobals::Instance().screenHeight,
                32
                ),
            "Xtarda Rescue",
            sf::Style::Titlebar | sf::Style::Close
            );
        window.setFramerateLimit( 60 );
        window.setKeyRepeatEnabled( false );
        window.setMouseCursorVisible( false );

        Ship ship( "resources/spaceship.png" );
        ship.setPosition(
            { GameGlobals::Instance().screenWidth / 2.f, 0.f }
            );
        ship.sprite().setOrigin( { 30.f, 23.f } );

        std::vector<std::unique_ptr<Asteroid>> asteroids;
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
                        GameGlobals::Instance().screenWidth - 100
                        )),                       // x
                    100.f + n * 15.f,             // y
                    rnd.getFloat( -2.5f, 2.5f )   // speed
                    )
                );
        }

        sf::RectangleShape ground(
            sf::Vector2f(
                static_cast<float>( GameGlobals::Instance().screenWidth ),
                10.f
                )
            );
        ground.setFillColor( sf::Color( 94, 68, 4 ) );
        ground.setPosition(
            sf::Vector2f(
                0.f,
                GameGlobals::Instance().screenHeight - 10.f
                )
            );

        sf::Font font;
        if ( !font.loadFromFile( "resources/zxspectrum.ttf" ) )
        {
            return EXIT_FAILURE;
        }
        sf::Text text( "Xtarda Rescue", font, 20 );
        text.setFillColor( sf::Color::Green );
        text.setPosition(
            sf::Vector2f(
                ( GameGlobals::Instance().screenWidth -
                  text.getGlobalBounds().width) / 2,
                10
                )
            );

        // Start game loop
        while ( window.isOpen() )
        {
            // Process events
            sf::Event event;
            while ( window.pollEvent( event ) )
            {
                if ( event.type == sf::Event::Closed )
                {
                    window.close();
                }

                if ( event.type == sf::Event::KeyPressed )
                {
                    if ( event.key.code == sf::Keyboard::Escape )
                    {
                        window.close();
                    }
                }
            }
            if ( !landed && !crashing )
            {
                // Specific state of keys at this moment:
                if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
                {
                    ship.adjustSpeed( -0.05f, 0 );
                }
                if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
                {
                    ship.adjustSpeed( 0.05f, 0 );
                }
                if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
                {
                    ship.adjustSpeed( 0, 0.05f );
                }
                if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
                {
                    ship.adjustSpeed( 0, -0.05f );
                }
            }
            if ( !landed )
            {
                ship.move();
            }

            auto v = ship.getPosition();
            if ( v.y >= GameGlobals::Instance().screenHeight -
                ship.sprite().getLocalBounds().height + 10
                )
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
                landed = true;
            }

            // Collision checking
            if ( !crashing && asteroidCollisionCheck( ship.sprite(), asteroids ) )
            {
                crashing = true; 
                ship.adjustAcceleration( 5.f );
                text.setString( "Crashed into asteroid" );
            }
            if( crashing && !landed )
            {
                ship.sprite().setRotation( ship.sprite().getRotation() + 2.f );
            }


            // Clear the screen (fill it with black color)
            window.clear();;
            ship.draw( window );
            utils::centre( text );
            window.draw( text );
            window.draw( ground ); //

            for ( auto& a : asteroids )
            {
                window.draw( a->sprite() );
                a->move();
            }

            // Display window contents on screen
            window.display();
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
