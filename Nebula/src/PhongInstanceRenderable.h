#pragma once

#include "Renderable Objects/Phong/PhongRenderable.h"

namespace Nebula {
	class PhongInstanceRenderable : public Ruby::PhongRenderable {
	public:
		PhongInstanceRenderable(const std::vector<float>& verticies, const std::vector<unsigned int>& indicies, Ruby::PhongMaterial& mat) 
			: PhongRenderable(verticies, indicies, mat) {

		}

		// The assumption is made that a shader program is bound prior to this being called
		void render() const override {
			VAO.bind();
			Ruby::ShaderProgram::upload("model", model);
			Ruby::ShaderProgram::upload("material", 0, *material);
			glDrawElementsInstanced(GL_TRIANGLES, numberOfIndicies, GL_UNSIGNED_INT, 0, (16 * 256 * 16));
		}
	};
}