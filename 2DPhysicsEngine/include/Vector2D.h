#pragma once
#include <iostream>
#include <vector>

class Vector2D
{
public:
	Vector2D() = default;
	constexpr explicit Vector2D(const double x, const double y) : X(x), Y(y) {}

	double X = 0.0;
	double Y = 0.0;

	static double DotProduct(Vector2D, Vector2D);
	static double CrossProductMagnitude(Vector2D, Vector2D, Vector2D);
	// Distance between two vectors (or points represented by vectors)
	static double Distance(Vector2D, Vector2D);

	void Set(double x, double y);

	[[nodiscard]] double SqrtMagnitude() const;
	[[nodiscard]] double Magnitude() const;
	[[nodiscard]] Vector2D Normalize() const;

	[[nodiscard]] Vector2D GetPerpendicularVector(bool clockwise = true) const;

	[[nodiscard]] double AngleRadWith(Vector2D other) const;
	[[nodiscard]] double AngleDegWith(Vector2D other) const;
	[[nodiscard]] bool IsPerpendicular(Vector2D other) const;

	[[nodiscard]] std::string ToString() const;

	[[nodiscard]] Vector2D operator+(Vector2D other) const;
	Vector2D& operator+=(Vector2D other);

	[[nodiscard]] Vector2D operator-(Vector2D other) const;
	Vector2D& operator-=(Vector2D other);

	[[nodiscard]] Vector2D operator*(double scalar) const;
	Vector2D& operator*=(double scalar);

	[[nodiscard]] Vector2D operator/(double scalar) const;
	Vector2D& operator/=(double scalar);

	[[nodiscard]] bool operator==(const Vector2D&) const;
};
