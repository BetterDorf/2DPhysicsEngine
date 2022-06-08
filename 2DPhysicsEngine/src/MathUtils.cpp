#include "MathUtils.h"
#include <cmath>

bool mathUtils::isApproximatelyEqual(const double a, const double b)
{
	return std::abs(a - b) <= mathUtils::epsilon;
}

double mathUtils::radToDeg(double rad)
{
	return rad * 180 / pi;
}

double mathUtils::degToRad(double deg)
{
	return deg / 180 * pi;
}