#pragma once

#include <vector>
#include <array>
#include <string>

#include "Log.h"
#include "Block.h"

namespace Nebula {
	class BlockManager {
	public:
		static void addBlock(Block& block) {
			blocks.push_back(std::move(block));
		}

		static Block* getBlock(const std::string& name) {
			for (Block& block : blocks) {
				if (block.internalName == name) {
					return &block;
				}
			}
			LOG("Block not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

		static Block* getBlock(unsigned int ID) {
			for (Block& block : blocks) {
				if (block.ID == ID) {
					return &block;
				}
			}
			LOG("Block not found in list.", Lazuli::LogLevel::ERROR);
			return nullptr;
		}

	private:
		static std::vector<Block> blocks;
	};
}