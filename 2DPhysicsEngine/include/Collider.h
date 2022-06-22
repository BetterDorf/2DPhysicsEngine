#pragma once

class Collider
{
public:
	enum class ShapeType
	{
		None,
		Circle,
		Rectangle
	};

	[[nodiscard]] static bool CheckCollision(Collider*, Collider*);
	[[nodiscard]] virtual ShapeType GetShapeType() const = 0;
};