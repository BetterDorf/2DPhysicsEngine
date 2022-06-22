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

	bool CircleToCircleCollision(const CircleCollider* circle1, const CircleCollider* circle2);
	bool CheckCollision(Collider* col1, Collider* col2);
}