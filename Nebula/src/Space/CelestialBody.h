#pragma once

#include <vector>

#include "Colour.h"

namespace Nebula {
	using Kilogram = float;
	using Meter = float;

	class CelestialBody {
	public:
		CelestialBody(Kilogram Mass, Meter Radius, Meter DistanceFromParent, Ruby::Colour colour)
			: mass(Mass), radius(Radius), distanceFromParent(DistanceFromParent), averageColour(colour) { }

		void addChild(const CelestialBody& body) {
			children.push_back(body);
		}

	private:
		Kilogram mass;
		Meter radius;
		Meter distanceFromParent;
		Ruby::Colour averageColour; // TODO replace with texture

		std::vector<CelestialBody> children;
	};
}