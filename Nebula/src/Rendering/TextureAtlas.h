#pragma once

#include "OpenGL objects/Texture.h"
#include "Arrays/IndexCordinateConversion.h"

namespace Nebula {
	class TextureAtlas : public Ruby::Texture {
	public:
		TextureAtlas(std::vector<Ruby::Image*> images) 
			: imagesPerSide((unsigned int)ceil(sqrt(images.size()))), Texture(createEmptyTexture(images)) {

			unsigned int size = images[0]->getWidth();
			unsigned int imagesPerSide = (unsigned int)ceil(sqrt(images.size()));

			for (unsigned int x = 0; x < imagesPerSide; x++) {
				for (unsigned int y = 0; y < imagesPerSide; y++) {
					unsigned int index = Malachite::twoDToIndex(Malachite::Vector2i{ (int)y, (int)x }, (int)imagesPerSide);
					if (index >= images.size()) {
						break;
					}

					this->setSubData(x * size, y * size, *images[index]);
				}
			}

			Ruby::VertexAttributeObject::unbind();

			std::vector<float> content{};

			float imageWorth = 1.0f / images.size();

			unsigned int i{ 0 };
			for (Ruby::Image* image : images) {
				content.push_back(0.0f);
				content.push_back(0.0f + imageWorth * i);

				content.push_back(0.0f);
				content.push_back(0.0f + (imageWorth * i) + imageWorth);

				content.push_back(1.0f);
				content.push_back(0.0f + (imageWorth * i) + imageWorth);

				content.push_back(1.0f);
				content.push_back(0.0f + imageWorth * i);

				i++;
			}

			/*textureCordVBO.bind();
			textureCordVBO.setData(content);
			textureCordVBO.unbind();

			textureCordBufferTexture.bind();
			textureCordBufferTexture.setData(textureCordVBO, GL_RGB32F);*/
		}

		//Ruby::BufferTexture textureCordBufferTexture{ };
		unsigned int imagesPerSide;

	private:
		//Ruby::VertexBufferObject textureCordVBO{ };

		Ruby::Texture createEmptyTexture(std::vector<Ruby::Image*> images) {
			unsigned int size = images[0]->getWidth();
			unsigned int imagesPerSide = (unsigned int)ceil(sqrt(images.size()));

			return Texture{ GL_RGBA, imagesPerSide * size, imagesPerSide * size, GL_CLAMP_TO_BORDER, GL_NEAREST, true };
		}
	};
}