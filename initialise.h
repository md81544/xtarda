#pragma once

#include <memory>
#include <vector>

class ISprite;
class GameLoop;
namespace sf{ class RectangleShape; }

// General initialisation code
namespace init
{

void createAsteroids(
    GameLoop& gameLoop,
    std::vector<std::unique_ptr<ISprite>>& vec
    );

std::unique_ptr<sf::RectangleShape> createGround(
    GameLoop& GameLoop
    );

} // namespace init
