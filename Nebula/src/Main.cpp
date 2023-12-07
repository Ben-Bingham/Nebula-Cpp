#include "Core/Engine_New.h"
#include "Core/Game.h"
#include "Utility/Log.h"

using namespace Gem;

 int main() {
 	Engine_New engine{};

    Game game{ engine };

    //game.Run(CreatePtr<Level_New>(), [&](Ptr<Level_New> level)->bool { return engine.glfwContext.time.GetElapsedTime() < 3.0f; });
    //game.Run(CreatePtr<Level_New>(), [&](Ptr<Level_New> level)->bool { return engine.glfwContext.time.GetElapsedTime() < 6.0f; });

    EntityComponentSystem_New ecs{};

    Entity_New ent = ecs.entityManager.Create();
    Entity_New ent1 = ecs.entityManager.Create();
    Entity_New ent2 = ecs.entityManager.Create();
    Entity_New ent3 = ecs.entityManager.Create();
    Entity_New ent4 = ecs.entityManager.Create();

    int a = 1;
 }
