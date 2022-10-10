#pragma once

namespace Nebula {
	struct Block {
		Block(std::string iName, std::array<unsigned int, 6> texIds = { 0, 0, 0, 0, 0, 0 })
			: internalName(iName), textureIDs(texIds) {
		}

		unsigned int ID{ getNextID() };
		std::array<unsigned int, 6> textureIDs;

		std::string internalName;
	private:
		static unsigned int nextID;
		unsigned int getNextID() { return nextID++; }
	};
}