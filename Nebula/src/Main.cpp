#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "Renderable Objects/Phong/PhongCube.h"

int main() {
	Ruby::Window window{ };
	Ruby::Renderer renderer{ };

	Ruby::Image red{ Malachite::Vector3f{1.0f, 0.0f, 0.0f} };

	Ruby::Texture diffuseTexture{ red };
	Ruby::Texture specularTexture{ red };

	Ruby::PhongMaterial cubeMaterial{ diffuseTexture, specularTexture };
	Ruby::PhongCube cube{ cubeMaterial };

	std::cin.get();
}