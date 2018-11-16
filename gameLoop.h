#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

class ISprite;

// This class acts as a "controller" for the game and deals with
// initialisation, main loop, redrawing, etc. Leaving other code
// to act as the "model" and dealing with state.
// Actions for keypresses are registered as callbacks.
class GameLoop
{
public:
    GameLoop( int windowWidth, int windowHeight );
    bool isWindowOpen();
    void registerKeyHandler(
        sf::Keyboard::Key key,
        std::function<void()> callback
        );
    void processEvents();
    void clear();
    void draw( ISprite* const sprite );
    void draw( const sf::Drawable& d );
    void display();
    void exit();
private:
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unordered_map< sf::Keyboard::Key, std::function<void()> > m_keyMap;
};
