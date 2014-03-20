#ifndef CIRCLE_H
#define CIRCLE_H


#include "BoundingShape.h"


class AABB;


class Circle : public BoundingShape
{

public:
	// constructor
	Circle(GameObject* go, float r);
	// destructor
	~Circle();

public:
	// getter function to return the circle's radius
	float getRadius() const;

public:
	// generice collision check to determine what type of BoundingShape you are colliding with
	bool checkBounding(BoundingShape* other);

	// Collisions checks that at slower movement speeds
	bool checkDiscrete(AABB* other);
	bool checkDiscrete(Circle* other);

	// Collision checks using ray casts to prevent objects tunneling through each other
	bool checkContinuous(AABB* other);
	bool checkContinuous(Circle* other);

	// Object draw function
	void draw();

private:
	
	float radius;

}; // Circle


#endif // CIRCLE_H
