#include "MathUtils.h"
#include <cmath>

bool mathUtils::isApproximatelyEqual(const float a, const float b)
{
	return std::abs(a - b) <= mathUtils::epsilon;
}

float mathUtils::radToDeg(const float rad)
{
	return rad * 180 / pi;
}

float mathUtils::degToRad(const float deg)
{
	return deg / 180 * pi;
}

float mathUtils::signnum_c(const float x)
{
	if (x > 0.0) return 1.0;
	if (x < 0.0) return -1.0;
	return x;
}
