#pragma once
#include "PhysicShape.h"
#include "Vector2D.h"

#include <vector>

class PolygonShape final : public PhysicShape
{
public:
	explicit PolygonShape(std::vector<Vector2D>);

	[[nodiscard]] ShapeType GetShapeType() const override { return ShapeType::Polygon; }

	[[nodiscard]] Vector2D GetFurthestPoint(Vector2D dir) const override;
	void InsertPoint(Vector2D point, int id);

	[[nodiscard]] std::vector<Vector2D>& GetPoints() { return points_; }
private:
	std::vector<Vector2D> points_;

	void RepositionCenter();
};