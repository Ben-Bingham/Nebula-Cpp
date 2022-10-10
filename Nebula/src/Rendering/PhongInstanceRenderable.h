#pragma once

#include "Renderable Objects/Phong/PhongRenderable.h"

namespace Nebula {
	class PhongInstanceRenderable : public Ruby::PhongRenderable {
	public:
		PhongInstanceRenderable(const std::vector<float>& verticies, const std::vector<unsigned int>& indicies, Ruby::PhongMaterial& mat, unsigned int num) 
			: PhongRenderable(verticies, indicies, mat), numberToRender(num) {

		}

		void render() const override {
			VAO.bind();
			Ruby::ShaderProgram::upload("model", model);
			Ruby::ShaderProgram::upload("material", 0, *material);
			glDrawElementsInstanced(GL_TRIANGLES, numberOfIndicies, GL_UNSIGNED_INT, 0, numberToRender);
		}

		void setNumberToRender(unsigned int numb) { numberToRender = numb; }

	protected:
		unsigned int numberToRender{ 0 };
	};
}