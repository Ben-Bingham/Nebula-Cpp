#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "Renderable Objects/Phong/PhongCube.h"
#include "TextFile.h"

#include "PhongInstanceRenderable.h"

Ruby::Camera camera{ Malachite::Vector3f{0.0f, 0.0f, 3.0f } };
struct FPSController {
	bool firstMouse = true;
	int lastX = 0;
	int lastY = 0;
	float mouseSensitivity = 0.1f;
	Malachite::Degree yaw = -90.0f;
	Malachite::Degree pitch;
};
FPSController fpsController{ };

void mousePositionCallback(int xpos, int ypos, void* data) {
	FPSController* controller = (FPSController*)data;

	if (controller->firstMouse) {
		controller->lastX = (int)xpos;
		controller->lastY = (int)ypos;
		controller->firstMouse = false;
	}

	float xOffset = (float)(xpos - controller->lastX);
	float yOffset = (float)(controller->lastY - ypos);
	controller->lastX = (int)xpos;
	controller->lastY = (int)ypos;

	xOffset *= controller->mouseSensitivity;
	yOffset *= controller->mouseSensitivity;

	controller->yaw += xOffset;
	controller->pitch += yOffset;

	if (controller->pitch > 89.0f)
		controller->pitch = 89.0f;
	if (controller->pitch < -89.0f)
		controller->pitch = -89.0f;

	Malachite::Vector3f direction;
	direction.x = cos(Malachite::degreesToRadians(controller->yaw)) * cos(Malachite::degreesToRadians(controller->pitch));
	direction.y = sin(Malachite::degreesToRadians(controller->pitch));
	direction.z = sin(Malachite::degreesToRadians(controller->yaw)) * cos(Malachite::degreesToRadians(controller->pitch));

	camera.front = Malachite::normalize(direction);
	camera.updateCameraVectors();
}

const unsigned int xSize{ 16 };
const unsigned int ySize{ 256 };
const unsigned int zSize{ 16 };
//
//using Chunk = unsigned char[xSize][ySize][zSize];
//
const std::vector<unsigned int> indices{
		0, 1, 2,
		1, 3, 2,
		4, 5, 6,
		5, 7, 6,
		8, 9, 10,
		9, 11, 10,
		12, 13, 14,
		13, 15, 14,
		16, 17, 18,
		17, 19, 18,
		20, 21, 22,
		21, 23, 22,
};

const std::vector<float> verticies{
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f, 1.0f, 1.0f,

	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0, 0.0f, 0.0,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0, 0.0f, 1.0,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0, 1.0f, 0.0,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0, 1.0f, 1.0,

	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f, 1.0f, 1.0f,

	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f, 1.0f, 1.0f
};

