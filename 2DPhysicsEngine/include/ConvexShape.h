#pragma once
#include "PhysicShape.h"
#include "Vector2D.h"

#include <vector>

class ConvexShape final : public PhysicShape
{
public:
	explicit ConvexShape(std::vector<Vector2D>);

	[[nodiscard]] ShapeType GetShapeType() const override { return ShapeType::Convex; }

	/// <summary>
	/// Find the point that is the furthest from the center in a given direction.
	///	That is to say, the point that maximizes the dot product with the given direction.
	/// </summary>
	///	<param name="dir">Direction from the center that the point must be in</param>
	///	<returns>Furthest point in the given direction</returns>
	[[nodiscard]] Vector2D GetFurthestPoint(Vector2D dir) const override;

	[[nodiscard]] int GetPointId(Vector2D point) const;

	void InsertPoint(Vector2D point, int id);
	/// <summary>
	/// Remove from the points vector all points that would make the shape concave.
	/// Equivalent to drawing the shape only with the outer edges
	/// </summary>
	void ConvertToConvex();

	[[nodiscard]] std::vector<Vector2D>& GetPoints() { return points_; }
private:
	std::vector<Vector2D> points_;

	/// <summary>
	/// Move all points so that the center of gravity is at the local origin (0, 0)
	///	Also recalculates the boundingCircleRadius
	/// </summary>
	void RepositionCenter();
};