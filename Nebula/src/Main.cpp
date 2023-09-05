// #include "PlanetLevel.h"
// #include "Core/Game Flow/Application.h"
//
// using namespace Gem;
//
// int main() {
// 	constexpr Application app{};
//
// 	app.Load(CreatePtr<Nebula::PlanetLevel>());
// }

#include <iostream>
#include "Entity Component System/EntityManager.h"

struct Pos {
	int x, y;
};

int main() {
	using namespace Gem;

	EntityManager ecs{};

	Entity entity = ecs.Create();

	size_t a = ComponentInfo<Pos>::id;

	auto b = ecs.m_Pools[a];

	std::cin.get();
}