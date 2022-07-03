#include "MathUtils.h"
#include <cmath>

bool mathUtils::isApproximatelyEqual(const double a, const double b)
{
	return std::abs(a - b) <= mathUtils::epsilon;
}

double mathUtils::radToDeg(const double rad)
{
	return rad * 180 / pi;
}

double mathUtils::degToRad(const double deg)
{
	return deg / 180 * pi;
}

double mathUtils::signnum_c(const double x)
{
	if (x > 0.0) return 1.0;
	if (x < 0.0) return -1.0;
	return x;
}
