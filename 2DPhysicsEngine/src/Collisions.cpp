#include "Collisions.h"

#include "CircleShape.h"
#include "MathUtils.h"
#include "PhysicsConstant.h"

namespace Collisions
{
	ColData CheckCollision(Rigibody* rb1, Rigibody* rb2)
	{
		ColData colData(rb1, rb2);

		//Bypass normal calculations if center are identical
		if (rb1->GetPos() == rb2->GetPos())
		{
			colData.HasCollided = true;
			colData.ColNormal = Vector2D(0.0, 1.0);
		}
		else if (rb1->GetCollider()->GetShapeType() == PhysicShape::ShapeType::Circle &&
			rb2->GetCollider()->GetShapeType() == PhysicShape::ShapeType::Circle)
		{
			CheckCollisionCircle(colData);
		}
		else
		{
			//Check the bounding circle of the two shapes
			if (CheckCollisionCircle(colData); colData.HasCollided)
			{
				CheckCollisionGJK(colData);
			}
		}

		return colData;
	}

	void CheckCollisionCircle(ColData& colData)
	{
		const Rigibody* rb1 = colData.A;
		const Rigibody* rb2 = colData.B;

		const double distanceBetweenCenters = (rb1->GetPos() - rb2->GetPos()).Magnitude();
		const double radiiLength = rb1->GetCollider()->GetBoundingCircleRad() + rb2->GetCollider()->GetBoundingCircleRad();

		if (distanceBetweenCenters <= radiiLength)
		{
			colData.HasCollided = true;

			//Add collision normal
			colData.ColNormal = (rb2->GetPos() - rb1->GetPos()).Normalize() * (radiiLength - distanceBetweenCenters + mathUtils::epsilon);
		}
		else
		{
			colData.HasCollided = false;
		}
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
				GJKGenerateCollisionNormal(simplex, colData);
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

	void GJKGenerateCollisionNormal(std::vector<Vector2D> polytope, ColData& data)
	{
		//We'll modify the simplex into a polytope in order to find the closest original edge from the origin
		if(!data.HasCollided)
			return;

		double minDistance = INFINITY;
		Vector2D minNormal;
		int minIndex = 0;

		static constexpr int MAXITER = 300;
		int iter = 0;
		while (minDistance >= INFINITY)
		{
			if (++iter > MAXITER)
			{
				data.ColNormal = Vector2D();
				return;
			}

			//Loop over every edge
			for (int p1 = 0; p1 < static_cast<int>(polytope.size()); p1++)
			{
				//Find the normal
				const int p2 = (p1 + 1) % static_cast<int>(polytope.size());
				Vector2D edge = polytope[p2] - polytope[p1];
				Vector2D normal = edge.GetPerpendicularVector().Normalize();

				//Distance to origin
				double normalDistance = Vector2D::DotProduct(normal, polytope[p1]);

				//Check that we took the correct normal vector and flip it if not
				if (normalDistance < 0.0)
				{
					normalDistance *= -1.0;
					normal *= -1.0;
				}

				//Use this distance if it's the best we found yet
				if (normalDistance < minDistance)
				{
					minDistance = normalDistance;
					minNormal = normal;
					minIndex = p2;
				}
			}

			//Get point in the direction of closest normal
			Vector2D support = GJKSupportFunction(data.A, data.B, minNormal);
			const double supportDistance = Vector2D::DotProduct(minNormal, support);

			//If there is a point that gives a different result, we didn't finish our search yet
			if (!mathUtils::isApproximatelyEqual(supportDistance, minDistance))
			{
				minDistance = INFINITY;
				//Add the suport point in between the two vertex
				polytope.insert(polytope.begin() + minIndex, support);
			}
		}

		//Add a small value to the distance so that the shapes are guaranteed not to be in each other when pushed out
		data.ColNormal = minNormal * (minDistance + mathUtils::epsilon);
	}

	void SolveOverlap(const ColData& data)
	{
		//Find proportions of displacement according to masses, the less mass they have, the more they move
		const double m1 = data.A->GetMass();
		const double m2 = data.B->GetMass();
		double prop1 = m2 / (m1 + m2);
		double prop2 = m1 / (m1 + m2);

		if (data.A->IsStatic())
		{
			if (data.B->IsStatic())
			{
				prop2 = 0.0;
				prop1 = 0.0;
			}
			else
			{
				prop1 = 0.0;
				prop2 = 1.0;
			}
		}
		else if (data.B->IsStatic())
		{
			prop2 = 0.0;
			prop1 = 1.0;
		}
		

		//Move shapes out of the other
		data.A->SetPos(data.A->GetPos() - data.ColNormal * prop1);
		data.B->SetPos(data.B->GetPos() + data.ColNormal * prop2);
	}

	void SolveVelocities(const ColData& data)
	{
		Rigibody* rb1 = data.A;
		Rigibody* rb2 = data.B;

		//handle static
		if (rb1->IsStatic() && rb2->IsStatic())
			return;

		if (rb1->IsStatic() || rb2->IsStatic())
		{
			Rigibody* nonStatic = !rb1->IsStatic() ? rb1 : rb2;

			const Vector2D v = nonStatic->GetVelocity();
			const Vector2D n = data.ColNormal.Normalize() * -1.0;
			Vector2D v1;
			const double k = 2.0 * Vector2D::DotProduct(v, n);
			v1.X = v.X - k * n.X;
			v1.Y = v.Y - k * n.Y;

			nonStatic->SetVelocity(v1);
			return;
		}

		const double v1 = rb1->GetVelocity().Magnitude();
		const double v2 = rb2->GetVelocity().Magnitude();

		const double m1 = rb1->GetMass();
		const double m2 = rb2->GetMass();

		const double theta1 = rb1->GetVelocity().AngleRadWithOAxis();
		const double theta2 = rb2->GetVelocity().AngleRadWithOAxis();

		const double phi = data.ColNormal.AngleRadWithOAxis();

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