#pragma once
#include "Vector2D.h"
#include <SFML/Graphics.hpp>

namespace SFMLUtils
{
	constexpr double PIXELSTOMETERSRATIO = 50.0;

	sf::Vector2f WorldToScreenPos(Vector2D worldPos, Vector2D cameraPos);
	Vector2D ScreenToWorldPos(sf::Vector2f screenPos, Vector2D cameraPos);
}