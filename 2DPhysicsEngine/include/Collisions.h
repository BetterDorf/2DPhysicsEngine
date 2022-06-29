#pragma once

#include "Rigibody.h"
#include "ConvexShape.h"

namespace Collisions
{
	struct ColData
	{
	public:
		explicit ColData(Rigibody* a, Rigibody* b) : A(a), B(b) {}

		Rigibody* A;
		Rigibody* B;
	};

	ColData MakeColData(Rigibody* rb1, Rigibody* rb2);

	bool CheckCollision(const Rigibody* rb1, const Rigibody* rb2);
	bool CheckCollisionCircle(const Rigibody* rb1, const Rigibody* rb2);

	bool CheckCollisionGJK(const Rigibody* rb1, const Rigibody* rb2);
	Vector2D GJKSupportFunction(const Rigibody* rb1, const Rigibody* rb2, Vector2D dir);
	/// <summary>
	/// Check if the given simplex contains the origin and transforms it according to the GJK algorithm
	///	Only works in the context of a simplex formed by GJK
	/// </summary>
	/// <param name="simplex">Simplex to check and modify</param>
	/// <param name="dir">Direction to update (will be the next pivot point direction)</param>
	/// <returns>Wether the origin is contained in the simplex</returns>
	bool GJKHandleSimplex(std::vector<Vector2D>& simplex, Vector2D& dir);

	void SolveOverlap(ColData);
	void SolveVelocities(ColData);

	
}