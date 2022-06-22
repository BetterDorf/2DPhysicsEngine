#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider() : radius_(1.0) {}
	explicit CircleCollider(const double radius) : radius_(radius) { }

	[[nodiscard]] ShapeType GetShapeType() const override { return ShapeType::Circle; }

	[[nodiscard]] double GetRadius() const { return radius_; }
	void SetRadius(const double newRadius) { radius_ = newRadius; }

private:
	double radius_ = 0.0;
};