#pragma once
#include <iostream>

class Vector
{
public:
	Vector() = default;
	Vector(const double x, const double y) : X(x), Y(y) {}

	double X = 0.0;
	double Y = 0.0;

	static double DotProduct(Vector, Vector);
	// Distance between two vectors (or points represented by vectors)
	static double Distance(Vector, Vector);

	void Set(double x, double y);

	[[nodiscard]] double SqrtMagnitude() const;
	[[nodiscard]] double Magnitude() const;
	[[nodiscard]] Vector Normalize() const;

	[[nodiscard]] Vector GetPerpendicularVector(bool clockwise) const;

	[[nodiscard]] double AngleRadWith(Vector other) const;
	[[nodiscard]] double AngleDegWith(Vector other) const;
	[[nodiscard]] bool IsPerpendicular(Vector other) const;

	[[nodiscard]] std::string ToString() const;

	[[nodiscard]] Vector operator+(Vector other) const;
	Vector& operator+=(Vector other);

	[[nodiscard]] Vector operator-(Vector other) const;
	Vector& operator-=(Vector other);

	[[nodiscard]] Vector operator*(double scalar) const;
	Vector& operator*=(double scalar);

	[[nodiscard]] Vector operator/(double scalar) const;
	Vector& operator/=(double scalar);

	Vector& operator = (Vector other);

	[[nodiscard]] bool operator==(const Vector&) const;
};
