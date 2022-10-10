#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "Renderable Objects/Phong/PhongCube.h"
#include "TextFile.h"

#include "OpenGL objects/BufferTexture.h"

#include "PhongInstanceRenderable.h"

#include "BlockManager.h"
#include "Arrays/IndexCordinateConversion.h"

#include "Chunk.h"

const unsigned int worldSize{ 5 };

Ruby::Camera camera{ Malachite::Vector3f{ worldSize / 2 * 16.0f, 90.0f, worldSize / 2 * 16.0f } };
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
	Ruby::Window window{ 640, 480 };
	Ruby::Mouse* mouse = &window.ioManger.mouse;
	Ruby::Keyboard* keyboard = &window.ioManger.keyboard;

	mouse->addMousePositionCallback(mousePositionCallback, (void*)&fpsController);
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