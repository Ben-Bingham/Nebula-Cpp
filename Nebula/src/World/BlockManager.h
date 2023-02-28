#pragma once

#include <vector>
#include <array>
#include <string>

#include "Log.h"
#include "Block.h"
#include "Rendering/ImageRegister.h"

namespace Nebula {
	class BlockManager {
	public:
		BlockManager() = default;

		void addBlock(const Block& block) {
			m_Blocks.push_back(block);
		}

		Block* getBlock(const std::string& name) {
			for (Block& block : m_Blocks) {
				if (block.internalName == name) {
					return &block;
				}
			}
			LOG("Block not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

		Block* getBlock(unsigned int ID) {
			for (Block& block : m_Blocks) {
				if (block.id == ID) {
					return &block;
				}
			}
			LOG("Block not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

		ImageRegister diffuseImageManager;

	private:
		std::vector<Block> m_Blocks;
	};
}