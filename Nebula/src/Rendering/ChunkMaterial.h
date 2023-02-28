#pragma once

#include "Materials/MaterialData.h"

#include "Shaders/Uniforms/UniformSet.h"

#include "World/Chunk.h"
#include "OpenGL objects/GlBuffer.h"
#include "OpenGL objects/BufferTexture.h"

namespace Nebula {
	using ChunkSizeType = std::remove_const_t<decltype(Chunk::xSize)>; //TODO improve names
	using CharBuffer = Ruby::BlankBuffer<Malachite::Vector4<ChunkSizeType>>;
	using CharBufferTexture = Ruby::BufferTexture<Malachite::Vector4<ChunkSizeType>>;

	class ChunkMaterial : public Ruby::MaterialData {
	public:
		ChunkMaterial(const Celestite::Ptr<Ruby::Image>& textureAtlas);

		void use(const Malachite::Matrix4f& model, const Malachite::Matrix4f& view, const Malachite::Matrix4f& projection) override;
		void end() override;

	private:
		Celestite::Ptr<Ruby::Texture> m_TextureAtlas;
		inline static Celestite::Ptr<CharBuffer> m_BlockPositionBuffer{};
		inline static bool m_InitializedPositions{ false };

		inline static Celestite::Ptr<CharBufferTexture> m_BlockPositions{};

		Ruby::UniformSet<
			Celestite::Ptr<CharBufferTexture>
		> m_Uniforms {
			Ruby::Uniform{"blockPositions", m_BlockPositions}
		};
	};
}