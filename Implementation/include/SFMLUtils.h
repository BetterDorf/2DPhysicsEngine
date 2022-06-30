#pragma once
#include "Vector2D.h"
#include <SFML/Graphics.hpp>

namespace SFMLUtils
{
	constexpr double PIXELSTOMETERSRATIO = 50.0;
	constexpr double MAXTIMESTEP = 1.0 / 10.0;

	sf::Vector2f WorldToScreenPos(Vector2D worldPos, Vector2D cameraPos);
	Vector2D ScreenToWorldPos(sf::Vector2f screenPos, Vector2D cameraPos);

	sf::Vector2f vector2ToSFML(Vector2D);
	Vector2D sfVectorToVector2(sf::Vector2f);
}