#include "Chunk.h"
#include "BlockManager.h"

namespace Nebula {
	void Chunk::generateBlocks(BlockManager* blockManager) { // Generates what blocks are actually in the chunk
		Block* airBlock = blockManager->getBlock("BLOCK_AIR");
		Block* dirtBlock = blockManager->getBlock("BLOCK_DIRT");
		Block* unknownBlock = blockManager->getBlock("BLOCK_UNKNOWN");

		for (size_t x = 0; x < xSize; x++) {
			for (size_t y = 0; y < ySize; y++) {
				for (size_t z = 0; z < zSize; z++) {
					if (y < 80) {
						blocks[x][y][z] = dirtBlock;
					}
					else if (y == 80) {
						blocks[x][y][z] = unknownBlock;
					}
					else {
						blocks[x][y][z] = airBlock;
					}
				}
			}
		}
	}

	void Chunk::createTextureBuffer(const Chunk& posXChunk, const Chunk& negXChunk, const Chunk& posYChunk, const Chunk& negYChunk, BlockManager* blockManager) { // Generates "Geometry"
		std::vector<float> content{ };
		unsigned int blocksToRend{ 0 };

		Block* airBlock = blockManager->getBlock("BLOCK_AIR");

		for (unsigned int x = 0; x < xSize; x++) {
			for (unsigned int y = 0; y < ySize; y++) {
				for (unsigned int z = 0; z < zSize; z++) {
					Block* block = blocks[x][y][z];
					Block* posXBlock{ airBlock };
					Block* negXBlock{ airBlock };
					Block* posYBlock{ airBlock };
					Block* negYBlock{ airBlock };
					Block* posZBlock{ airBlock };
					Block* negZBlock{ airBlock };

					if (block != airBlock) {
						// X
						if (x <= 14) {
							posXBlock = blocks[x + 1][y][z];
						}
						else {
							posXBlock = posXChunk.blocks[0][y][z];
						}

						if (x >= 1) {
							negXBlock = blocks[x - 1][y][z];
						}
						else {
							negXBlock = negXChunk.blocks[15][y][z];
						}

						// Y
						if (y <= 254) {
							posYBlock = blocks[x][y + 1][z];
						}
						if (y >= 1) {
							negYBlock = blocks[x][y - 1][z];
						}

						// Z
						if (z <= 14) {
							posZBlock = blocks[x][y][z + 1];
						}
						else {
							posZBlock = posYChunk.blocks[x][y][15];
						}

						if (z >= 1) {
							negZBlock = blocks[x][y][z - 1];
						}
						else {
							negZBlock = negYChunk.blocks[x][y][0];
						}

						if (posXBlock == airBlock || negXBlock == airBlock || posYBlock == airBlock || negYBlock == airBlock || posZBlock == airBlock || negZBlock == airBlock) {
							content.push_back(static_cast<float>(x));
							content.push_back(static_cast<float>(y));
							content.push_back(static_cast<float>(z));
							content.push_back(static_cast<float>(block->textureIDs[0]));
							//TODO add additional texture info
							blocksToRend++;
						}
					}
				}
			}
		}

		blocksToRender = blocksToRend;

		// "Geometry"
		Ruby::VertexAttributeObject::unbind();

		textureBufferVBO.bind();
		textureBufferVBO.setData(content);
		textureBufferVBO.unbind();

		offsetBufferTexture.bind();
		offsetBufferTexture.setData(textureBufferVBO, GL_RGBA32F);
	}

	const unsigned int Chunk::xSize{ 16 };
	const unsigned int Chunk::ySize{ 256 };
	const unsigned int Chunk::zSize{ 16 };
}