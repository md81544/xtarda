#include "gameLoop.h"

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

void GameLoop::registerKeyHandler(
    sf::Keyboard::Key key,
    std::function<void()> callback
    )
{
}
