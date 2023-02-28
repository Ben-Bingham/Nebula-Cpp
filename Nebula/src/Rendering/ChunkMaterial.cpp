#include "ChunkMaterial.h"

#include "Shaders/ShaderLibrary.h"

namespace Nebula {
	ChunkMaterial::ChunkMaterial(const Celestite::Ptr<Ruby::Image>& textureAtlas)
		: MaterialData(Ruby::ShaderLibrary::Get()[Ruby::ShaderLibrary::Get().LoadShader("assets\\shaders\\ChunkShader.vert", "assets\\shaders\\ChunkShader.frag")])
		, m_TextureAtlas(Celestite::CreatePtr<Ruby::Texture>(textureAtlas)) {

		if (!m_InitializedPositions) {
			using BlockCordType = std::remove_const_t<decltype(Chunk::xSize)>;
			std::vector<Malachite::Vector4<BlockCordType>> positionVector;

			for (BlockCordType x{ 0 }; x < Chunk::xSize; x++) {
				for (BlockCordType y{ 0 }; y < Chunk::ySize; y++) {
					for (BlockCordType z{ 0 }; z < Chunk::zSize; z++) {
						positionVector.emplace_back(Malachite::Vector4<BlockCordType>{ x, y, z, 0 });
					}
				}
			}

			m_BlockPositionBuffer = Celestite::CreatePtr<CharBuffer>();
			m_BlockPositionBuffer->setData(positionVector);

			m_BlockPositions = Celestite::CreatePtr<CharBufferTexture>();
			m_BlockPositions->Bind();
			m_BlockPositions->AssignBuffer(m_BlockPositionBuffer);

			m_InitializedPositions = true;
		}
	}

	void ChunkMaterial::use(const Malachite::Matrix4f& model, const Malachite::Matrix4f& view, const Malachite::Matrix4f& projection) {
#ifdef NEBULA_DEBUG
		if (!m_TextureAtlas) {
			LOG("Chunk material not initialized.", Lazuli::LogLevel::ERROR);
		}
#endif

		m_Program->use();
		m_Uniforms.upload();

		const Malachite::Matrix4f modelViewProjection = model * view * projection;

		Ruby::ShaderProgram::upload("modelViewProjection", modelViewProjection);
		Ruby::ShaderProgram::upload("model", model);
	}

	void ChunkMaterial::end() {
		MaterialData::end();
	}
}