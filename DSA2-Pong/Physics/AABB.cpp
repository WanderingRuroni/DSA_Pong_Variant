#include "AABB.h"

#include "Circle.h"
#include "CollisionHelpers.h"
#include "GameObject.h"

#include "DebugDrawing.h"

#include <cassert>

namespace
{
	const Color DEBUG_COLOR = Colors::RED;
};

AABB::AABB(GameObject* go, Vector2 e)
	: BoundingShape(go), extents(e)
{
}

AABB::~AABB()
{
}

Vector2 AABB::getExtents() const
{
	return extents;
}

// calls defined function from the BoundingShape.h
bool AABB::checkBounding(BoundingShape* other)
{
	HANDLE_COLLISION(other);
}

bool AABB::checkDiscrete(AABB* other)
{
	bool collision = false;

	// center points of both BoundingShapes
	Point2 center = getCenter();
	Point2 otherCenter = other->getCenter();

	// boolean check to determine if the two shapes are colliding
	collision = (center.x - otherCenter.x) < (extents.x + other->extents.x) ||
				(center.y - otherCenter.y) < (extents.y + other->extents.y);
	if (collision)
	{
		SEND_COLLISION_EVENT(other);
	}
	
	return collision;
}

bool AABB::checkDiscrete(Circle* other)
{
	bool collision = false;

	// center points of both BoundingShapes
	Point2 center = getCenter();
	Point2 otherCenter = other->getCenter();

	// radius of the Circle shape
	float otherRadius = other->getRadius();
	
	// Checks to see if distance between AABB and Circle 
	collision = CollisionHelpers::distanceToAABBSquared(otherCenter, *this) < otherRadius * otherRadius;
	if (collision)
	{
		SEND_COLLISION_EVENT(other);
	}

	return collision;
}

bool AABB::checkContinuous(AABB* other)
{
	return false;
}

bool AABB::checkContinuous(Circle* other)
{
	bool collision = false;

	GameObject* otherGo = other->getGameObject();

	// subtract Velocities to make the second object seem stationary for easier checks
	Vector2 relVel = otherGo->velocity - gameObject->velocity;
	// Ray used for ray casting
	Ray ray(getCenter(), relVel);

	float otherRadius = other->getRadius();

	// An expanded version of our AABB to determine if the passed in Bounding shape will hit at all
	AABB expandedBox(gameObject, Vector2(extents.x, extents.y + otherRadius));

	Point2 contactPoint;
	float t;

	// Looks to see if a ray intersects the AABB
	collision = CollisionHelpers::intersectRayAABB(contactPoint, t, ray, expandedBox);
	if (collision)
	{
		Collision thisCollision;
		thisCollision.gameObject = otherGo;
		thisCollision.contact.point = CollisionHelpers::closestPointOnAABB(contactPoint, *this);
		thisCollision.contact.normal = CollisionHelpers::normalToPointOnAABB(contactPoint, expandedBox);

		Collision otherCollision = getCollisionData(other);

		gameObject->onCollision(this, otherCollision);
		otherGo->onCollision(other, thisCollision);
	}

	return collision;
}

// Draw function used for debugging purposes
void AABB::draw()
{
	glPushMatrix();

	glColor4fv(DEBUG_COLOR);

	glLineWidth(3.0f);
	glLineStipple(1, std::numeric_limits<UINT16>::max());

	Point2 center = getCenter();
	glTranslatef(center.x, center.y, 0.0f);

	// creates vertices to draw the debug area
	glBegin(GL_LINE_LOOP);
		glVertex2f(-extents.x, -extents.y);
		glVertex2f( extents.x, -extents.y);
		glVertex2f( extents.x,  extents.y);
		glVertex2f(-extents.x,  extents.y);
	glEnd();

	glPopMatrix();
}
