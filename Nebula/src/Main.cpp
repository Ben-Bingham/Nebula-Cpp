#include <iostream>

#include "Camera.h"
#include "Engine.h"
#include "Powers.h"
#include "Window.h"
#include "Renderers/Renderer.h"
#include "World/BlockManager.h"
#include "World/Chunk.h"
#include "OpenGL objects/Texture.h"
#include "Renderable Objects/SkyBox.h"
#include "Rendering/TextureAtlas.h"
#include "Materials/PhongMaterial.h"
#include "Timing.h"
#include "Geometry/Mesh.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Materials/Material.h"

#include "Physics/CelestialPhysician.h"
#include "Physics/CelestialPhysics.h"
#include "Physics/PhysicsCalculator.h"

#include "Rendering/ChunkMaterial.h"
#include "Rendering/ChunkRenderer.h"

#include "Space/CelestialBody.h"

#include "World/BlockRegister.h"

class MovementController {
public:
	float movementSpeed{ 0.1f };

	int lastXPosition{ 0 };
	int lastYPosition{ 0 };
	bool firstMouseMovement{ false };
	float mouseSensitivity{ 0.1f };
	Malachite::Degree yaw{ -90.0f };
	Malachite::Degree pitch{ 0.0f };
};

class Movement : public Esperite::System {
public:
	Movement() = default;
	~Movement() override = default;

	void StartUp(Esperite::Scene* scene) override {
		Wavellite::Window::Get().disableCursor();
	}

	void Step(Esperite::Scene* scene) override {
		for (auto& gb : scene->gameObjects) {
			if (scene->HasComponent<MovementController>(gb)
				&& scene->HasComponent<Malachite::Transform>(gb)
				&& scene->HasComponent<Ruby::Camera>(gb)) {

				MovementController* controller = scene->GetComponent<MovementController>(gb);
				Malachite::Transform* transform = scene->GetComponent<Malachite::Transform>(gb);
				Ruby::Camera* camera = scene->GetComponent<Ruby::Camera>(gb);

				const Wavellite::Keyboard& keyboard = Wavellite::Keyboard::Get();

				Malachite::Vector3f up = Malachite::Vector3f::up;
				Malachite::Vector3f left = cross(camera->forward, up).normalize();

				if (keyboard.KEY_W) { transform->position() += camera->forward * controller->movementSpeed; }
				if (keyboard.KEY_S) { transform->position() -= camera->forward * controller->movementSpeed; }
				if (keyboard.KEY_A) { transform->position() -= left * controller->movementSpeed; }
				if (keyboard.KEY_D) { transform->position() += left * controller->movementSpeed; }
				if (keyboard.KEY_SPACE) { transform->position() += up * controller->movementSpeed; }
				if (keyboard.KEY_LEFT_SHIFT) { transform->position() -= up * controller->movementSpeed; }

				if (Wavellite::Mouse::Get().hasMoved) {
					if (!controller->firstMouseMovement) {
						controller->lastXPosition = Wavellite::Mouse::Get().xPosition;
						controller->lastYPosition = Wavellite::Mouse::Get().yPosition;
						controller->firstMouseMovement = true;
					}

					float xOffset = (float)(Wavellite::Mouse::Get().xPosition - controller->lastXPosition);
					float yOffset = (float)(controller->lastYPosition - Wavellite::Mouse::Get().yPosition);
					controller->lastXPosition = Wavellite::Mouse::Get().xPosition;
					controller->lastYPosition = Wavellite::Mouse::Get().yPosition;

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

					camera->forward = direction.normalize();
				}

				if (keyboard.KEY_UP) { controller->movementSpeed += 0.1f; }
				if (keyboard.KEY_DOWN) { controller->movementSpeed -= 0.1f; }

				if (controller->movementSpeed < 0.001f) {
					controller->movementSpeed = 0.001f;
				}
			}
		}
	}
};

class GameController : public Esperite::System {
public:
	GameController() = default;
	~GameController() = default;

	void StartUp(Esperite::Scene* scene) override {
		// Wavellite::Window::Get().setSwapInterval(0);
	}

	void Step(Esperite::Scene* scene) override {
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - previousTime;
		LOG(std::to_string(1.0f / deltaTime));
		previousTime = currentTime;
		frameCount++;
		averageTime += deltaTime;

		if (Wavellite::Keyboard::Get().KEY_ESCAPE) {
			Wavellite::Window::Get().Close();
		}
	}

	void EndStep(Esperite::Scene* scene) override {
		
	}

	void ShutDown(Esperite::Scene* scene) override {
		LOG("Number of frames: " + std::to_string(frameCount));
		LOG("Average delta time: " + std::to_string(averageTime / frameCount));
		LOG("Average FPS: " + std::to_string(1.0f / (averageTime / frameCount)));

		// std::cin.get();
	}

	double previousTime = glfwGetTime();
	unsigned long long frameCount{ 0 };
	double averageTime{ 0 };
};

