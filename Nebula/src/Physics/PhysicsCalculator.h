#pragma once
#include "CelestialPhysics.h"
#include "GameObject.h"
#include "Scene.h"

namespace Nebula {
	class PhysicsCalculator {
	public:
		// static CelestialPhysics SpeedBasedCalculation(const CelestialPhysics& parent, float velocity);
		// static CelestialPhysics DistanceBasedCalculation(const CelestialPhysics& parent, float distance);
		static float MassCalculator(float distance, float velocity); // Calculates the mass of the parent object based on properties of the child
	};
}