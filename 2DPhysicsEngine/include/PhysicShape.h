#pragma once
#include "Vector2D.h"

class PhysicShape
{
public:
	virtual ~PhysicShape() = default;

	enum class ShapeType
	{
		None,
		Circle,
		Polygon
	};

	[[nodiscard]] static bool CheckCollision(PhysicShape*, PhysicShape*);
	[[nodiscard]] virtual ShapeType GetShapeType() const = 0;

	[[nodiscard]] double GetBoundingCircleRad() const { return boundingCircleRadius_; }

	/// <summary>
	/// Computes the furthest point in a given direction
	/// </summary>
	/// <param name="dir">Direction from the center of the wanted point</param>
	/// <returns>The point furthest in the given direction</returns>
	[[nodiscard]] virtual Vector2D GetFurthestPoint(Vector2D dir) const = 0;

protected:
	double boundingCircleRadius_ = 0.0;
};