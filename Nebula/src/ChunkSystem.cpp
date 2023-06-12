#include <vector>
#include <tuple>

#include "ChunkSystem.h"
#include "Chunk.h"
#include "Entity Component System/ComponentView.h"
#include "Math/Vector.h"
#include "Utility/Transform.h"

namespace Nebula {
	void ChunkSystem::Step(Gem::EntityManager& entityManager, float dt) {
		using PlayerPair = std::pair<Player*, Gem::Transform*>;
		using ChunkPair = std::pair<Chunk*, Gem::Transform*>;

		std::vector<PlayerPair> players;
		for (auto [player, transform] : Gem::ComponentView<Player, Gem::Transform>{ entityManager }) {
			players.push_back(std::make_pair<Player*, Gem::Transform*>{ &player, &transform });
		}

#ifdef NEBULA_DEBUG
		if (players.size() != 1) {
			LOG("Invalid number of players.", Gem::LogLevel::ERROR);
			return;
		}
#endif

		PlayerPair& player = players[0];

		std::vector<Gem::Vector3f> allowedChunks = GetAllowedChunks(player);

		std::vector<ChunkPair> existingChunks{};
		for (auto [chunk, transform] : Gem::ComponentView<Chunk, Gem::Transform>{ entityManager }) {
			existingChunks.push_back(std::make_pair<Chunk*, Gem::Transform*>(&chunk, &transform));
		}

		for (auto existingChunk : existingChunks) {
			bool allowed = false;
			for (auto allowedChunk : allowedChunks) {
				if (existingChunk.second->position == allowedChunk) {
					allowed = true;
					break;
				}
			}

			if (!allowed) {
				entityManager.Extract<Chunk>()// TODO stuck, how can we get a refrence to the gameobject and delete it. LAST HERE
			}
		}

		// Create any necessary missing chunks
			// TODO

		for (auto [chunk, transform] : Gem::ComponentView<Chunk, Gem::Transform>{ entityManager }) {
			// Submit chunks to rendering
				// TODO
		}
	}
}