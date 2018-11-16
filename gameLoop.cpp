#include "gameLoop.h"
#include "isprite.h"

GameLoop::GameLoop( int windowWidth, int windowHeight )
{
    m_window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(
            windowWidth, 
            windowHeight,
            32
            ),
        "Xtarda Rescue",
        sf::Style::Titlebar | sf::Style::Close
        );
    m_window->setFramerateLimit( 60 );
    m_window->setKeyRepeatEnabled( false );
    m_window->setMouseCursorVisible( false );
}

bool GameLoop::isWindowOpen()
{
    return m_window->isOpen();
}

void GameLoop::registerKeyHandler(
    sf::Keyboard::Key key,
    std::function<void()> callback
    )
{
    m_keyMap[ key ] = callback;
}

void GameLoop::registerDrawable( sf::Drawable * d )
{
    m_drawables.push_back( d );
}

void GameLoop::processEvents()
{
    sf::Event event;
    while ( m_window->pollEvent( event ) )
    {
        // TODO currently EVENT handling (as opposed to key-
        // press handling) is hard-coded here.
        if ( event.type == sf::Event::Closed )
        {
            m_window->close();
        }

        if ( event.type == sf::Event::KeyPressed )
        {
            if ( event.key.code == sf::Keyboard::Escape )
            {
                m_window->close();
            }
        }
    }
    // Now cycle through registered key presses and
    // make callbacks
    for( const auto& pr : m_keyMap )
    {
        if ( sf::Keyboard::isKeyPressed( pr.first ) )
        {
            pr.second();
        }
    }
}

void GameLoop::updateDisplay()
{
    m_window->clear();
    for ( auto p : m_drawables )
    {
        m_window->draw( *p );
    }
    m_window->display();
}

void GameLoop::exit()
{
    m_window->close();
}
