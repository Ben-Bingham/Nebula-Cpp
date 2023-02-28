#pragma once
#include "CelestialPhysics.h"
#include "Powers.h"
#include "System.h"

#include "Utility/Transform.h"

namespace Nebula {
	const float GRAVITATIONAL_CONSTANT{ Malachite::ee(6.67430f, -11.0f) };
	class CelestialPhysician : public Esperite::System {
	public:
		CelestialPhysician() = default;
		~CelestialPhysician() override = default;

		void Step(Esperite::Scene* scene) override {
			for (auto& gb1 : scene->gameObjects) {
				if (scene->HasComponent<CelestialPhysics>(gb1) &&
					scene->HasComponent<Malachite::Transform>(gb1)) {
					CelestialPhysics* physics1 = scene->GetComponent<CelestialPhysics>(gb1);
					Malachite::Transform* transform1 = scene->GetComponent<Malachite::Transform>(gb1);

					for (auto& gb2 : scene->gameObjects) {
						if (gb1 == gb2) {
							continue;
						}
					
						if (scene->HasComponent<CelestialPhysics>(gb2) &&
							scene->HasComponent<Malachite::Transform>(gb2)) {
							CelestialPhysics* physics2 = scene->GetComponent<CelestialPhysics>(gb2);
							Malachite::Transform* transform2 = scene->GetComponent<Malachite::Transform>(gb2);
							
							const Malachite::Vector3f displacementBetween = transform2->position() - transform1->position();
							const float distanceBetween = displacementBetween.length();

							const float inwardAcceleration = (physics1->velocity.Magnitude() * physics1->velocity.Magnitude()) / distanceBetween;
							physics1->acceleration += inwardAcceleration;
							int a = 1;
							// float gravitationalForce = (GRAVITATIONAL_CONSTANT * physics1->mass * physics2->mass) / (distanceBetween * distanceBetween);
							//
							// Malachite::Vector3f direction = displacementBetween.normalize();
							// Malachite::Vector3f gravitationalForce3D = gravitationalForce * direction;
							//
							// gravitationalForce3D /= physics1->mass;
							// physics1->acceleration += gravitationalForce3D;
						}
					}

					physics1->velocity += physics1->acceleration;
					// physics1->acceleration = 0.0f;
					// transform1->position() += physics1->velocity;
					// physics1->velocity = 0.0f;
					// LOG(transform1->position().toString());
				}
			}
		}
	};
}