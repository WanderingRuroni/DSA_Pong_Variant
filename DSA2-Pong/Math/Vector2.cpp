#include "Vector2.h"

float Vector2::length() const
{
	return sqrt(x * x + y * y);
}

float Vector2::lengthSquared() const
{
	return x * x + y * y;
}

void Vector2::normalize()
{
	float s = 1 / sqrt(x * x + y * y);
	x *= s; y *= s;
}

Vector2 Vector2::normalized() const
{
	float s = 1 / sqrt(x * x + y * y);
	return Vector2(x * s, y * s);
}

void Vector2::project(const Vector2& vec)
{
	*this = ( (*this * vec) / vec.lengthSquared() ) * vec;
}

Vector2 Vector2::projected(const Vector2& vec) const
{
	return ( (*this * vec) / vec.lengthSquared() ) * vec;
}

void Vector2::reflect(const Vector2& axis)
{
	Vector2 incident = *this;
	*this = incident - 2 * axis * (incident * axis);
}

Vector2 Vector2::reflected(const Vector2& axis) const
{
	Vector2 incident = *this;
	return incident - 2 * axis * (incident * axis);
}

bool Vector2::isParallelTo(const Vector2& vec) const
{
	if ( Math::fAbsEquals( ( ( *this * vec ) * ( *this * vec ) ) / ( lengthSquared() * vec.lengthSquared() ), 1.0f, 0.001f ) )
		return true;

	return false;
}

bool Vector2::isPerpendicularTo(const Vector2& vec) const
{
	if ( Math::fAbsEquals( ( ( *this * vec ) * ( *this * vec ) ) / ( lengthSquared() * vec.lengthSquared() ), 0.0f, 0.001f ) )
		return true;

	return false;
}

float Vector2::angleBetween(const Vector2& vec) const
{
	return atan2(*this ^ vec, *this * vec);
}

float Vector2::angleBetweenNormalized(const Vector2& vec) const
{
	return acos(*this * vec);
}
