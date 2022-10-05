#pragma once
#include "Vector2D.h"

namespace PhysicsConstants
{
	constexpr Vector2D gravityAcceleration(0.0, -9.806);

	static constexpr float deccelerationFactor = 0.1;

	static constexpr int maxBodiesInRegion = 8;
	static constexpr int maxQuadDepth = 5;
}
