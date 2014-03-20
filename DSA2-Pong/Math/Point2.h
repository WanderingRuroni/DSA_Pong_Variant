#ifndef POINT_2D_H
#define POINT_2D_H


#include "Math.h"


class Vector2;

/**
 * 2D Point implementation.
 *
 * @author Peter B. Tummillo
 */
class Point2
{

public:

	Point2() : x(0.0f), y(0.0f) {}
	
	Point2(const float* floatArr)
	{
		if(floatArr)
		{
			memcpy( arr, floatArr, sizeof(Point2) );
		}
	}

	Point2(float xVal, float yVal) : x(xVal), y(yVal) {}

public:

	// Accessor
	float operator [] (int n) const 
	{ 
		return arr[n];
	}

	// Casting

    operator float* () const
	{
		return (float*)arr;
	}

    operator const float* () const
	{
		return (const float*)arr;
	}

	// Compound Assignment

	Point2& operator += (const Vector2& vec);

	Point2& operator -= (const Vector2& vec);

	Point2& operator *= (float f) 
	{
		x *= f; y *= f;
		return *this;
	}

	Point2& operator /= (float f) 
	{
		float inv = 1 / f;
		x *= inv; y *= inv;
		return *this;
	}

	// Arithmetic

	Point2 operator + (const Vector2& vec) const;

	Vector2 operator - (const Point2& point) const;

	Point2 operator - (const Vector2& vec) const;

	Point2 operator * (float f) const
	{
		return Point2(x * f, y * f);
	}

	Point2 operator / (float f) const
	{
		float inv = 1 / f;
		return Point2(x * inv, y * inv);
	}

	friend Point2 operator * (float f, const Point2& point);

	// Comparison

	bool operator == (const Point2& point) const
	{
		return x == point.x && y == point.y;
	}

	bool operator != (const Point2& point) const
	{
		return x != point.x || y != point.y;
	}

	// Output

	friend std::ostream& operator << (std::ostream& os, const Point2& point);

	friend std::wostream& operator << (std::wostream& wos, const Point2& point);

public:

	float distanceTo(const Point2& point) const;

	float distanceToSquared(const Point2& point) const;

	float distanceFromOrigin() const;

	float distanceFromOriginSquared() const;

public:

	union
	{
		struct
		{
			float x, y;
		};
		float arr[2];
	};

}; // Point2


inline Point2 operator * (float f, const Point2& point) 
{
	return Point2(f * point.x, f * point.y);
}

inline std::ostream& operator << (std::ostream& os, const Point2& point) 
{
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}

inline std::wostream& operator << (std::wostream& wos, const Point2& point) 
{
	wos << "(" << point.x << ", " << point.y << ")";
	return wos;
}


#endif // POINT_2D_H
