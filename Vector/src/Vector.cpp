#include <cmath>
#include "Vector.h"

#include <string>

float Vector::Magnitude() const
{
	return sqrt(X * X + Y * Y);
}

Vector Vector::Normalize() const
{
	return *this / this->Magnitude();
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

Vector Vector::operator*(const float scalar) const
{
	return Vector(this->X * scalar, this->Y * scalar);
}

Vector& Vector::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

Vector Vector::operator/(const float scalar) const
{
	return *this * (1 / scalar);
}

Vector& Vector::operator/=(const float scalar)
{
	*this = *this / scalar;
	return *this;
}