#ifndef AABB_H
#define AABB_H


#include "BoundingShape.h"

#include <Math/Vector2.h>


class Circle;


class AABB : public BoundingShape
{

public:
	// constructor
	AABB(GameObject* go, Vector2 e);
	//destructor
	~AABB();

public:
	// getter function for the extents of the AABB
	Vector2 getExtents() const;

public:
	// Handles a generic collision with another BoundingShape
	bool checkBounding(BoundingShape* other);

	// Collisions with a moving and stationary BoundingShapes
	bool checkDiscrete(AABB* other);
	bool checkDiscrete(Circle* other);

	// Collision checks with two moving BoundingShapes
	bool checkContinuous(AABB* other);
	bool checkContinuous(Circle* other);

	// Draws the Debug Lines around the BoundingShape
	void draw();

private:

	Vector2 extents;

}; // AABB


#endif // AABB_H
