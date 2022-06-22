#include "Collisions.h"

namespace Collisions
{
	bool CheckCollision(const Rigibody* rb1, const Rigibody* rb2)
	{
		if (rb1->GetCollider()->GetShapeType() == Collider::ShapeType::Circle && 
			rb2->GetCollider()->GetShapeType() == Collider::ShapeType::Circle)
		{
			const auto circle1 = dynamic_cast<CircleCollider*>(rb1->GetCollider());
			const auto circle2 = dynamic_cast<CircleCollider*>(rb2->GetCollider());

			const double distanceBetweenCenters = (rb1->GetPos() - rb2->GetPos()).Magnitude();

			if (distanceBetweenCenters <= circle1->GetRadius() || distanceBetweenCenters <= circle2->GetRadius())
				return true;

			return false;
		}

		return false;
	}
}
