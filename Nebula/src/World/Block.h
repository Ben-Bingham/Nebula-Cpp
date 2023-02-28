#pragma once
#include <array>

#include "Geometry/Mesh.h"
#include "Rendering/ImageRegister.h"
#include "Pointer.h"

namespace Nebula {
	using BlockIndex = unsigned short; //TODO maybe replace with pointer to block
	constexpr unsigned int MAX_BLOCKS = std::numeric_limits<BlockIndex>::max();

	struct Block {
		Block(std::string iName, const std::initializer_list<ImageIndex> texIds)
			: internalName(std::move(iName)), textureIDs() {
			if (texIds.size() == 6) {
				std::ranges::copy(texIds.begin(), texIds.end(), textureIDs.begin());
			}
			else if (texIds.size() == 1) {
				for (int i = 0; i < 6; i++) {
					textureIDs[i] = *texIds.begin();
				}
			}
			else {
				for (int i = 0; i < 6; i++) {
					textureIDs[i] = 0;
				}
				LOG("Incorrect amount of textures given");
			}

			if (!cubeMesh) {
				cubeMesh = Celestite::CreatePtr<Ruby::MeshData>(Celestite::CreatePtr<Ruby::Cube>());
			}
		}

		std::string internalName;

		unsigned int id{ GetNextId() };
		std::array<ImageIndex, 6> textureIDs;

		inline static Celestite::Ptr<Ruby::MeshData> cubeMesh{ nullptr };

	private:
		inline static unsigned int m_NextId{ 0 };
		static unsigned int GetNextId() { return m_NextId++; }
	};
}