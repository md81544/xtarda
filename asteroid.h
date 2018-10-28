#pragma once 

#include <SFML/Graphics.hpp>
#include <string>

class Asteroid
{
public:
    Asteroid( const std::string& filename, float x, float y, float speed );
    sf::Sprite&     sprite();
    sf::Vector2f    getPosition();
    void            setPosition( const sf::Vector2f& v );
    void            move();     // apply speed to position
private:
    sf::Texture     m_texture;
    sf::Sprite      m_sprite;
    float           m_speed; // not currently used; can be positive or negative 
};