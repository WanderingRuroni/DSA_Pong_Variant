#ifndef VECTOR_2D_H
#define VECTOR_2D_H


#include "Math.h"


enum Vector2Component
{
	V2_X, V2_Y
};

/**
 * 2D Vector implementation.
 *
 * @author Peter B. Tummillo
 */
class Vector2 
{
	
public:
	
	Vector2() : x(0.0f), y(0.0f) {}
	
	Vector2(const float* floatArr)
	{
		if(floatArr)
		{
			memcpy( arr, floatArr, sizeof(Vector2) );
		}
	}
	
	Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}

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

	Vector2& operator += (const Vector2& vec) 
	{
		x += vec.x; y += vec.y;
		return *this;
	}

	Vector2& operator -= (const Vector2& vec)
	{
		x -= vec.x; y -= vec.y;
		return *this;
	}

	Vector2& operator *= (float f) 
	{
		x *= f; y *= f;
		return *this;
	}

	Vector2& operator /= (float f) 
	{
		float inv = 1 / f;
		x *= inv; y *= inv;
		return *this;
	}

	// Arithmetic

	Vector2 operator + (const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 operator - (const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2 operator * (float f) const
	{
		return Vector2(x * f, y * f);
	}

	Vector2 operator / (float f) const
	{
		float inv = 1 / f;
		return Vector2(x * inv, x * inv);
	}

	// Dot Product
	float operator * (const Vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	// 2D Cross Product (Perp-Dot Product)

	float operator ^ (const Vector2& vec) const
	{
		return x * vec.y - y * vec.x;
	}

	friend Vector2 operator * (float f, const Vector2& vec);

	// Comparison

	bool operator == (const Vector2& vec) const
	{
		return x == vec.x && y == vec.y;
	}

	bool operator != (const Vector2& vec) const
	{
		return x != vec.x || y != vec.y;
	}

	// Negation
	Vector2 operator - () const 
	{
		return Vector2(-x, -y);
	}

	// Output

	friend std::ostream& operator << (std::ostream& os, const Vector2& vec);

	friend std::wostream& operator << (std::wostream& wos, const Vector2& vec);
  
public:

	static const Vector2 zero()
	{
		return Vector2(0.0f, 0.0f);
	}

	template<Vector2Component c0>
	Vector2 swizzle() const
	{
		return Vector2(arr[c0], arr[c0]);
	}

	template<Vector2Component c0, Vector2Component c1>
	Vector2 swizzle() const
	{
		return Vector2(arr[c0], arr[c1]);
	}

	float length() const;

	float lengthSquared() const;

	void normalize();
	
	Vector2 normalized() const;

	void project(const Vector2& vec);

	Vector2 projected(const Vector2& vec) const;

	void reflect(const Vector2& axis);

	Vector2 reflected(const Vector2& axis) const;

	bool isParallelTo(const Vector2& vec) const;

	bool isPerpendicularTo(const Vector2& vec) const;

	float angleBetween(const Vector2& vec) const;

	float angleBetweenNormalized(const Vector2& vec) const;

	Vector2 right()
	{
		return Vector2(-y, x);
	}

	Vector2 left()
	{
		return Vector2(y, -x);
	}

public:

	union
	{
		struct
		{
			float x, y;
		};
		float arr[2];
	};

}; // Vector2


inline Vector2 operator * (float f, const Vector2& vec)
{
	return Vector2(f * vec.x, f * vec.y);
}

inline std::ostream& operator << (std::ostream& os, const Vector2& vec) 
{
	os << "(" << vec.x << ", " << vec.y << ")";
	return os;
}

inline std::wostream& operator << (std::wostream& wos, const Vector2& vec) 
{
	wos << "(" << vec.x << ", " << vec.y << ")";
	return wos;
}


#endif // VECTOR_2D_H
