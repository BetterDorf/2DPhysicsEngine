#pragma once
#include "PhysicShape.h"
#include "Vector2D.h"

#include <vector>

class PolygonShape : public PhysicShape
{
public:
	PolygonShape();

	[[nodiscard]] ShapeType GetShapeType() const override { return ShapeType::Polygon; }
private:
	std::vector<Vector2D> points_;
};