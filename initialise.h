#pragma once

#include <memory>
#include <vector>

class ISprite;
class GameLoop;
// General initialisation code

namespace init
{

void createAsteroids(
    GameLoop& gameLoop,
    std::vector<std::unique_ptr<ISprite>>& vec
);

} // namespace init