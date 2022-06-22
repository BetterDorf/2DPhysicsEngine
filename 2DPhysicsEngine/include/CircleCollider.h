#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	explicit CircleCollider(const double radius) : radius_(radius) { }

	[[nodiscard]] ShapeType GetShapeType() const override { return ShapeType::Circle; }

	[[nodiscard]] double GetRadius() const { return radius_; }

private:
	double radius_ = 0.0;
};