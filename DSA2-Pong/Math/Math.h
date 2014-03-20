#ifndef MATH_H
#define MATH_H


#include <Shared/Types.h>

#include <cmath>
#include <cfloat>


/**
 * Holds common mathmatical constants and functions.
 *
 * @author Peter B. Tummillo
 */
namespace Math
{

	const float Infinity = FLT_MAX;

	const float PI         = 3.14159265358979323f;
	const float TWO_PI     = 2 * PI;
	const float QUARTER_PI = PI / 4;
	
	const float DEGTORAD = PI / 180.0f;
	const float RADTODEG = 180.0f / PI;

	/**
	 * Converts an angle from degrees to radians.
	 */
	inline float toRadians(float degrees)
	{
		return degrees * DEGTORAD;
	}

	/**
	 * Converts an angle from radians to degrees.
	 */
	inline float toDegrees(float radians)
	{
		return radians * RADTODEG;
	}

	/**
	 * Rounds a number to the specified number of places.
	 */
	inline float round(float num, UINT places)
	{
		float offset = pow( 10.0f, static_cast<int>(places) );
		return static_cast<int>(num * offset + 0.5f) / offset;
	}

	/**
	 * Returns the value clamped to [min,max].
	 */
	template<typename T>
	inline T clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : (value > max ? max : value);
	}


	/**
	 * Linearly intERPolates between two values.
	 * (Returns min when t = 0.0f and max when t = 1.0f.)    
	 */
	template<typename T>
	inline T lerp(const T& min, const T& max, float t)
	{
		return min + (max - min) * t;
	}

	/**
	 * Does an almost equal comparison of two floating point numbers,
	 * where maxUlps is how many representable floats can be accepted between a and b.
	 * 
	 * @source http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
	 */
	inline bool fEquals(float a, float b, int maxUlps) 
	{
		// Make sure maxUlps is non-negative and small enough that the
		// default NaN won't compare as equal to anything
		// TODO: Figure out what the fuck is up with this function
		//assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);

		// Make float a lexicographically ordered as a twos-complement int
		int aInt = *(int*)&a;
		if (aInt < 0)
			aInt = 0x80000000 - aInt;
    
		// Make float b lexicographically ordered as a twos-complement int
		int bInt = *(int*)&b;
		if (bInt < 0)
			bInt = 0x80000000 - bInt;

		// Do almost equal comparison
		return abs(aInt - bInt) <= maxUlps;
	}


	/**
	 * Does an almost equal comparison of two floating point numbers
	 * using absolute error (good for your average range of numbers).
	 */
	inline bool fAbsEquals(float a, float b, float maxAbsError)
	{
		// Check to save time
		if (a == b)
			return true;

		return fabs(a - b) < maxAbsError ? true : false;
	}


	/**
	 * Does an almost equal comparison of two floating point numbers
	 * using relative error (good for really small numbers & really big numbers).
	 */
	inline bool fRelEquals(float a, float b, float maxRelError)
	{
		// Check to save time
		if (a == b)
			return true;

		// Calculate relative error
		float relError;

		// Always divides by the larger number so the order of a & b doesn't matter
		if ( fabs(b) > fabs(a) )
			relError = fabs( (a - b) / b );
		else
			relError = fabs( (a - b) / a );
		
		return relError <= maxRelError ? true : false;
	}

}; // Math


#endif // MATH_H
