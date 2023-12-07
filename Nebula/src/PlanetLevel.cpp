#include "PlanetLevel.h"
#include "ChunkSystem.h"
#include "Player.h"
#include "Entity Component System/ComponentView.h"
#include "Rendering/Components/Camera.h"
#include "Rendering/Systems/FpsCameraSystem.h"

namespace Nebula {
	void PlanetLevel::Load() {
		//m_Ecs.systems.push_back(Gem::CreatePtr<ChunkSystem>());
		//m_Ecs.systems.push_back(Gem::CreatePtr<Gem::FpsCameraSystem>());

		Gem::Entity player = m_Ecs.entityManager.Create();
		//m_Ecs.entityManager.Insert<Player>(player);
		//m_Ecs.entityManager.Insert<Gem::Transform>(player);
		//m_Ecs.entityManager.Insert<Gem::Camera>(player, Gem::Camera::CameraType::FPS);
	}

	void PlanetLevel::Unload() {

	}
}