#include "Collisions.h"

namespace Collisions
{
	bool CheckCollision(Collider* col1, Collider* col2)
	{
		if (col1->GetShapeType() == Collider::ShapeType::Circle && col2->GetShapeType() == Collider::ShapeType::Circle)
		{
			const auto circle1 = dynamic_cast<CircleCollider*>(col1);
			const auto circle2 = dynamic_cast<CircleCollider*>(col2);

			return CircleToCircleCollision(circle1, circle2);
		}

		return false;
	}

	bool CircleToCircleCollision(const CircleCollider* circle1, const CircleCollider* circle2)
	{
		const double distanceToC2Center = (circle1->GetRigibody()->GetPos() - circle2->GetRigibody()->GetPos()).Magnitude();

		if (distanceToC2Center <= circle1->GetRadius())
		{
			return true;
		}

		return false;
	}
}
