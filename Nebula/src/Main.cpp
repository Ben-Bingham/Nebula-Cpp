#include "PlanetLevel.h"
#include "Core/Game Flow/Application.h"

using namespace Gem;

int main() {
	constexpr Application app{};

	app.Load(CreatePtr<Nebula::PlanetLevel>());
}