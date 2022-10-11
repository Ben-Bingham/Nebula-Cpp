#pragma once

#include <vector>
#include <array>
#include <string>

#include "Log.h"
#include "Block.h"
#include "Rendering/ImageManager.h"

namespace Nebula {
	class BlockManager {
	public:
		BlockManager() { }

		void addBlock(Block& block) {
			blocks.push_back(std::move(block));
		}

		Block* getBlock(const std::string& name) {
			for (Block& block : blocks) {
				if (block.internalName == name) {
					return &block;
				}
			}
			LOG("Block not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

		Block* getBlock(unsigned int ID) {
			for (Block& block : blocks) {
				if (block.ID == ID) {
					return &block;
				}
			}
			LOG("Block not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

		ImageManager imageManager;

	private:
		std::vector<Block> blocks;
	};
}