#pragma once
#include "Entity Component System/System.h"

namespace Nebula {
	class ChunkSystem : public Gem::System {
	public:
		ChunkSystem() = default;
		ChunkSystem(const ChunkSystem& other) = default;
		ChunkSystem(ChunkSystem&& other) noexcept = default;
		ChunkSystem& operator=(const ChunkSystem& other) = default;
		ChunkSystem& operator=(ChunkSystem&& other) noexcept = default;
		~ChunkSystem() override = default;

		void Step(Gem::EntityManager& entityManager, float dt) override;
	};
}