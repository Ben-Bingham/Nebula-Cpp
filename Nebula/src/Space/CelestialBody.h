#pragma once

#include <vector>

#include "PhysicsObject.h"

#include "Utility/Colour.h"

#include "Units.h"

namespace Nebula {
	class CelestialBody {
	public:
		CelestialBody(const Pyrite::Kilogram mass, const Pyrite::Meter radius, Pyrite::Meter distanceFromParent, const Ruby::Colour colour)
			: m_Mass(mass), m_Radius(radius), m_DistanceFromParent(distanceFromParent), m_AverageColour(colour) { }

		void addChild(const CelestialBody& body) {
			m_Children.push_back(body);
		}

	private:
		Pyrite::PhysicsObject m_PhysicsObject;

		Pyrite::Kilogram m_Mass;
		Pyrite::Meter m_Radius;
		Pyrite::Meter m_DistanceFromParent;
		Ruby::Colour m_AverageColour; // TODO replace with texture

		std::vector<CelestialBody> m_Children;
	};
}