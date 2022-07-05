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
	/// <summary>
	/// Calculate the cross product of two vectors
	/// </summary>
	/// <param name="a">first vector</param>
	/// <param name="b">second vector</param>
	/// <returns>Gives back the z value of the perpendicular vector</returns>
	static double CrossProduct(Vector2D a, Vector2D b);
	/// <summary>
	/// Calculate the vector that is the cross product between two vectors in the plane
	/// </summary>
	/// <param name="a">the z component of the perpendicular vector, other values are 0</param>
	/// <param name="b">the vector in the plane</param>
	/// <returns>a vector in the plane</returns>
	static Vector2D CrossProduct(double a, Vector2D b);
	/// <summary>
	/// Calculate the vector that is the cross product between a vector in the plane and a vector perpendicular to the plane
	/// </summary>
	/// <param name="a">the vector in the plane</param>
	/// <param name="b">the z component of the perpendicular vector, other values are 0</param>
	/// <returns>a vector in the plane</returns>
	static Vector2D CrossProduct(Vector2D a, double b);
	static Vector2D TripleProduct(Vector2D a, Vector2D b, Vector2D c);
	// Distance between two vectors (or rather, points represented by vectors)
	static double Distance(Vector2D, Vector2D);

	void Set(double x, double y);

	[[nodiscard]] double SqrtMagnitude() const;
	[[nodiscard]] double Magnitude() const;
	[[nodiscard]] Vector2D Normalize() const;

	[[nodiscard]] Vector2D GetPerpendicularVector(bool clockwise = true) const;

	[[nodiscard]] double AngleRadWith(Vector2D other) const;
	[[nodiscard]] double AngleDegWith(Vector2D other) const;
	[[nodiscard]] double AngleClockwiseWith(Vector2D other) const;
	[[nodiscard]] double AngleRadWithOAxis() const;
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
