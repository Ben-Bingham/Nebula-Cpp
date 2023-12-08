#pragma once
#include <vector>

//#include "Entity Component System/Entity.h"
//#include "Entity Component System/System.h"

#include "Math/Vector.h"

#include "Utility/Transform.h"

namespace Nebula {
	//class ChunkSystem : public Gem::System {
	//public:
	//	ChunkSystem() = default;
	//	ChunkSystem(const ChunkSystem& other) = default;
	//	ChunkSystem(ChunkSystem&& other) noexcept = default;
	//	ChunkSystem& operator=(const ChunkSystem& other) = default;
	//	ChunkSystem& operator=(ChunkSystem&& other) noexcept = default;
	//	~ChunkSystem() override = default;

	//	void Step(Gem::EntityManager& entityManager, float dt) override;

	//	int loadDistance{ 3 };

	//private:
	//	std::vector<Gem::Entity> m_Chunks;

	//	[[nodiscard]] std::vector<Gem::Vector2i> CreateValidChunkPositionList(const Gem::Transform& playerTransform) const;
	//	void DeleteUnnecessaryChunks(Gem::EntityManager& entityManager, const std::vector<Gem::Vector2i>& validChunks);
	//	void CreateMissingChunks(Gem::EntityManager& entityManager, const std::vector<Gem::Vector2i>& validChunks);

	//	[[nodiscard]] static Gem::Entity CreateChunk(Gem::EntityManager& entityManager, const Gem::Vector2i& position);
	//	static void DeleteChunk(Gem::EntityManager& entityManager, Gem::Entity chunk);
	//};
}