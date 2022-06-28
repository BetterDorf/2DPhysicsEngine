#include "Vector2D.h"

#include <cmath>
#include <string>
#include "MathUtils.h"

double Vector2D::DotProduct(const Vector2D a, const Vector2D b)
{
	return a.X * b.X + a.Y * b.Y;
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