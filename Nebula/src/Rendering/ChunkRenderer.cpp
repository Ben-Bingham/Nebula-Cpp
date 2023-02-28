#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <ranges>

#include "ChunkRenderer.h"

#include "Camera.h"
#include "ChunkMaterial.h"

#include "Utility/Transform.h"

#include "World/BlockRegister.h"
#include "World/Chunk.h"
#include "Window.h"

#include "Materials/Material.h"
#include "OpenGLState.h"

namespace Nebula::ChunkRenderer {
	void Render(Esperite::Scene* scene, Ruby::Camera* camera) {
		const Ruby::OpenGlState::Face face = Ruby::OpenGlState::get().getFaceToCull();
		Ruby::OpenGlState::get().setFaceToCull(Ruby::OpenGlState::Face::BACK);

		for (const auto& gb : scene->gameObjects) {
			if (scene->HasComponent<Chunk>(gb) &&
				scene->HasComponent<Ruby::Material>(gb)
				) {

				auto& chunk = *scene->GetComponent<Chunk>(gb);
				auto* material = scene->GetComponent<Ruby::Material>(gb);

				using BlockPosition = Malachite::Vector3f;
				using BlockBucket = std::pair<BlockIndex, std::vector<BlockPosition>>;

				std::vector<BlockBucket> buckets;

				for (size_t x{ 0 }; x < Chunk::xSize; x++) {
					for (size_t y{ 0 }; y < Chunk::ySize; y++) {
						for (size_t z{ 0 }; z < Chunk::zSize; z++) {
							bool added{ false };
							for (auto& [index, positions] : buckets) {
								if (chunk[x][y][z] == index) {
									positions.emplace_back(Malachite::Vector3f{ (float)x, (float)y, (float)z });
									added = true;
								}
							}

							if (!added) {
								buckets.emplace_back(BlockBucket{ chunk[x][y][z], { Malachite::Vector3f{ (float)x, (float)y, (float)z } } });
							}
						}
					}
				}

				constexpr size_t NUMBER_OF_BLOCKS = (size_t)Chunk::xSize * (size_t)Chunk::ySize * (size_t)Chunk::zSize;
				constexpr size_t SIDES_PER_BLOCK = 6;

				std::vector<ImageIndex> data;
				data.resize(NUMBER_OF_BLOCKS * SIDES_PER_BLOCK);

				int i{ 0 };
				for (const auto& index : std::views::keys(buckets)) {
					for (int j = 0; j < SIDES_PER_BLOCK; j++) {
						data[i] = BlockRegister::Get()[index].textureIDs[j];
					}

					i++;
				}

				Block::cubeMesh->bind();

				material->material->use(Malachite::Matrix4f{1.0f}, camera->viewMatrix, Wavellite::Window::Get().getProjectionMatrix());

				glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)Block::cubeMesh->getIndexCount(), GL_UNSIGNED_INT, nullptr, NUMBER_OF_BLOCKS);
				material->material->end();
			}
		}

		Ruby::OpenGlState::get().setFaceToCull(face);
	}
}