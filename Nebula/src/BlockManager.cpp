#include "BlockManager.h"

namespace Nebula {
	unsigned int Block::nextID{ 0 };
	std::vector<Block> BlockManager::blocks{};
}