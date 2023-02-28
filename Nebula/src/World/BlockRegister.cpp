#include "BlockRegister.h"

namespace Nebula {
	BlockRegister& BlockRegister::Get() {
		static BlockRegister blockRegister;
	
		return blockRegister;
	}
	
	BlockIndex BlockRegister::Register(const Block& block) {
		m_Blocks.push_back(block);
	
		return m_Blocks.size() - 1;
	}
	
	Block BlockRegister::operator[](const size_t index) {
		return m_Blocks[index];
	}
}