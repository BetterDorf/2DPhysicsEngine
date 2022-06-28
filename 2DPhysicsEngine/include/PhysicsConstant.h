#pragma once
#include "Vector2D.h"

namespace PhysicsConstants
{
	static constexpr double gravHorizontal = 0.0;
	static constexpr double gravVertical = -9.806;

	constexpr Vector2D GRAVITY_ACCELERATION(gravHorizontal, gravVertical);
}