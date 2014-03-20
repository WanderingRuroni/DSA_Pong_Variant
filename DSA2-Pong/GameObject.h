#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "GameTime.h"

#include <Math/Color.h>
#include <Math/Point2.h>
#include <Math/Vector2.h>

#include <Physics/BoundingShape.h>

#include <vector>


class GameObject
{

public:
	// constructor
	GameObject(Point2 p, Color c);
	// destructor
	virtual ~GameObject();

public:
	// getter function for the name of the object
	std::string getName();

public:
	// initialize function
	void init();
	// intial collision function to determine type of BoundingShape used
	bool checkCollisions(const GameObject& other);

public:

	virtual void update(const GameTime& gameTime);
	virtual void draw();
	// resolves collisions againts AABB and Cirlce BoundingShapes
	virtual void onCollision(AABB* aabb, const Collision& collision) {}
	virtual void onCollision(Circle* circle, const Collision& collision) {}

protected:

	virtual void makeVerts() = 0;

public:
	
	Point2 position;
	Vector2 velocity;

	Color color;

protected:
	// object name
	std::string name;
	// Vector of vertices to hold BoundingShape vertices
	std::vector<Point2*> vertices;
	
	BoundingShape* bounds;
	
	float friction;
	float speed;

}; // GameObject


#endif // GAMEOBJECT_H
