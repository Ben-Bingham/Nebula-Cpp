#pragma once

#include <vector>

#include "Block.h"

namespace Nebula {
	class BlockRegister { //TODO maybe this should extend from some kind of register class in case more of these are needed, like for items
	public:
		static BlockRegister& Get();
	
		[[nodiscard]] BlockIndex Register(const Block& block);
	
		[[nodiscard]] Block operator[](size_t index);

		BlockRegister(const BlockRegister& other) = delete;
		BlockRegister(BlockRegister&& other) noexcept = delete;
		BlockRegister& operator=(const BlockRegister& other) = delete;
		BlockRegister& operator=(BlockRegister&& other) noexcept = delete;
		~BlockRegister() = default;

	private:
		BlockRegister() = default;
	
		std::vector<Block> m_Blocks;
	};
}
