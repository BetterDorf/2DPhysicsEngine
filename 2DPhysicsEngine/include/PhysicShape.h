#pragma once

class PhysicShape
{
public:
	enum class ShapeType
	{
		None,
		Circle,
		Polygon
	};

	[[nodiscard]] static bool CheckCollision(PhysicShape*, PhysicShape*);
	[[nodiscard]] virtual ShapeType GetShapeType() const = 0;
};