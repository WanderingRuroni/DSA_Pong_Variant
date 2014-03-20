#include "Ball.h"

#include <Physics/AABB.h>
#include <Physics/Circle.h>

namespace
{
	const GLuint NUM_SIDES = 20;

	const GLfloat SPEED_UP = 1.1f;
}

Ball::Ball(Point2 p, float r)
	: GameObject(p, Colors::WHITE), radius(r)
{
	name = "Ball";

	speed = 200.0f;

	maxSpeed = speed * SPEED_UP * 2.0f;

	bounds = new Circle(this, radius);
}

Ball::~Ball()
{
}

float Ball::getRadius()
{
	return radius;
}

void Ball::reset(const Point2& resetPos)
{
	// resets velocity to a static position
	velocity.x = 0.0f;
	velocity.y = 0.0f;

	// reduces speed to intial number
	speed = 200.0f;
	
	// places ball it is starting position
	position = resetPos;

	// bool indicator if it can be launched again
	isLaunched = false;
}

void Ball::launch(const Vector2& launchDir)
{
	if(!isLaunched)
	{
		velocity = launchDir * speed;
		
		isLaunched = true;
	}
}

#include <Physics/Ray.h>
#include "DebugDrawing.h"

void Ball::update(const GameTime& gameTime, GLuint topBound, GLuint bottomBound)
{
	GameObject::update(gameTime);

	// changes the type of collisions the ball will have based on its speed
	float spd = velocity.lengthSquared();
	if (bounds->collisionType == CT_Discrete)
	{
		if (spd >= 400.0f * 400.0f)
		{
			bounds->collisionType = CT_Continuous;
		}
	}
	else if (bounds->collisionType == CT_Continuous)
	{
		if (spd < 400.0f * 400.0f)
		{
			bounds->collisionType = CT_Discrete;
		}
	}

	// clamps balls position inside the screen's boundaries and reverses direction when it hits either bound
	if(position.y - radius < topBound)
	{
		position.y = radius;

		velocity.y *= -1.0f;
	}
	else if(position.y + radius > bottomBound)
	{
		position.y = bottomBound - radius;

		velocity.y *= -1.0f;
	}
}

void Ball::makeVerts()
{
	// create vertices based on an angle rotating a number of times based on the number of edges it has
	for (int side = 0; side < NUM_SIDES; ++side)
	{
		GLfloat angle = 2 * Math::PI * side / NUM_SIDES;

		Point2* vertex = new Point2(radius * cos(angle), radius * sin(angle));
		vertices.push_back(vertex);
	}
}

void Ball::onCollision(Circle* circle, const Collision& collision)
{
	// ray used for debugging
	Ray ray(collision.contact.point, collision.contact.normal * 1000.0f);

	// draw debug properties if activated
	DebugDrawing::getInstance().addRay(ray);

	// Resolve collision
	position = collision.contact.point + collision.contact.normal * circle->getRadius();

	// Reflect ball
	velocity.reflect(collision.contact.normal);

	// If this collision was with a paddle, add some of the paddle's
	// velocity to the ball
	if (collision.gameObject->getName() == "Paddle")
	{
		Vector2 addedVel = collision.gameObject->velocity;
		addedVel.y *= 0.5f;

		velocity += addedVel;
	}
}