int main() {
	using namespace Celestite;

	Emerald::Engine engine{};
	Wavellite::Time time{};
	engine.AddDefaultSystems();

	Esperite::Scene scene{};
	engine.activeScene = &scene;

	engine.AddSystem(CreatePtr<Movement>());
	engine.AddSystem(CreatePtr<GameController>());
	engine.AddSystem(CreatePtr<Nebula::CelestialPhysician>());

	const Esperite::GameObject player = scene.NewGameObject<Malachite::Transform, MovementController, Ruby::Camera>();
	Malachite::Transform* playerTransform = scene.GetComponent<Malachite::Transform>(player);
	playerTransform->position().z = 5.0f;

	auto cubeGeometry = Celestite::CreatePtr<Ruby::MeshData>(CreatePtr<Ruby::Cube>());

	auto sunMaterial = CreatePtr<Ruby::SolidMaterial>();
	sunMaterial->colour = Ruby::Colour{ 255, 255, 0 };
	//
	// auto earthMaterial = CreatePtr<Ruby::SolidMaterial>();
	// earthMaterial->colour = Ruby::Colour{ 0, 255, 0 };
	//
	// auto moonMaterial = CreatePtr<Ruby::SolidMaterial>();
	// moonMaterial->colour = Ruby::Colour{ 0, 0, 255 };

	// Celestial body playground
	// Nebula::CelestialBody sun{ 1.989f * (Nebula::Kilogram)pow(10.0f, 30), 696340.0f, 0.0f, Ruby::Colour{ 229,79,6 } };
	//
	// Nebula::CelestialBody earth{ 5.97f * (Nebula::Kilogram)pow(10.0f, 24), 6.37f * (Nebula::Meter)pow(10.0f, 6), 149320000, Ruby::Colour{19,26,45} };
	// sun.addChild(earth);

	// Esperite::GameObject moon = scene.NewGameObject<Ruby::Mesh, Ruby::Material, Malachite::Transform, Nebula::CelestialPhysics>();
	// scene.GetComponent<Ruby::Mesh>(moon)->mesh = cubeGeometry;
	// scene.GetComponent<Ruby::Material>(moon)->material = moonMaterial;
	// auto* moonTransform = scene.GetComponent<Malachite::Transform>(moon);
	// moonTransform->scale() *= 0.5f;
	// moonTransform->position().x = 25.0f;
	// moonTransform->position().y = 5.0f;
	// moonTransform->position().z = -5.0f;
	// auto* moonPhysics = scene.GetComponent<Nebula::CelestialPhysics>(moon);
	// moonPhysics->velocity.z = 0.3f;
	// moonPhysics->mass = 100.0f;
	//
	// Esperite::GameObject earth = scene.NewGameObject<Ruby::Mesh, Ruby::Material, Malachite::Transform, Nebula::CelestialPhysics>();
	// scene.GetComponent<Ruby::Mesh>(earth)->mesh = cubeGeometry;
	// scene.GetComponent<Ruby::Material>(earth)->material = earthMaterial;
	// auto* earthTransform = scene.GetComponent<Malachite::Transform>(earth);
	// earthTransform->position().x = 20.0f;
	// auto* earthPhysics = scene.GetComponent<Nebula::CelestialPhysics>(earth);
	// earthPhysics->velocity.z = 0.1f;
	// earthPhysics->mass = Nebula::PhysicsCalculator::MassCalculator((earthTransform->position() - moonTransform->position()).Magnitude(), moonPhysics->velocity.Magnitude());
	//
	// Esperite::GameObject sun = scene.NewGameObject<Ruby::Mesh, Ruby::Material, Malachite::Transform
	// , Nebula::CelestialPhysics
	// >();
	// scene.GetComponent<Ruby::Mesh>(sun)->mesh = cubeGeometry;
	// scene.GetComponent<Ruby::Material>(sun)->material = sunMaterial;
	// auto* sunTransform = scene.GetComponent<Malachite::Transform>(sun);
	// sunTransform->scale() *= 3.0f;
	// auto* sunPhysics = scene.GetComponent<Nebula::CelestialPhysics>(sun);
	// sunPhysics->mass = Nebula::PhysicsCalculator::MassCalculator((sunTransform->position() - earthTransform->position()).Magnitude(), earthPhysics->velocity.Magnitude());

	// Blocks
	using namespace Nebula;

	auto& imageRegister = ImageRegister::Get();
	auto& blockRegister = BlockRegister::Get();

	ImageIndex dirtImageIndex = imageRegister.Register(ImageElement{ "DIRT", Ruby::Image{"assets\\images\\textures\\dirt.png"} });

	const BlockIndex dirtIndex = blockRegister.Register(Block{ "Dirt", { dirtImageIndex, dirtImageIndex, dirtImageIndex , dirtImageIndex, dirtImageIndex, dirtImageIndex } });

	const Ptr<ChunkMaterial> chunkMaterial = CreatePtr<ChunkMaterial>(CreatePtr<Ruby::Image>(imageRegister[dirtImageIndex].image)); // TODO replace with acutal image and not just a badly ownd image

	const Esperite::GameObject testChunk = scene.NewGameObject<Chunk, Ruby::Material>();
	auto* testChunkMaterial = scene.GetComponent<Ruby::Material>(testChunk);
	testChunkMaterial->material = chunkMaterial;

	auto& chunk = *scene.GetComponent<Chunk>(testChunk);

	for (unsigned int x = 0; x < Chunk::xSize; x++) {
		for (unsigned int y = 0; y < Chunk::ySize; y++) {
			for (unsigned int z = 0; z < Chunk::zSize; z++) {
				chunk[x][y][z] = dirtIndex;
			}
		}
	}

	engine.GetSystem<Ruby::Renderer>()->AddRenderFunction(ChunkRenderer::Render);

	engine.Start();
}