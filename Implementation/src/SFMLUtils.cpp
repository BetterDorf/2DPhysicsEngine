#include "SFMLUtils.h"

namespace SFMLUtils
{
	sf::Vector2f WorldToScreenPos(const Vector2D worldPos, const Vector2D cameraPos)
	{
		const Vector2D newPos = worldPos * PIXELSTOMETERSRATIO - cameraPos;

		return sf::Vector2f(static_cast<float>(newPos.X), static_cast<float>(- newPos.Y));
	}

	Vector2D ScreenToWorldPos(const sf::Vector2f screenPos, const Vector2D cameraPos)
	{
		const Vector2D newPos = Vector2D(static_cast<double>(screenPos.x),
			static_cast<double>(-screenPos.y)) / PIXELSTOMETERSRATIO + cameraPos;

		return newPos;
	}
}