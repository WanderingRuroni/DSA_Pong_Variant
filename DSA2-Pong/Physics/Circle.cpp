#include "Circle.h"

#include "AABB.h"
#include "CollisionHelpers.h"
#include "GameObject.h"

#include "DebugDrawing.h"

namespace
{
	const Color DEBUG_COLOR = Colors::GREEN;

	const UINT DEBUG_SIDES = 40;
}

Circle::Circle(GameObject* go, float r)
	: BoundingShape(go), radius(r)
{
}

Circle::~Circle(void)
{
}

float Circle::getRadius() const
{
	return radius;
}

// returns a macro to the BoundingShape class
bool Circle::checkBounding(BoundingShape* other)
{
	HANDLE_COLLISION(other);
}
// checks collisions based on distance between each object colliding
bool Circle::checkDiscrete(AABB* other)
{
	bool collision = false;

	Point2 center = getCenter();
	Point2 otherCenter = other->getCenter();

	collision = CollisionHelpers::distanceToAABBSquared(center, *other) < radius * radius;
	if (collision)
	{
		SEND_COLLISION_EVENT(other);
	}

	return collision;
}
// check collisions based on distance of both circle's radii
bool Circle::checkDiscrete(Circle* other)
{
	bool collision = false;

	Point2 center = getCenter();
	Point2 otherCenter = other->getCenter();

	float sumRadii = radius + other->radius;
	collision = center.distanceToSquared(otherCenter) < sumRadii * sumRadii;
	if (collision)
	{
		SEND_COLLISION_EVENT(other);
	}

	return collision;
}

// Collisions cast a ray into the AABB to determine if it will hit and at what time step it will collide
bool Circle::checkContinuous(AABB* other)
{
	bool collision = false;

	GameObject* otherGo = other->getGameObject();

	// Subtract Velocities to make the AABB seem stationary in the check
	Vector2 relVel = gameObject->velocity - otherGo->velocity;
	// The ray to cast into the AABB
	Ray ray(getCenter(), relVel);

	Vector2 otherExtents = other->getExtents();
	// An expanded version of our AABB passed to see when it will possibly collide ahead of time
	AABB expandedBox(other->getGameObject(), Vector2(otherExtents.x, otherExtents.y + radius));

	Point2 contactPoint;
	float t;

	collision = CollisionHelpers::intersectRayAABB(contactPoint, t, ray, expandedBox);
	if (collision)
	{
		Collision thisCollision = other->getCollisionData(this);

		Collision otherCollision;
		otherCollision.gameObject = otherGo;
		otherCollision.contact.point = CollisionHelpers::closestPointOnAABB(contactPoint, *other);
		otherCollision.contact.normal = CollisionHelpers::normalToPointOnAABB(otherCollision.contact.point, *other);

		gameObject->onCollision(this, otherCollision);
		otherGo->onCollision(other, thisCollision);
	}

	return collision;
}

// Collisions cast a ray into the Circle to determine if it will hit and at what time step it will collide
bool Circle::checkContinuous(Circle* other)
{
	bool collision = false;

	GameObject* otherGo = other->getGameObject();

	// expand other circle by the radius of the current circle
	Circle expandedCircle(otherGo, (other->getRadius() + getRadius()));

	// Subtract movement of the other circle from both circles, making the second circle stationary
	Vector2 relVel = this->getGameObject()->velocity - otherGo->velocity;

	Point2 contactPt;
	float t;
	Ray ray(getCenter(), relVel);
	//Ray ray(getCenter(), gameObject->velocity);

	//DebugDrawing::getInstance().raysToDraw.push_back(ray);

	if(CollisionHelpers::intersectRayCircle(contactPt, t, ray, expandedCircle))
	{
		//Collision thisCollision = other->getCollisionData(this);
		Collision thisCollision;
		thisCollision.gameObject = gameObject;
		thisCollision.contact.normal = (other->getCenter() - contactPt).normalized();
		thisCollision.contact.point = getCenter() + thisCollision.contact.normal * getRadius();

		Collision otherCollision;
		otherCollision.gameObject = otherGo;
		otherCollision.contact.normal = (contactPt - other->getCenter()).normalized();
		otherCollision.contact.point = other->getCenter() + otherCollision.contact.normal * other->getRadius();

		gameObject->onCollision(this, otherCollision);
		otherGo->onCollision(other, thisCollision);
	}

	return false;
}

// Draw vertices of the BoundingShape for debugging purposes
void Circle::draw()
{
	glPushMatrix();

	glColor4fv(DEBUG_COLOR);

	glLineWidth(3.0f);
	glLineStipple(1, std::numeric_limits<UINT16>::max());

	Point2 center = getCenter();
	glTranslatef(center.x, center.y, 0.0f);

	glBegin(GL_LINE_LOOP);
		for (UINT side = 0; side < DEBUG_SIDES; ++side)
		{
			float angle = 2 * Math::PI * side / DEBUG_SIDES;

			Point2 vertex(radius * cos(angle), radius * sin(angle));
			glVertex2fv(vertex);
		}
	glEnd();

	glPopMatrix();
}
