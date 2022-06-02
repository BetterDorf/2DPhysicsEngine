#pragma once
#include <iostream>

class Vector
{
public:
	float X;
	float Y;

	Vector(const float x, const float y) : X(x), Y(y) {}

	[[nodiscard]] float SqrtMagnitude() const;
	[[nodiscard]] float Magnitude() const;
	[[nodiscard]] Vector Normalize() const;

	[[nodiscard]] std::string ToString() const;

	[[nodiscard]] Vector operator+(Vector other) const;
	Vector& operator+=(Vector other);

	[[nodiscard]] Vector operator-(Vector other) const;
	Vector& operator-=(Vector other);

	[[nodiscard]] Vector operator*(float scalar) const;
	Vector& operator*=(float scalar);

	[[nodiscard]] Vector operator/(float scalar) const;
	Vector& operator/=(float scalar);
};
