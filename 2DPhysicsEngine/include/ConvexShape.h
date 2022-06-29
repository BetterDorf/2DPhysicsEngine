#pragma once
#include "PhysicShape.h"
#include "Vector2D.h"

#include <vector>

class ConvexShape final : public PhysicShape
{
public:
	explicit ConvexShape(std::vector<Vector2D>);

	[[nodiscard]] ShapeType GetShapeType() const override { return ShapeType::Polygon; }

	[[nodiscard]] Vector2D GetFurthestPoint(Vector2D dir) const override;

	[[nodiscard]] std::vector<Vector2D> GetEdges(int pointId);
	[[nodiscard]] std::vector<Vector2D> GetEdges(Vector2D point);
	[[nodiscard]] int GetPointId(Vector2D point) const;

	void InsertPoint(Vector2D point, int id);
	void ConvertToConvex();

	[[nodiscard]] std::vector<Vector2D>& GetPoints() { return points_; }
private:
	std::vector<Vector2D> points_;

	void RepositionCenter();
};