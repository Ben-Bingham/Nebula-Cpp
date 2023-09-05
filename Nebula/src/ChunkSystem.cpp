#include <tuple>

#include "ChunkSystem.h"
#include "Chunk.h"
#include "imgui.h"
#include "Player.h"

#include "Entity Component System/ComponentView.h"
#include "Math/Vector.h"

#include "Rendering/Components/Mesh.h"
#include "Rendering/Material/Material.h"
#include "Rendering/Material/Materials/DefaultMaterial.h"
#include "Rendering/Material/Materials/SimpleMaterial.h"

#include "Utility/Transform.h"

namespace Nebula {
	void ChunkSystem::Step(Gem::EntityManager& entityManager, float dt) {
		// Player setup
		int i = 0;
		for (auto [player, transform] : Gem::ComponentView<Player, Gem::Transform>{ entityManager }) { i++; }
		if (i != 1) { LOG("Invalid number of players", Gem::LogLevel::ERROR); return; }

		const auto player = *Gem::ComponentView<Player, Gem::Transform>{ entityManager }.begin();

		const std::vector<Gem::Vector2i> validChunks = CreateValidChunkPositionList(std::get<1>(player));

		DeleteUnnecessaryChunks(entityManager, validChunks);
		CreateMissingChunks(entityManager, validChunks);

		for (auto [chunk, transform] : Gem::ComponentView<Chunk, Gem::Transform>{ entityManager }) {
			// Submit chunks to rendering
			    // TODO
		}

		ImGui::Begin("Chunk Properties");
		ImGui::DragInt("Load Distance", &loadDistance, 1.0f, 0, 30);
		ImGui::End();
	}

	std::vector<Gem::Vector2i> ChunkSystem::CreateValidChunkPositionList(const Gem::Transform& playerTransform) const {
		const Gem::Vector2i playersChunkPosition{ (int)(std::floor(playerTransform.position.x) / (float)Chunk::xSize), (int)(std::floor(playerTransform.position.z) / (float)Chunk::zSize) };
		const Gem::Vector2i topRightCornerOfValidChunks{ playersChunkPosition.x + (int)loadDistance, playersChunkPosition.y + (int)loadDistance };
		const Gem::Vector2i bottomLeftCornerOfValidChunks{ playersChunkPosition.x - (int)loadDistance, playersChunkPosition.y - (int)loadDistance };

		std::vector<Gem::Vector2i> validChunks{};

		for (int x = bottomLeftCornerOfValidChunks.x; x <= topRightCornerOfValidChunks.x; x++) {
			for (int y = bottomLeftCornerOfValidChunks.y; y <= topRightCornerOfValidChunks.y; y++) {
				validChunks.emplace_back(Gem::Vector2i{ x, y });
			}
		}

		return validChunks;
	}

	void ChunkSystem::DeleteUnnecessaryChunks(Gem::EntityManager& entityManager, const std::vector<Gem::Vector2i>& validChunks) {
		auto it = m_Chunks.begin();
		while (it != m_Chunks.end()) {
			const auto transform = entityManager.GetComponent<Gem::Transform>(*it);
			const auto simplifiedPos = Gem::Vector2i{ (int)std::floor(transform.position.x), (int)std::floor(transform.position.y) };
			bool allowedToExist = false;

			for (const auto& validChunk : validChunks) {
				if (validChunk == simplifiedPos) {
					allowedToExist = true;
					break;
				}
			}

			if (!allowedToExist) {
				DeleteChunk(entityManager, *it);

				it = m_Chunks.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void ChunkSystem::CreateMissingChunks(Gem::EntityManager& entityManager, const std::vector<Gem::Vector2i>& validChunks) {
		std::vector<Gem::Vector2i> neededChunks = validChunks;

		auto it = neededChunks.begin();
		while (it != neededChunks.end()) {
			bool alreadyHaveChunk = false;
			for (const auto& chunk : m_Chunks) {
				const auto transform = entityManager.GetComponent<Gem::Transform>(chunk);
				const auto simplifiedPos = Gem::Vector2i{ (int)std::floor(transform.position.x), (int)std::floor(transform.position.z) };

				if (*it == simplifiedPos) {
					alreadyHaveChunk = true;
					break;
				}
			}

			if (alreadyHaveChunk) {
				it = neededChunks.erase(it);
			}
			else {
				++it;
			}
		}

		for (const auto& neededChunk : neededChunks) {
			m_Chunks.push_back(CreateChunk(entityManager, neededChunk));
		}
	}

	Gem::Entity ChunkSystem::CreateChunk(Gem::EntityManager& entityManager, const Gem::Vector2i& position) {
		static auto mat = Gem::CreatePtr<Gem::DefaultMaterial>(Gem::Image{"assets\\images\\container.png"}, Gem::Image{"assets\\images\\container_specular.png"});
		// static auto mat = Gem::CreatePtr<Gem::SimpleMaterial>(Gem::Colour::BLUE);

		Gem::Entity chunk = entityManager.Create();
		entityManager.Insert<Chunk>(chunk);
		entityManager.Insert<Gem::Transform>(chunk, Gem::Vector3f{ (float)position.x, 0.0f, (float)position.y });
		entityManager.Insert<Gem::Material>(chunk, mat);
		entityManager.Insert<Gem::Mesh>(chunk, Gem::Cube{});

		return chunk;
	}

	void ChunkSystem::DeleteChunk(Gem::EntityManager& entityManager, Gem::Entity chunk) {
		entityManager.Extract<Gem::Mesh>(chunk);
		entityManager.Extract<Gem::Material>(chunk);
		entityManager.Extract<Gem::Transform>(chunk);
		entityManager.Extract<Chunk>(chunk);
		entityManager.Kill(chunk);
	}
}