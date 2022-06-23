#pragma once
#include "Vector.h"

namespace PhysicsConstants
{
	static constexpr double gravHorizontal = 0.0;
	static constexpr double gravVertical = -9.806;

	constexpr Vector GRAVITY_ACCELERATION(gravHorizontal, gravVertical);
}