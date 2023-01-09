#pragma once

namespace Nebula {
	struct Block {
		Block(std::string iName, const std::array<unsigned short, 6> texIds = { 0, 0, 0, 0, 0, 0 })
			: internalName(std::move(iName)), textureIDs(texIds) {
		}

		std::string internalName;

		unsigned int id{ getNextId() };
		std::array<unsigned short, 6> textureIDs;

	private:
		inline static unsigned int m_NextId{ 0 };
		static unsigned int getNextId() { return m_NextId++; }
	};
}