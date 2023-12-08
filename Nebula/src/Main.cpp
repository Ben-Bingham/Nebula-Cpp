#include "Core/Engine_New.h"
#include "Core/Game.h"
#include "Utility/Log.h"
#include "Entity Component System/View.h"

using namespace Gem;

 int main() {
 	Engine_New engine{};

    Game game{ engine };

    //game.Run(CreatePtr<Level_New>(), [&](Ptr<Level_New> level)->bool { return engine.glfwContext.time.GetElapsedTime() < 3.0f; });
    //game.Run(CreatePtr<Level_New>(), [&](Ptr<Level_New> level)->bool { return engine.glfwContext.time.GetElapsedTime() < 6.0f; });

    EntityComponentSystem ecs{};

    int sdkfjhsdf = 1;
 }
