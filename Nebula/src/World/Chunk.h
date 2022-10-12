#pragma once
#include <vector>

#include "Vector.h"
#include "Rendering/ChunkRenderable.h"
#include "BlockManager.h"
#include "Block.h"

namespace Nebula {
	class Chunk {
	public:
		Chunk(Malachite::Vector2i absPos, ChunkRenderable& renderable)
			: absolutePosition(absPos), renderable(&renderable) {

			blocks.resize(16);

			for (std::vector<std::vector<Nebula::Block*>>& vec : blocks) {
				vec.resize(256);
				for (std::vector<Nebula::Block*>& vec2 : vec) {
					vec2.resize(16);
				}
			}
		}

		void generateBlocks(BlockManager* blockManager);
		
		void createTextureBuffer(const Chunk& posX, const Chunk& negX, const Chunk& posY, const Chunk& negY, BlockManager* blockManager);

		void render() {
			renderable->model = Malachite::Matrix4f{ 1.0f };
			renderable->model.translate(absolutePosition.x * 16.0f, 0.0f, absolutePosition.y * 16.0f);
			Ruby::ShaderProgram::upload("offsetBuffer", 5, offsetBufferTexture);
			renderable->setNumberToRender(blocksToRender);

			renderable->render();
		}

		void breakBlock() {
			// TODO
		}

		Malachite::Vector2i absolutePosition;

		const static unsigned int xSize;
		const static unsigned int ySize;
		const static unsigned int zSize;

		std::vector<std::vector<std::vector<Nebula::Block*>>> blocks;

	private:
		Nebula::ChunkRenderable* renderable;

		unsigned int blocksToRender{ 0 };

		Ruby::VertexBufferObject textureBufferVBO{ };
		Ruby::BufferTexture offsetBufferTexture{ };
	};
}