#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "World/BlockManager.h"
#include "World/Chunk.h"

const unsigned int worldSize{ 5 };

Ruby::Camera camera{ Malachite::Vector3f{ worldSize / 2 * 16.0f, 90.0f, worldSize / 2 * 16.0f } };

struct FPSController {
	bool firstMouse = true;
	int lastX = 0;
	int lastY = 0;
	float mouseSensitivity = 0.1f;
	Malachite::Degree yaw = -90.0f;
	Malachite::Degree pitch;

	float speed = 0.1f;
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

void mouseScrollCallback(int xoffset, int yoffset, void* data) {
	FPSController* controller = (FPSController*)data;
	controller->speed += yoffset * 0.001f;

	if (controller->speed < 0) {
		controller->speed = 0;
	}
}

int main() {
	Ruby::Window window{ 640, 480 };
	Ruby::Mouse* mouse = &window.ioManger.mouse;
	Ruby::Keyboard* keyboard = &window.ioManger.keyboard;

	mouse->addMousePositionCallback(mousePositionCallback, (void*)&fpsController);
	mouse->addScrollCallback(mouseScrollCallback, (void*)&fpsController);
	window.disableCursor();

	Ruby::Renderer renderer{ };

	Ruby::VertexShader phongInstanceVertexShader{ Ruby::TextFile{ "assets\\shaders\\PhongInstance.vert" } };
	Ruby::FragmentShader phongInstanceFragmentShader{ Ruby::TextFile{ "assets\\shaders\\PhongInstance.frag" } };
	Ruby::ShaderProgram phongInstanceProgram{ phongInstanceVertexShader, phongInstanceFragmentShader, std::vector<Ruby::Attribute>{ 3, 3, 2 } };

	renderer.addShader(phongInstanceProgram);

	Ruby::Image containerImage{ "assets\\images\\container.png" };
	Ruby::Image containerSpecularImage{ "assets\\images\\container_specular.png" };

	Ruby::Texture diffuseTexture{ containerImage };
	Ruby::Texture specularTexture{ containerSpecularImage };

	Ruby::PhongMaterial cubeMaterial{ diffuseTexture, specularTexture };

	Ruby::Image textureAtlasImage{ Malachite::Vector3f{1.0f, 0.0f, 0.0f } }; //TODO not solid colour // TODO index 0 should be unknown and 1 should be air
	Ruby::Texture textureAtlas{ textureAtlasImage };
	Ruby::PhongMaterial atlasMaterial{ textureAtlas, textureAtlas }; //TODO atlas for specular textures //TODO make the texture atlas static

	Nebula::BlockManager::addBlock(Nebula::Block{ "BLOCK_AIR", std::array<unsigned int, 6>{1, 1, 1, 1, 1, 1} });
	Nebula::BlockManager::addBlock(Nebula::Block{ "BLOCK_CONTAINER", std::array<unsigned int, 6>{2, 2, 2, 2, 2, 2} });
	
	// TODO chunk manager
	std::vector<Nebula::Chunk> chunks{};

	Nebula::ChunkRenderable chunkRenderable{ atlasMaterial };

	for (unsigned int x = 0; x < worldSize; x++) {
		for (unsigned int y = 0; y < worldSize; y++) {
			chunks.push_back(Nebula::Chunk{ Malachite::Vector2i{(int)x, (int)y}, chunkRenderable });
			chunks.back().generateBlocks();
		}
	}

	Nebula::Chunk airChunk{ Malachite::Vector2i{0, 0}, chunkRenderable };

	Nebula::Block* airBlock = Nebula::BlockManager::getBlock("BLOCK_AIR");

	for (unsigned int x = 0; x < airChunk.blocks.size(); x++) {
		for (unsigned int y = 0; y < airChunk.blocks[x].size(); y++) {
			for (unsigned int z = 0; z < airChunk.blocks[x][y].size(); z++) {
				airChunk.blocks[x][y][z] = airBlock;
			}
		}
	}

	unsigned int i{ 0 };
	for (Nebula::Chunk& chunk : chunks) {
		int x = i / worldSize;
		int y = i % worldSize;

		Nebula::Chunk* posX{ &airChunk };
		Nebula::Chunk* negX{ &airChunk };
		Nebula::Chunk* posY{ &airChunk };
		Nebula::Chunk* negY{ &airChunk };

		Malachite::Vector2i posXAbsCords{ x + 1, y };
		Malachite::Vector2i negXAbsCords{ x - 1, y };
		Malachite::Vector2i posYAbsCords{ x, y + 1 };
		Malachite::Vector2i negYAbsCords{ x, y - 1 };

		for (Nebula::Chunk& chunk : chunks) {
			if (chunk.absolutePosition == posXAbsCords) {
				posX = &chunk;
			}
			else if (chunk.absolutePosition == negXAbsCords) {
				negX = &chunk;
			}
			else if (chunk.absolutePosition == posYAbsCords) {
				posY = &chunk;
			}
			else if (chunk.absolutePosition == negYAbsCords) {
				negY = &chunk;
			}
		}

		chunk.createTextureBuffer(*posX, *negX, *posY, *negY);
		i++;
	}


	Ruby::DirectionalLight dirLight{};
	std::vector<Ruby::DirectionalLight*> directionalLights{};
	directionalLights.push_back(&dirLight);

	renderer.shaders.phongShader.use();
	Ruby::ShaderProgram::upload("directionalLights", 2, directionalLights);

	phongInstanceProgram.use();
	Ruby::ShaderProgram::upload("directionalLights", 2, directionalLights);
	Ruby::ShaderProgram::upload("material", 0, atlasMaterial);

	renderer.init(window.getProjectionMatrix());

	double previousTime = glfwGetTime();
	unsigned long long frameCount{ 0 };
	double averageTime{ 0 };

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (window.isOpen() /*&& frameCount < 100*/) {
		window.pollEvents();

		if (keyboard->KEY_W) {
			camera.position += camera.front * fpsController.speed;
		}

		if (keyboard->KEY_A) {
			camera.position -= camera.right * fpsController.speed;
		}

		if (keyboard->KEY_S) {
			camera.position -= camera.front * fpsController.speed;
		}

		if (keyboard->KEY_D) {
			camera.position += camera.right * fpsController.speed;
		}

		if (keyboard->KEY_SPACE) {
			camera.position += Malachite::Vector3f{ 0.0f, 1.0f, 0.0f } * fpsController.speed;
		}

		if (keyboard->KEY_LEFT_SHIFT) {
			camera.position -= Malachite::Vector3f{ 0.0f, 1.0f, 0.0f } * fpsController.speed;
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

				for (Nebula::Chunk& chunk : chunks) {
					chunk.render();
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

	//std::cin.get();
}