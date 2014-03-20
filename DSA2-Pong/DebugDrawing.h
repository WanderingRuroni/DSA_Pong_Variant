#ifndef DEBUG_DRAWING_H
#define DEBUG_DRAWING_H


#include <Physics/Ray.h>
#include "GameTime.h"

#include <algorithm>

// Singleton Debug Drawing class to be used across necessary GameObjects for debug purposes

struct RayInfo
{
	RayInfo() {}

	Ray ray;
	GLuint lifeTime;
};


class DebugDrawing
{

private:

	DebugDrawing() : enabled(false) {}

	~DebugDrawing() {}

public:

	static DebugDrawing& getInstance()
	{
		static DebugDrawing instance;

		return instance;
	}

public:
	// adds RayInfo into a vector of RayInfo's
	void addRay(Ray ray)
	{
		if (enabled)
		{
			RayInfo* rayInfo = new RayInfo();
			rayInfo->ray = ray;
			rayInfo->lifeTime = 30;

			raysToDraw.push_back(rayInfo);
		}
	}

	void draw(const GameTime& gameTime)
	{
		// Draws the ray over a small amount of time that decays after intially drawing
		if (enabled)
		{
			for (UINT i = 0; i < raysToDraw.size(); ++i)
			{
				RayInfo* rayInfo = raysToDraw[i];

				rayInfo->ray.draw(gameTime);
				--(rayInfo->lifeTime);

				if (rayInfo->lifeTime == 0)
				{
					std::vector<RayInfo*>::iterator it = std::find(raysToDraw.begin(), raysToDraw.end(), rayInfo);
					if (it != raysToDraw.end())
					{
						delete rayInfo;
						raysToDraw.erase(it);
					}
				}
			}
		}
	}

public:

	bool enabled;

private:

	std::vector<RayInfo*> raysToDraw;

};


#endif // DEBUG_DRAWING_H
