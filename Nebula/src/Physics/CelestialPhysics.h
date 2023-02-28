#pragma once
#include "Vector.h"

namespace Nebula {
	class CelestialPhysics { //TODO eventually this sould extend a base class with basic physics info from pyrite
	public:
		CelestialPhysics() = default;

		float mass;
		Malachite::Vector3f velocity{};
		Malachite::Vector3f acceleration{};
	};
}