#pragma once

namespace mathUtils
{
	static double epsilon = 0.001;
	static double pi = 3.14159265358979323846264;

	bool isApproximatelyEqual(double a, double b);

	double radToDeg(double rad);
	double degToRad(double deg);
}