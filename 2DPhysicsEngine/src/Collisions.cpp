#include "Collisions.h"

#include "CircleShape.h"
#include "MathUtils.h"

namespace Collisions
{
	ColData CheckCollision(Rigibody* rb1, Rigibody* rb2)
	{
		ColData colData(rb1, rb2);

		if (rb1->GetCollider()->GetShapeType() == PhysicShape::ShapeType::Circle &&
			rb2->GetCollider()->GetShapeType() == PhysicShape::ShapeType::Circle)
		{
			CheckCollisionCircle(colData);
		}
		else
		{
			//Check the bounding circle of the two shapes
			if (CheckCollisionCircle(colData); colData.HasCollided)
				CheckCollisionGJK(colData);
		}

		return colData;
	}

	void CheckCollisionCircle(ColData& colData)
	{
		const Rigibody* rb1 = colData.A;
		const Rigibody* rb2 = colData.B;

		const double distanceBetweenCenters = (rb1->GetPos() - rb2->GetPos()).Magnitude();

		if (distanceBetweenCenters <= rb1->GetCollider()->GetBoundingCircleRad() + rb2->GetCollider()->GetBoundingCircleRad())
		{
			colData.HasCollided = true;
			return;
		}

		colData.HasCollided = false;
	}

	void CheckCollisionGJK(ColData& colData)
	{
		const Rigibody* rb1 = colData.A;
		const Rigibody* rb2 = colData.B;

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
				colData.HasCollided = false;
				return;
			}

			simplex.emplace_back(A);

			//Check if we have the origin in our simplex
			if (GJKHandleSimplex(simplex, dir))
			{
				colData.HasCollided = true;
				colData.Simplex = simplex;
				return;
			}
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

			const Vector2D ABPerp = Vector2D::TripleProduct(AB, AO, AB).Normalize();
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

			const Vector2D ABPerp = Vector2D::TripleProduct(AC, AB, AB).Normalize();
			const Vector2D ACPerp = Vector2D::TripleProduct(AB, AC, AC).Normalize();

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

	void SolveOverlap(const ColData& data)
	{
		
	}

	void SolveVelocities(const ColData& data)
	{
		Rigibody* rb1 = data.A;
		Rigibody* rb2 = data.B;

		const double v1 = rb1->GetVelocity().Magnitude();
		const double v2 = rb2->GetVelocity().Magnitude();

		const double m1 = rb1->GetMass();
		const double m2 = rb2->GetMass();

		const double theta1 = rb1->GetVelocity().AngleRadWithOAxis();
		const double theta2 = rb2->GetVelocity().AngleRadWithOAxis();

		//TEMPORARY SOLUTION UNTIL WE HAVE CONTACT MANIFOLD
		const double phi = (rb2->GetPos() - rb1->GetPos()).AngleRadWithOAxis();

		const double v1fx = ((v1 * std::cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * std::cos(theta2 - phi)) / (m1 + m2))
			* std::cos(phi) + v1 * std::sin(theta1 - phi) * std::cos(phi + mathUtils::pi / 2);
		const double v1fy = ((v1 * std::cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * std::cos(theta2 - phi)) / (m1 + m2))
			* std::sin(phi) + v1 * std::sin(theta1 - phi) * std::sin(phi + mathUtils::pi / 2);

		const double v2fx = ((v2 * std::cos(theta2 - phi) * (m2 - m1) + 2 * m1 * v1 * std::cos(theta1 - phi)) / (m2 + m1))
			* std::cos(phi) + v2 * std::sin(theta2 - phi) * std::cos(phi + mathUtils::pi / 2);
		const double v2fy = ((v2 * std::cos(theta2 - phi) * (m2 - m1) + 2 * m1 * v1 * std::cos(theta1 - phi)) / (m2 + m1))
			* std::sin(phi) + v2 * std::sin(theta2 - phi) * std::sin(phi + mathUtils::pi / 2);

		rb1->SetVelocity(Vector2D(v1fx, v1fy));
		rb2->SetVelocity(Vector2D(v2fx, v2fy));
	}
}
