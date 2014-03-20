#include "BoundingShape.h"

#include "AABB.h"
#include "Circle.h"
#include "CollisionHelpers.h"
#include "GameObject.h"

#include <cassert>

BoundingShape::BoundingShape(GameObject* go)
	: gameObject(go), collisionType(CT_Discrete)
{
}

BoundingShape::~BoundingShape()
{
}

GameObject* BoundingShape::getGameObject() const
{
	return gameObject;
}

Point2 BoundingShape::getCenter() const
{
	return gameObject->position;
}

// returns informatino based on the AABB being passed in for collision resolution
Collision BoundingShape::getCollisionData(AABB* other)
{
	Collision collision;

	collision.gameObject = other->getGameObject();
	collision.contact.point = CollisionHelpers::closestPointOnAABB(getCenter(), *other);
	collision.contact.normal = CollisionHelpers::normalToPointOnAABB(collision.contact.point, *other);

	return collision;
}

// returns informatino based on the Circle being passed in for collision resolution
Collision BoundingShape::getCollisionData(Circle* other)
{
	Collision collision;

	Point2 otherCenter = other->getCenter();

	collision.gameObject = other->getGameObject();
	collision.contact.normal = (getCenter() - otherCenter).normalized();
	collision.contact.point = otherCenter + collision.contact.normal * other->getRadius();

	return collision;
}
