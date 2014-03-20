#ifndef BOUNDINGSHAPE_H
#define BOUNDINGSHAPE_H


#include <Math/Point2.h>
#include <Math/Vector2.h>

// Macro calls to handle whether or not the collisions arer continuous or discrete
#define HANDLE_COLLISION(other)\
{\
	bool collision = false;\
\
	if (collisionType == CT_Discrete && other->collisionType == CT_Discrete)\
	{\
		collision = other->checkDiscrete(this);\
	}\
	else\
	{\
		collision = other->checkContinuous(this);\
	}\
\
	return collision;\
}

// send the appropriate collision data to the functions
#define SEND_COLLISION_EVENT(other)\
{\
	Collision thisCollision = other->getCollisionData(this);\
	Collision otherCollision = getCollisionData(other);\
\
	gameObject->onCollision(this, otherCollision);\
	other->getGameObject()->onCollision(other, thisCollision);\
}


class GameObject;

class AABB;
class Circle;


/**
 * CT_Discrete: For most objects.
 * CT_Continuous: For fast moving objects.
 */
enum CollisionType
{
	CT_Discrete,
	CT_Continuous,
};

// custom structs used in determining collisions
struct Contact
{
	Point2 point;
	Vector2 normal;
};

// Collision struct used in determining collision points
struct Collision
{
	GameObject* gameObject;
	Contact contact;
};

class BoundingShape
{

public:
	// constructor
	BoundingShape(GameObject* go);
	// destructor
	~BoundingShape();

public:
	// getter to return the GameObject associated with the BoundingShape
	GameObject* getGameObject() const;

	// getter for the BoundingShape's center
	Point2 getCenter() const;

public:

	Collision getCollisionData(AABB* other);
	Collision getCollisionData(Circle* other);

public:

	virtual bool checkBounding(BoundingShape* other) = 0;

	// Checks Collisions between moving and staionary BoundingShapes
	virtual bool checkDiscrete(AABB* other) = 0;
	virtual bool checkDiscrete(Circle* other) = 0;

	// Check Collisions between two moving BoundingShapes
	virtual bool checkContinuous(AABB* other) = 0;
	virtual bool checkContinuous(Circle* other) = 0;

	virtual void draw() = 0;

public:

	CollisionType collisionType;

protected:

	GameObject* gameObject;

}; // BoundingShape


#endif // BOUNDINGSHAPE_H
