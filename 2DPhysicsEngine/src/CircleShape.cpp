#include "CircleShape.h"

Vector2D CircleShape::GetFurthestPoint(const Vector2D dir) const
{
	return dir.Normalize() * radius_;
}