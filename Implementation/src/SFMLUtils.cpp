#include "SFMLUtils.h"

namespace SFMLUtils
{
	sf::Vector2f WorldToScreenPos(const Vector worldPos, const Vector cameraPos)
	{
		const Vector newPos = worldPos * PIXELSTOMETERSRATIO - cameraPos;

		return sf::Vector2f(static_cast<float>(newPos.X), static_cast<float>(- newPos.Y));
	}

	Vector ScreenToWorldPos(const sf::Vector2f screenPos, const Vector cameraPos)
	{
		const Vector newPos = Vector(static_cast<double>(screenPos.x),
			static_cast<double>(- screenPos.y)) / PIXELSTOMETERSRATIO + cameraPos;

		return newPos;
	}
}