#include "Vector.h"

#include <cmath>
#include <string>
#include "MathUtils.h"

double Vector::DotProduct(const Vector a, const Vector b)
{
	return a.X * b.X + a.Y * b.Y;
}

double Vector::Distance(const Vector a, const Vector b)
{
	return (a - b).Magnitude();
}

void Vector::Set(const double x, const double y)
{
	X = x;
	Y = y;
}

double Vector::SqrtMagnitude() const
{
	return X * X + Y * Y;
}

double Vector::Magnitude() const
{
	return std::sqrt(SqrtMagnitude());
}

Vector Vector::Normalize() const
{
	return *this / this->Magnitude();
}

Vector Vector::GetPerpendicularVector(const bool clockwise) const
{
	Vector perpendicular;

	if (clockwise)
		perpendicular.Set(Y, -X);
	else
		perpendicular.Set(-Y, X);

	return perpendicular;
}

double Vector::AngleRadWith(const Vector other) const
{
	return std::acos(DotProduct(*this, other) / (Magnitude() * other.Magnitude()));
}

double Vector::AngleDegWith(const Vector other) const
{
	return mathUtils::radToDeg(AngleRadWith(other));
}

bool Vector::IsPerpendicular(const Vector other) const
{
	return mathUtils::isApproximatelyEqual(DotProduct(*this, other), 0.0);
}

std::string Vector::ToString() const
{
	return "(" + std::to_string(X) + ";" + std::to_string(Y) + ")";
}

Vector Vector::operator+(const Vector other) const
{
	return Vector(this->X + other.X, this->Y + other.Y);
}

Vector& Vector::operator+=(const Vector other)
{
	*this = *this + other;
	return *this;
}

Vector Vector::operator-(const Vector other) const
{
	return Vector(this->X - other.X, this->Y - other.Y);
}

Vector& Vector::operator-=(const Vector other)
{
	*this = *this - other;
	return *this;
}

Vector Vector::operator*(const double scalar) const
{
	return Vector(this->X * scalar, this->Y * scalar);
}

Vector& Vector::operator*=(const double scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector Vector::operator/(const double scalar) const
{
	return *this * (1.0 / scalar);
}

Vector& Vector::operator/=(const double scalar)
{
	*this = *this / scalar;
	return *this;
}

bool Vector::operator==(const Vector& other) const
{
	return mathUtils::isApproximatelyEqual(X, other.X) && mathUtils::isApproximatelyEqual(Y, other.Y);
}