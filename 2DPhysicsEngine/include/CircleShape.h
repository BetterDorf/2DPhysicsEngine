#pragma once
#include "PhysicShape.h"

class CircleShape final : public PhysicShape
{
public:
	explicit CircleShape(const float radius) : radius_(radius) { boundingCircleRadius_ = radius_; }
	CircleShape() : CircleShape(0.5) {}

	[[nodiscard]] ShapeType GetShapeType() const override { return ShapeType::Circle; }

	[[nodiscard]] Vector2D GetFurthestPoint(Vector2D dir) const override;

	[[nodiscard]] float GetRadius() const { return radius_; }
	void SetRadius(const float newRadius) { radius_ = newRadius; }

private:
	float radius_ = 0.0;
};