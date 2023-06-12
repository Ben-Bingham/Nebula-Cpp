#pragma once
#include <array>

namespace Nebula {
	struct Chunk {
		static inline constexpr int xSize{ 16 };
		static inline constexpr int ySize{ 256 };
		static inline constexpr int zSize{ 16 };

		using BlockId = unsigned int;
		std::array<std::array<std::array<BlockId, zSize>, ySize>, xSize> blocks;
	};
}