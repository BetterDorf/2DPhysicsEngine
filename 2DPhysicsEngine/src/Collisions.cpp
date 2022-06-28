#include "Collisions.h"

namespace Collisions
{
	ColData CheckCollision(const Rigibody* rb1, const Rigibody* rb2)
	{
		ColData data;
		data.HasCollided = false;

		if (rb1->GetCollider()->GetShapeType() == PhysicShape::ShapeType::Circle && 
			rb2->GetCollider()->GetShapeType() == PhysicShape::ShapeType::Circle)
		{
			const auto circle1 = dynamic_cast<CircleShape*>(rb1->GetCollider());
			const auto circle2 = dynamic_cast<CircleShape*>(rb2->GetCollider());

			const double distanceBetweenCenters = (rb1->GetPos() - rb2->GetPos()).Magnitude();

			if (distanceBetweenCenters <= circle1->GetRadius() + circle2->GetRadius())
			{
				data.HasCollided = true;
			}
		}

		return data;
	}

	void SolveOverlap(Rigibody* rb1, Rigibody* rb2)
	{
		
	}

	void SolveVelocities(Rigibody* rb1, Rigibody* rb2)
	{
		//Find the normal and tangent vector of the collision
		const Vector2D normalVector = (rb2->GetPos() - rb1->GetPos()).Normalize();
		const Vector2D tangVector = normalVector.GetPerpendicularVector(true);

		//Calculate projections of V1 on normal and tangent
		const double V1n = (normalVector.X * rb1->GetVelocity().X + normalVector.Y * rb1->GetVelocity().Y);
		const double V1t = (tangVector.X * rb1->GetVelocity().X + tangVector.Y * rb1->GetVelocity().Y);

		//Calculate projections of V2 on normal and tangent
		const double V2n = (normalVector.X * rb2->GetVelocity().X + normalVector.Y * rb2->GetVelocity().Y);
		const double V2t = (tangVector.X * rb2->GetVelocity().X + tangVector.Y * rb2->GetVelocity().Y);

		//Set velocities according to their elastic collisions on each axis
		rb1->SetVelocity(Vector2D(normalVector.X * V2n + tangVector.X * V1t,
			normalVector.Y * V2n + tangVector.Y * V1t));
		rb2->SetVelocity(Vector2D(normalVector.X * V1n + tangVector.X * V2t,
			normalVector.Y * V1n + tangVector.Y * V2t));
	}
}
