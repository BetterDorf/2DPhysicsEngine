#include "Collisions.h"
#include "CircleShape.h"

namespace Collisions
{
	ColData MakeColData(Rigibody* rb1, Rigibody* rb2)
	{
		return ColData(rb1, rb2);
	}

	bool CheckCollision(const Rigibody* rb1, const Rigibody* rb2)
	{
		if (rb1->GetCollider()->GetShapeType() == PhysicShape::ShapeType::Circle &&
			rb2->GetCollider()->GetShapeType() == PhysicShape::ShapeType::Circle)
		{
			return CheckCollisionCircle(rb1, rb2);
		}
		else
		{
			//Check the bounding circle of the two shapes
			if (CheckCollisionCircle(rb1, rb2))
				return CheckCollisionGJK(rb1, rb2);
			return false;
		}

	}

	bool CheckCollisionCircle(const Rigibody* rb1, const Rigibody* rb2)
	{
		const double distanceBetweenCenters = (rb1->GetPos() - rb2->GetPos()).Magnitude();

		if (distanceBetweenCenters <= rb1->GetCollider()->GetBoundingCircleRad() + rb2->GetCollider()->GetBoundingCircleRad())
		{
			return true;
		}

		return false;
	}

	bool CheckCollisionGJK(const Rigibody* rb1, const Rigibody* rb2)
	{
		//All points used in this algorithm are put into their world coordinates counterpart

		//Get starting direction
		Vector2D dir = (rb2->GetPos() - rb1->GetPos()).Normalize();

		//Construct a simplex (triangle), if the origin is inside of it, we are colliding
		//Form first point
		std::vector simplex{ GJKSupportFunction(rb1, rb2, dir) };

		//next direction is towards the origin
		dir = Vector2D(0.0, 0.0) - simplex[0];

		while (true)
		{
			Vector2D A = GJKSupportFunction(rb1, rb2, dir);

			//Shapes don't intersect if next support point doesn't pass the origin
			if (Vector2D::DotProduct(A, dir) < 0.0)
			{
				return false;
			}

			simplex.emplace_back(A);

			//Check if we have the origin in our simplex
			if (GJKHandleSimplex(simplex, dir))
				return true;
		}
	}

	Vector2D GJKSupportFunction(const Rigibody* rb1, const Rigibody* rb2, const Vector2D dir)
	{
		return rb1->LocalToWorldPos(rb1->GetCollider()->GetFurthestPoint(dir))
		- rb2->LocalToWorldPos(rb2->GetCollider()->GetFurthestPoint(dir * -1));
	}

	bool GJKHandleSimplex(std::vector<Vector2D>& simplex, Vector2D& dir)
	{
		if (simplex.size() == 2)
		{
			//LINE CASE
			const Vector2D B = simplex[0];
			const Vector2D A = simplex[1];

			const Vector2D AB = (B - A).Normalize();
			const Vector2D AO = (Vector2D(0, 0) - A).Normalize();

			const Vector2D ABPerp = Vector2D::TripleProduct(AB, AO, AB);
			dir = ABPerp;
			return false;
		}
		else
		{
			//TRIANGLE CASE
			const Vector2D C = simplex[0];
			const Vector2D B = simplex[1];
			const Vector2D A = simplex[2];

			const Vector2D AB = (B - A).Normalize();
			const Vector2D AC = (C - A).Normalize();
			const Vector2D AO = (Vector2D(0, 0) - A).Normalize();

			const Vector2D ABPerp = Vector2D::TripleProduct(AC, AB, AB);
			const Vector2D ACPerp = Vector2D::TripleProduct(AB, AC, AC);

			//Check region AB for origin
			if (Vector2D::DotProduct(ABPerp, AO) > 0.0)
			{
				//Remove C
				simplex.erase(simplex.begin());
				dir = ABPerp;
				return false;
			}

			//Check region AC for origin
			if (Vector2D::DotProduct(ACPerp, AO) > 0.0)
			{
				//Remove B
				simplex.erase(simplex.begin() + 1);
				dir = ACPerp;
				return false;
			}

			//Origin must be within Simplex
			return true;
		}
	}

	void SolveOverlap(ColData col)
	{
		
	}

	void SolveVelocities(const ColData data)
	{
		Rigibody* rb1 = data.A;
		Rigibody* rb2 = data.B;

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
