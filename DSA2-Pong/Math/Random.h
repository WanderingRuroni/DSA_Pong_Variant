#ifndef RANDOM_H
#define RANDOM_H


#include <Shared/Types.h>


/**
 * A pseudo-random number generator.
 *
 * Uses J. Bentley's subtractive random number generator implementation derived
 * from Knuth: http://rosettacode.org/wiki/Subtractive_generator.
 *
 * The formula for a subtractive random number generator is:
 *     rn = (r(n - I) - r (n - J)), (mod M); where I, J, and M are positive numbers
 *
 * @author Peter B. Tummillo
 */
class Random
{

public:

	Random();

	Random(UINT seed);

public:

	/**
	 * Fills a byte array with randomly generated numbers in the range
	 * [0, UCHAR_MAX).
	 *
	 * @param buffer Byte array.
	 * @param bufferSize Size of the byte array.
	 */
	void getBytes(BYTE* buffer, UINT bufferSize);

	/**
	 * Generates a random int in the range [0, INT_MAX).
	 *
	 * @return Integer from [0, INT_MAX).
	 */
	int getInt();

	/**
	 * Generates a random int in the range [0, max).
	 *
	 * @param max Maximum.
	 * @return Integer from [0, max).
	 */
	int getInt(int max);

	/**
	 * Generates a random int in the range [min, max).
	 *
	 * @param min Minimum.
	 * @param max Maximum.
	 * @return Integer from [min, max).
	 */
	int getInt(int min, int max);

	/**
	 * Generates a random float in the range [0.0, 1.0).
	 *
	 * @return Float from [0.0, 1.0).
	 */
	float getFloat();

	/**
	 * Generates a random float in the range [min, max).
	 *
	 * @param min Minimum.
	 * @param max Maximum.
	 * @return Float from [min, max).
	 */
	float getFloat(float min, float max);

protected:

	/**
	 * Sampler function that generates a random float in the range [0.0, 1.0).
	 *
	 * All Random functions use this sampler, so it can be used to change the
	 * generator derived classes are based on.
	 */
	virtual float sample();

private:

	void init();

protected:

	UINT _seed;

private:

	/**
	 * The state of this generator is determined by previously generated random
	 * numbers, stored in a circular buffer that only keeps the most recent.
	 */
	std::vector<UINT> _state;

}; // Random


#endif // RANDOM_H
