#pragma once 

#include "isprite.h"
#include <SFML/Graphics.hpp>
#include <string>

class Asteroid : public ISprite
{
public:
    Asteroid(
        const std::string& filename,
        float x,
        float y,
        float speed,
        float rotation,
        float scale
        );
    void move() override;
private:
    float m_rotation{ 0.f };
};