#pragma once

#include "Rigibody.h"
#include "CircleCollider.h"

namespace Collisions
{
	struct ColData
	{
	public:
		explicit ColData(const bool col) : HasCollided(col) {}

		bool HasCollided;
	};

	bool CheckCollision(const Rigibody* rb1, const Rigibody* rb2);
}