int main() {
	Ruby::Window window{ };
	Ruby::Mouse* mouse = &window.ioManger.mouse;
	Ruby::Keyboard* keyboard = &window.ioManger.keyboard;

	mouse->addMousePositionCallback(mousePositionCallback, (void*)&fpsController);
	window.disableCursor();

	Ruby::Renderer renderer{ };

	Ruby::VertexShader phongInstanceVertexShader{ Ruby::TextFile{ "assets\\shaders\\PhongInstance.vert" } };
	Ruby::GeometryShader phongInstanceGeometryShader{ Ruby::TextFile{ "assets\\shaders\\PhongInstance.geom" } };
	Ruby::FragmentShader phongInstanceFragmentShader{ Ruby::TextFile{ "assets\\shaders\\PhongInstance.frag" } };
	Ruby::ShaderProgram phongInstanceProgram{ phongInstanceVertexShader, phongInstanceGeometryShader, phongInstanceFragmentShader, std::vector<Ruby::Attribute>{ 3, 3, 2 } };

	renderer.addShader(phongInstanceProgram);

	Ruby::Image containerImage{ "assets\\images\\container.png" };
	Ruby::Image containerSpecularImage{ "assets\\images\\container_specular.png" };

	Ruby::Texture diffuseTexture{ containerImage };
	Ruby::Texture specularTexture{ containerSpecularImage };

	Ruby::PhongMaterial cubeMaterial{ diffuseTexture, specularTexture };
	Nebula::PhongInstanceRenderable cube{ std::vector<float>{ 0.0f, 0.0f, 0.0f }, std::vector<unsigned int>{ 0 }, cubeMaterial};

	std::vector<unsigned char> content{};

	/*content.resize(256 * 256 * 3);

	for (unsigned int i = 0; i < 256 * 256 * sizeof(unsigned char); i += 3) {
		content[i + 0u] = 1u;
		content[i + 1u] = 2u;
		content[i + 2u] = 3u;
	}*/


	for (size_t x = 0; x < xSize; x++) {
		for (size_t y = 0; y < ySize; y++) {
			for (size_t z = 0; z < zSize; z++) {
				content.push_back(static_cast<unsigned int>(x));
				content.push_back(static_cast<unsigned int>(y));
				content.push_back(static_cast<unsigned int>(z));
			}
		}
	}

	Ruby::Image offsetImage(content, 256, 256, 3);
	Ruby::Texture offsetTexture(offsetImage);

	//Chunk testChunk;

	// World Generation
	/*for (size_t x = 0; x < xSize; x++) {
		for (size_t y = 0; y < ySize; y++) {
			for (size_t z = 0; z < zSize; z++) {
				testChunk[x][y][z] = 1;
			}
		}
	}*/

	Ruby::DirectionalLight dirLight{};
	std::vector<Ruby::DirectionalLight*> directionalLights{};
	directionalLights.push_back(&dirLight);

	renderer.shaders.phongShader.use();
	Ruby::ShaderProgram::upload("directionalLights", 2, directionalLights);

	phongInstanceProgram.use();
	Ruby::ShaderProgram::upload("directionalLights", 2, directionalLights);
	Ruby::ShaderProgram::upload("offsetTexture", 5, offsetTexture);

	renderer.init(window.getProjectionMatrix());

	double previousTime = glfwGetTime();
	unsigned long long frameCount{ 0 };
	double averageTime{ 0 };

	while (window.isOpen() && frameCount < 100) {
		window.pollEvents();
		float velocity = 0.1f;

		if (keyboard->KEY_W) {
			camera.position += camera.front * velocity;
		}

		if (keyboard->KEY_A) {
			camera.position -= camera.right * velocity;
		}

		if (keyboard->KEY_S) {
			camera.position -= camera.front * velocity;
		}

		if (keyboard->KEY_D) {
			camera.position += camera.right * velocity;
		}

		if (keyboard->KEY_SPACE) {
			camera.position += Malachite::Vector3f{ 0.0f, 1.0f, 0.0f } *velocity;
		}

		if (keyboard->KEY_LEFT_SHIFT) {
			camera.position -= Malachite::Vector3f{ 0.0f, 1.0f, 0.0f } *velocity;
		}

		if (keyboard->KEY_ESCAPE) {
			window.close();
		}

		{ // Rendering
			renderer.prep(camera.getViewMatrix());

			{ // Normal Rendering
				renderer.phongRenderingPrep();

				// Cube
				Ruby::ShaderProgram::upload("cameraPosition", camera.position);

				renderer.phongRenderingEnd();
			}

			{ // Phong instance
				phongInstanceProgram.use();

				Ruby::ShaderProgram::upload("cameraPosition", camera.position);


				for (unsigned int x = 0; x < 5; x++) {
					for (unsigned int y = 0; y < 5; y++) {
						cube.model.translate(x * 16, 0, y * 16);
						cube.render();
						cube.model = Malachite::Matrix4f{ 1.0f };
					}
				}
			}

			renderer.end();
		}

		window.swapBuffers();

		double currentTime = glfwGetTime();
		double deltaTime = currentTime - previousTime;
		LOG(std::to_string(1.0f / deltaTime));
		previousTime = currentTime;
		frameCount++;
		averageTime += deltaTime;
	}

	LOG("Number of frames: " + std::to_string(frameCount));
	LOG("Average delta time: " + std::to_string(averageTime / frameCount));
	LOG("Average FPS: " + std::to_string(1.0f / (averageTime / frameCount)));

	std::cin.get();
}