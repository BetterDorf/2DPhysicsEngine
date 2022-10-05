#pragma once

namespace mathUtils
{
	static float epsilon = 0.001;
	static float pi = 3.14159265358979323846264;

	bool isApproximatelyEqual(float a, float b);

	float radToDeg(float rad);
	float degToRad(float deg);

	float signnum_c(float x);
}