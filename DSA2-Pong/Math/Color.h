#ifndef COLOR_H
#define COLOR_H


#include "Math.h"


enum ColorComponent
{
	R, G, B, A
};

/**
 * Stores RBGA values for a color.
 *
 * @author Peter B. Tummillo
 */
class Color
{

public:
		
	Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}

	Color(const float* floatArr)
	{
		if(floatArr)
		{
			memcpy( arr, floatArr, sizeof(Color) );
		}
	}

	Color(float rVal, float gVal, float bVal, float aVal = 1.0f) : r(rVal), g(gVal), b(bVal), a(aVal) {}
	
	Color(UINT rVal, UINT gVal, UINT bVal, UINT aVal = 255) : r(rVal / 255.0f), g(gVal / 255.0f), b(bVal / 255.0f), a(aVal / 255.0f) {}

public:

	// Casting

	operator float* () const
	{
		return (float*)&r;
	}

    operator const float* () const
	{
		return (const float*)&r;
	}

	// Compound Assignment

	Color& operator += (const Color& c)
	{
		r += c.r; g += c.g; b += c.b; a += c.a;
		return *this;
	}

	Color& operator -= (const Color& c)
	{
		r -= c.r; g -= c.g; b -= c.b; a -= c.a;
		return *this;
	}

	Color& operator *= (float f) 
	{
		r *= f; g *= f; b *= f; a *= f;
		return *this;
	}

	Color& operator /= (float f) 
	{
		float inv = 1 / f;
		r *= inv; g *= inv; b *= inv; a *= inv;
		return *this;
	}

	Color& operator *= (const Color& c)
	{
		r *= c.r; g *= c.g; b *= c.b; a *= c.a;
		return *this;
	}

	// Arithmetic

	Color operator + (const Color& color) const
	{
		return Color(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	Color operator - (const Color& color)
	{
		return Color(r - color.r, g - color.g, b - color.b, a - color.a);
	}

	Color operator * (float f) const
	{
		return Color(r * f, g * f, b * f, a * f);
	}

	Color operator / (float f) const
	{
		float inv = 1 / f;
		return Color(r * inv, g * inv, b * inv, a * inv);
	}

	// Componentwise Multiplication
	
	Color operator * (const Color& color) const
	{
		return Color(r * color.r, g * color.g, b * color.b, a * color.a);
	}

	friend Color operator * (float f, const Color& c);

	// Comparison

	bool operator == (const Color& color) const
	{
		return r == color.r && g == color.g && b == color.b && a == color.a;
	}

	bool operator != (const Color& color) const
	{
		return r != color.r || g != color.g || b != color.b || a != color.a;
	}

	// Output
	
	friend std::ostream& operator << (std::ostream& os, const Color& c);
	
	friend std::wostream& operator << (std::wostream& wos, const Color& c);

public:

	template<ColorComponent c0>
	Color swizzle() const
	{
		return Color(arr[c0], arr[c0], arr[c0], arr[c0]);
	}

	template<ColorComponent c0, ColorComponent c1>
	Color swizzle() const
	{
		return Color(arr[c0], arr[c1], arr[c1], arr[c1]);
	}

	template<ColorComponent c0, ColorComponent c1, ColorComponent c2>
	Color swizzle() const
	{
		return Color(arr[c0], arr[c1], arr[c2], arr[c2]);
	}

	template<ColorComponent c0, ColorComponent c1, ColorComponent c2, ColorComponent c3>
	Color swizzle() const
	{
		return Color(arr[c0], arr[c1], arr[c2], arr[c3]);
	}

	void constrain();

	Color constrained() const;

	bool isCloseEnough(const Color& c, float range) const;

public:

	UINT getUnsignedR() const
	{
		return static_cast<UINT>(r * 255);
	}

	UINT getUnsignedG() const
	{
		return static_cast<UINT>(g * 255);
	}

	UINT getUnsignedB() const
	{
		return static_cast<UINT>(b * 255);
	}

	UINT getUnsignedA() const
	{
		return static_cast<UINT>(a * 255);
	}

public:

	static Color random();

public:

	union
	{
		struct  
		{
			float r, g, b, a;
		};
		float arr[4];
	};
	
}; // Color


inline Color operator * (float f, const Color& c)
{
	return Color(f * c.r, f * c.g, f * c.b, f * c.a);
}

inline std::ostream& operator << (std::ostream& os, const Color& c)
{
	os << "R: " << c.r << "\tG: " << c.g << "\tB: " << c.b << "\tA: " << c.a;
	return os;
}

inline std::wostream& operator << (std::wostream& wos, const Color& c)
{
	wos << "R: " << c.r << "\tG: " << c.g << "\tB: " << c.b << "\tA: " << c.a;
	return wos;
}


// Convenience Colors
namespace Colors
{

	const Color WHITE (1.0f, 1.0f, 1.0f);
	const Color BLACK (0.0f, 0.0f, 0.0f);

	const Color DARK_GRAY  (0.25f, 0.25f, 0.25f);
	const Color GRAY       ( 0.5f,  0.5f,  0.5f);
	const Color LIGHT_GRAY (0.75f, 0.75f, 0.75f);

	const Color RED   (1.0f, 0.0f, 0.0f);
	const Color GREEN (0.0f, 1.0f, 0.0f);
	const Color BLUE  (0.0f, 0.0f, 1.0f);

	const Color YELLOW  (1.0f, 1.0f, 0.0f);
	const Color MAGENTA (1.0f, 0.0f, 1.0f);
	const Color CYAN    (0.0f, 1.0f, 1.0f);

	const Color ORANGE (1.0f,  0.5f,  0.0f);
	const Color BROWN  (150u,   75u,    0u);

	const Color PURPLE (159u,    0u,  197u);
	const Color VIOLET (143u,    0u,  255u);
	
	const Color PINK   (238u,  130u,  238u);

	const Color MS_BLUE (0.3f, 0.584f, 0.93f);

}; // Colors


#endif // COLOR_H
