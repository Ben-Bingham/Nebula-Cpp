#pragma once
#include "Core/Game Flow/Level.h"

namespace Nebula {
	class PlanetLevel : public Gem::Level {
	public:
		PlanetLevel() = default;
		PlanetLevel(const PlanetLevel& other) = default;
		PlanetLevel(PlanetLevel&& other) noexcept = default;
		PlanetLevel& operator=(const PlanetLevel& other) = delete;
		PlanetLevel& operator=(PlanetLevel&& other) noexcept = delete;
		~PlanetLevel() override = default;

		void Load() override;
		void Unload() override;
	};
}