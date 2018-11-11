#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class ISprite
{
public:
    ISprite( const std::string& filename );
    virtual ~ISprite(){};
    virtual void draw( sf::RenderWindow& window );
    virtual float getVerticalSpeed();
    virtual float getHorizontalSpeed();
    virtual void  setVerticalSpeed( float s);
    virtual void  setHorizontalSpeed( float s);
    virtual void  setPosition( sf::Vector2f pos );
    virtual sf::Vector2f getPosition();
    virtual void move() = 0;
protected:
    std::unique_ptr<sf::Sprite> m_sprite;
    float m_verticalSpeed;
    float m_horizontalSpeed;
    sf::Texture m_texture;
};
