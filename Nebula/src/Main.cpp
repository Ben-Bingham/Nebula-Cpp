#include "Core/Engine_New.h"
#include "Core/Game.h"

 using namespace Gem;

 int main() {
 	Engine_New engine{};

    Game game{ engine };

    game.levelManager.AddLevel(CreatePtr<Level_New>());

    game.Run();
 }