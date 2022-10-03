#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "Renderable Objects/Phong/PhongCube.h"

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


int main() {
	Ruby::Window window{ };
	Ruby::Mouse* mouse = &window.ioManger.mouse;
	Ruby::Keyboard* keyboard = &window.ioManger.keyboard;

	mouse->addMousePositionCallback(mousePositionCallback, (void*)&fpsController);
	window.disableCursor();

	Ruby::Renderer renderer{ };

	Ruby::Image red{ Malachite::Vector3f{ 1.0f, 0.0f, 0.0f } };

	Ruby::Texture diffuseTexture{ red };
	Ruby::Texture specularTexture{ red };

	Ruby::PhongMaterial cubeMaterial{ diffuseTexture, specularTexture };
	Ruby::PhongCube cube{ cubeMaterial };

	Ruby::DirectionalLight dirLight{};
	std::vector<Ruby::DirectionalLight*> directionalLights{};
	directionalLights.push_back(&dirLight);

	renderer.shaders.phongShader.use();
	Ruby::ShaderProgram::upload("directionalLights", 2, directionalLights);

	renderer.init(window.getProjectionMatrix());

	while (window.isOpen()) {
		window.pollEvents();
		float velocity = 0.05f;

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

		LOG(std::to_string(mouse->xPosition));
		{ // Rendering
			renderer.prep(camera.getViewMatrix());
			{ // Normal Rendering
				renderer.phongRenderingPrep();

				// Cube
				Ruby::ShaderProgram::upload("cameraPosition", camera.position);

				cube.model = Malachite::Matrix4f{ 1.0f };
				cube.model.rotate(Malachite::degreesToRadians(90.0f), Malachite::Vector3f((float)sin(glfwGetTime()), 1.0f, 0.0f));

				renderer.phongRender(cube);

				renderer.phongRenderingEnd();
			}
			renderer.end();
		}

		window.swapBuffers();
	}
}