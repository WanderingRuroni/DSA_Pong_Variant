#include "Random.h"

#include <cstdlib>
#include <limits>

#include <ctime>
#include <cassert>

namespace
{
	/**
	 * Capacity of this generator's state buffer.
	 */
	const UINT STATE_CAPACITY = 55;

	/**
	 * This generator will calculate 219 random numbers on initialization
	 * because starting at r220 avoids initial generator bias.
	 */
    const UINT INITIAL_LOAD = 219;

	/**
	 * Parameters I and J affect the period of this generator.
	 */
	const UINT I = 55;
	const UINT J = 24;
    
	/**
	 * M is the largest random number this generator can generate.
	 */
	const UINT M = static_cast<UINT>(1e9);
};


Random::Random()
	: _seed(static_cast<UINT>(time(NULL))), _state(STATE_CAPACITY)
{
	init();
}

Random::Random(UINT seed)
	: _seed(seed), _state(STATE_CAPACITY)
{
	init();
}

void Random::getBytes(BYTE* buffer, UINT bufferSize)
{
	for (UINT i = 0; i < bufferSize; ++i)
	{
		buffer[i] = getInt(std::numeric_limits<BYTE>::max());
	}
}

int Random::getInt()
{
	return getInt(std::numeric_limits<int>::max());
}

int Random::getInt(int max)
{
	return static_cast<int>(max * getFloat());
}

int Random::getInt(int min, int max)
{
	return min + getInt(max - min);
}

float Random::getFloat()
{
	return sample();
}

float Random::getFloat(float min, float max)
{
	return min + getFloat() * (max - min);
}

float Random::sample()
{
	static UINT stateI = I;
	static UINT stateJ = J;
 
	if (stateI-- == 0)
	{
		stateI = STATE_CAPACITY - 1;
	}
	if (stateJ-- == 0)
	{
		stateJ = STATE_CAPACITY - 1;
	}

	int newState = _state[stateI] - _state[stateJ];
	if (newState < 0)
	{
		newState += M;
	}
	_state[stateI] = newState;
 
	return static_cast<float>(newState) / M;
}

void Random::init()
{
	assert(I != J);

	// 1. Start with a single seed in the range [0, M).
	assert(_seed >= 0);
	while (_seed >= M)
	{
		_seed -= M;
	}
	
	// 2. Set s0 = seed and s1 = 1 (setting s1 = 1 avoids bad states).
	_state[0] = _seed % M;
	int s1 = 1;

	// 3. Compute s2 - s54 using the subtractive formula:
	//        sn = s(n - 2) - s(n - 1), (mod M)
	//
	// 4. Reorder state so sn = r((34 * n) - 1, mod STATE_CAPACITY)
	for (int i = 1, j = 21, p2 = s1; i < STATE_CAPACITY; ++i, j += 21) 
	{
		if (j >= STATE_CAPACITY)
		{
			j -= STATE_CAPACITY;
		}

		_state[j] = p2;
		
		p2 = _seed - p2;
		if (p2 < 0)
		{
			p2 += M;
		}
		
		_seed = _state[j];
	}
	
	// 5. Compute the next 165 values, r55 - r219, storing only the last 55.
	for (int i = STATE_CAPACITY; i <= INITIAL_LOAD; ++i)
	{
		sample();
	}
}
