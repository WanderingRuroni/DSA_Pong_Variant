#ifndef RAY_H
#define RAY_H


#include <GL/freeglut.h>

#include <Math/Point2.h>
#include <Math/Vector2.h>

#include "GameTime.h"

// ray struct used in collision detection and debug drawing
struct Ray
{

	Ray() {}

	Ray(Point2 myOrigin, Vector2 myDirection)
		: origin(myOrigin), direction(myDirection)
	{
	}

	// returns the far extent of the ray
	Point2 getPoint(float t) const
	{
		return origin + direction * t;
	}

	// draw function to see the ray
	void draw(const GameTime& gameTime)
	{
		glBegin(GL_LINES);
			glVertex2fv(origin);
			glVertex2fv(origin + direction * gameTime.elapsedTime);
		glEnd();
	}

	// Output
	friend std::ostream& operator << (std::ostream& os, const Ray& ray);
	friend std::wostream& operator << (std::wostream& wos, const Ray& ray);

	Point2 origin;
	Vector2 direction;

}; // Ray


inline std::ostream& operator << (std::ostream& os, const Ray& ray) 
{
	os << ray.origin << ", " << ray.direction;
	return os;
}

inline std::wostream& operator << (std::wostream& wos, const Ray& ray) 
{
	wos << ray.origin << ", " << ray.direction;
	return wos;
}


#endif // RAY_H
