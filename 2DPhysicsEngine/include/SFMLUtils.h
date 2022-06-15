#pragma once
#include "Vector.h"
#include <SFML/Graphics.hpp>

namespace SFMLUtils
{
	constexpr double PIXELSTOMETERSRATIO = 50.0;

	sf::Vector2f WorldToScreenPos(Vector worldPos, Vector cameraPos);
	Vector ScreenToWorldPos(sf::Vector2f screenPos, Vector cameraPos);
}