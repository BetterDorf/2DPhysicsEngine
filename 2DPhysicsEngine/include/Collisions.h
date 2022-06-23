#pragma once

#include "Rigibody.h"
#include "CircleCollider.h"

namespace Collisions
{
	struct ColData
	{
	public:
		ColData() = default;
		explicit ColData(const bool col) : HasCollided(col) {}

		bool HasCollided = false;
	};

	ColData CheckCollision(const Rigibody* rb1, const Rigibody* rb2);
	void SolveOverlap(Rigibody* rb1, Rigibody* rb2);
	void SolveVelocities(Rigibody* rb1, Rigibody* rb2);
}