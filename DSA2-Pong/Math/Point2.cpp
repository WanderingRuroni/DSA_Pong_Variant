#include "Point2.h"

#include "Vector2.h"

Point2& Point2::operator += (const Vector2& vec)
{
	x += vec.x; y += vec.y;
	return *this;
}

Point2& Point2::operator -= (const Vector2& vec)
{
	x -= vec.x; y -= vec.y;
	return *this;
}

Point2 Point2::operator + (const Vector2& vec) const
{
	return Point2(x + vec.x, y + vec.y);
}

Vector2 Point2::operator - (const Point2& point) const
{
	return Vector2(x - point.x, y - point.y);
}

Point2 Point2::operator - (const Vector2& vec) const
{
	return Point2(x - vec.x, y - vec.y);
}

float Point2::distanceTo(const Point2& p) const
{
	return sqrt( (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y) );
}

float Point2::distanceToSquared(const Point2& p) const
{
	return ( (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y) );
}

float Point2::distanceFromOrigin() const
{
	return sqrt(x * x + y * y);
}

float Point2::distanceFromOriginSquared() const
{
	return x * x + y * y;
}
