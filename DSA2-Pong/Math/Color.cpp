#include "Color.h"

#include "Random.h"

void Color::constrain()
{
	r = Math::clamp(r, 0.0f, 1.0f);
	g = Math::clamp(g, 0.0f, 1.0f);
	b = Math::clamp(b, 0.0f, 1.0f);
	a = Math::clamp(a, 0.0f, 1.0f);
}

Color Color::constrained() const
{
	return Color ( Math::clamp(r, 0.0f, 1.0f), Math::clamp(g, 0.0f, 1.0f), Math::clamp(b, 0.0f, 1.0f), Math::clamp(a, 0.0f, 1.0f) );
}

bool Color::isCloseEnough(const Color& c, float range) const
{
	// Sum components to get values
	float aVal = r + g + b + a;
	float bVal = c.r + c.g + c.b + c.a;

	return Math::fAbsEquals(aVal, bVal, range);
}

Color Color::random()
{
	Random random;

	UINT r = random.getInt(0, 256);
	UINT g = random.getInt(0, 256);
	UINT b = random.getInt(0, 256);

	return Color(r, g, b);
}
