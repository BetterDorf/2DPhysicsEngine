#pragma once
#include "PhysicShape.h"

class CircleShape : public PhysicShape
{
public:
	CircleShape() : radius_(0.5) {}
	explicit CircleShape(const double radius) : radius_(radius) { }

	[[nodiscard]] ShapeType GetShapeType() const override { return ShapeType::Circle; }

	[[nodiscard]] double GetRadius() const { return radius_; }
	void SetRadius(const double newRadius) { radius_ = newRadius; }

private:
	double radius_ = 0.0;
};