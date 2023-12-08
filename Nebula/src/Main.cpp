#include "Core/Engine_New.h"
#include "Core/Game.h"
#include "Utility/Log.h"
#include "Entity Component System/View.h"

using namespace Gem;

struct TestComponent1 {
    int val{ 0 };
};

struct TestComponent2 {
    int val{ 0 };
};

 int main() {
 	Engine_New engine{};

    Game game{ engine };

    //game.Run(CreatePtr<Level_New>(), [&](Ptr<Level_New> level)->bool { return engine.glfwContext.time.GetElapsedTime() < 3.0f; });
    //game.Run(CreatePtr<Level_New>(), [&](Ptr<Level_New> level)->bool { return engine.glfwContext.time.GetElapsedTime() < 6.0f; });

    EntityComponentSystem ecs{};

    Entity ent1 = ecs.entityManager.Create();
    Entity ent2 = ecs.entityManager.Create();
    Entity ent3 = ecs.entityManager.Create();
    Entity ent4 = ecs.entityManager.Create();

    ecs.componentManager.AddComponent<TestComponent1>(ent1, 1);
    ecs.componentManager.AddComponent<TestComponent1>(ent2, 2);
    ecs.componentManager.AddComponent<TestComponent1>(ent3, 3);
    ecs.componentManager.AddComponent<TestComponent1>(ent4, 4);

    ecs.componentManager.AddComponent<TestComponent2>(ent3, 5);
    ecs.componentManager.AddComponent<TestComponent2>(ent4, 6);

    for (auto ent : View<>(ecs)) {
        LOG("Entity: " + std::to_string(ent));
    }
    
    /*for (auto [ent, testComp1, testComp2] : View<TestComponent1, TestComponent2>(ecs)) {
        LOG("Entity: " + std::to_string(ent) + ", Value 1: " + std::to_string(testComp1.val) + ", Value 2: " + std::to_string(testComp2.val));
    }*/

    /*for (auto [ent, testComp1] : View<TestComponent1>(ecs)) {
        LOG("Entity: " + std::to_string(ent) + ", Value: " + std::to_string(testComp1.val));
    }*/

    int sdkfjhsdf = 1;
 }
