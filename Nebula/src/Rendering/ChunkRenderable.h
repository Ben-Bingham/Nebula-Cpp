#pragma once

#include "PhongInstanceRenderable.h"

namespace Nebula {
	class ChunkRenderable : public PhongInstanceRenderable {
	public:
		ChunkRenderable(Ruby::PhongMaterial& mat)
			: PhongInstanceRenderable(verticies, indices, mat, 0) {

		}

		void render() const override {
			VAO.bind();
			Ruby::ShaderProgram::upload("model", model);
			glDrawElementsInstanced(GL_TRIANGLES, numberOfIndicies, GL_UNSIGNED_INT, 0, numberToRender);
		}

	private:
		static const std::vector<float> verticies;
		static const std::vector<unsigned int> indices;
	};
}
