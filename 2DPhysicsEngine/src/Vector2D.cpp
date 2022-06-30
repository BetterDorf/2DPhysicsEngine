#include "Vector2D.h"
#include "MathUtils.h"

#include <cmath>
#include <string>

double Vector2D::DotProduct(const Vector2D a, const Vector2D b)
{
	return a.X * b.X + a.Y * b.Y;
}

double Vector2D::CrossProduct(const Vector2D a, const Vector2D b)
{
	return a.X * b.Y - a.Y * b.X;
}

Vector2D Vector2D::CrossProduct(const double a, const Vector2D b)
{
	return Vector2D(-a * b.Y, a * b.X);
}

Vector2D Vector2D::CrossProduct(const Vector2D a, const double b)
{
	return Vector2D(a.Y * b, - a.X * b);
}

Vector2D Vector2D::TripleProduct(const Vector2D a, const Vector2D b, const Vector2D c)
{
	return CrossProduct(CrossProduct(a, b), c);
}

double Vector2D::Distance(const Vector2D a, const Vector2D b)
{
	return (a - b).Magnitude();
}

void Vector2D::Set(const double x, const double y)
{
	X = x;
	Y = y;
}

double Vector2D::SqrtMagnitude() const
{
	return X * X + Y * Y;
}

double Vector2D::Magnitude() const
{
	return std::sqrt(SqrtMagnitude());
}

Vector2D Vector2D::Normalize() const
{
	return *this / this->Magnitude();
}

Vector2D Vector2D::GetPerpendicularVector(const bool clockwise) const
{
	Vector2D perpendicular;

	if (clockwise)
		perpendicular.Set(Y, -X);
	else
		perpendicular.Set(-Y, X);

	return perpendicular;
}

double Vector2D::AngleRadWith(const Vector2D other) const
{
	return std::acos(DotProduct(*this, other) / (Magnitude() * other.Magnitude()));
}

double Vector2D::AngleDegWith(const Vector2D other) const
{
	return mathUtils::radToDeg(AngleRadWith(other));
}

double Vector2D::AngleClockwiseWith(const Vector2D other) const
{
	const Vector2D v1 = *this;
	const Vector2D v2 = other;

	//dot product v1 and v2
	const double dot = DotProduct(v1, v2);
	//determinant
	const double det = v1.X * v2.Y - v1.Y * v2.X;

	const double angle =std::fmod(mathUtils::radToDeg(std::atan2(det, dot)) + 360.0, 360.0);

	return angle;
}

double Vector2D::AngleRadWithOAxis() const
{
	return std::atan2(Y, X);
}

bool Vector2D::IsPerpendicular(const Vector2D other) const
{
	return mathUtils::isApproximatelyEqual(DotProduct(*this, other), 0.0);
}

std::string Vector2D::ToString() const
{
	return "(" + std::to_string(X) + ";" + std::to_string(Y) + ")";
}

Vector2D Vector2D::operator+(const Vector2D other) const
{
	return Vector2D(this->X + other.X, this->Y + other.Y);
}

Vector2D& Vector2D::operator+=(const Vector2D other)
{
	*this = *this + other;
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D other) const
{
	return Vector2D(this->X - other.X, this->Y - other.Y);
}

Vector2D& Vector2D::operator-=(const Vector2D other)
{
	*this = *this - other;
	return *this;
}

Vector2D Vector2D::operator*(const double scalar) const
{
	return Vector2D(this->X * scalar, this->Y * scalar);
}

Vector2D& Vector2D::operator*=(const double scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector2D Vector2D::operator/(const double scalar) const
{
	return *this * (1.0 / scalar);
}

Vector2D& Vector2D::operator/=(const double scalar)
{
	*this = *this / scalar;
	return *this;
}

bool Vector2D::operator==(const Vector2D& other) const
{
	return mathUtils::isApproximatelyEqual(X, other.X) && mathUtils::isApproximatelyEqual(Y, other.Y);
}