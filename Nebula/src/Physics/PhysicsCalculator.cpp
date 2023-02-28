#include "PhysicsCalculator.h"

#include "CelestialPhysician.h"

#include "Utility/Transform.h"

namespace Nebula {
	// CelestialPhysics PhysicsCalculator::SpeedBasedCalculation(const CelestialPhysics& parent, float velocity) {
	// 	
	// }
	//
	// CelestialPhysics PhysicsCalculator::DistanceBasedCalculation(const CelestialPhysics& parent, float distanceAboveSurface) {
	// 	
	// }

	float PhysicsCalculator::MassCalculator(float distance, float velocity) {
		return ((velocity * velocity) * distance) / GRAVITATIONAL_CONSTANT;
	}
}