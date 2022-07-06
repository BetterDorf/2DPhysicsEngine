#include "SFMLUtils.h"

namespace SFMLUtils
{
	sf::Vector2f WorldToScreenPos(const Vector2D worldPos, const Vector2D cameraPos)
	{
		const Vector2D newPos = (worldPos - cameraPos) * PIXELSTOMETERSRATIO;

		return sf::Vector2f(static_cast<float>(newPos.X), static_cast<float>(- newPos.Y));
	}

	Vector2D ScreenToWorldPos(const sf::Vector2f screenPos, const Vector2D cameraPos)
	{
		const Vector2D newPos = Vector2D(static_cast<double>(screenPos.x),
			static_cast<double>(-screenPos.y)) / PIXELSTOMETERSRATIO + cameraPos;

		return newPos;
	}

	sf::Vector2f vector2ToSFML(const Vector2D v)
	{
		return sf::Vector2f(static_cast<float>(v.X * PIXELSTOMETERSRATIO), static_cast<float>(v.Y * -PIXELSTOMETERSRATIO));
	}

	Vector2D sfVectorToVector2(const sf::Vector2f v)
	{
		return Vector2D(static_cast<double>(v.x), -static_cast<double>(v.y)) / PIXELSTOMETERSRATIO;
	}
}
