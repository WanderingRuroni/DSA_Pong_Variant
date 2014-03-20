#include "GameObject.h"

#include "DebugDrawing.h"

namespace
{
	const float MIN_SPEED = sqrt(2.0f);
}

GameObject::GameObject(Point2 p, Color c)
	: position(p), color(c), bounds(nullptr), friction(1.0f), speed(0.0f)
{
}

GameObject::~GameObject()
{
	for(UINT i = 0; i < vertices.size(); ++i)
	{
		delete vertices[i];
	}

	if (bounds)
	{
		delete bounds;
	}
}

std::string GameObject::getName()
{
	return name;
}

void GameObject::init()
{
	makeVerts();
}

bool GameObject::checkCollisions(const GameObject& other)
{
	bool collision = false;
	
	if (bounds && other.bounds)
	{
		collision = bounds->checkBounding(other.bounds);
	}

	return collision;
}

void GameObject::draw() 
{
	UINT numVerts = vertices.size();
	if (numVerts > 0)
	{
		glPushMatrix();

		glColor4fv(color);

		glTranslatef(position.x, position.y, 0.0f);

		glBegin(GL_POLYGON);
			glVertex2fv(*vertices[0]);
			for( UINT i = 1; i < numVerts; i++)
			{
				glVertex2fv(*vertices[i]);
			}
			glVertex2fv(*vertices[0]);
		glEnd();

		glPopMatrix();
	}

	if (bounds)
	{
		if (DebugDrawing::getInstance().enabled)
		{
			bounds->draw();
		}
	}
}

void GameObject::update(const GameTime& gameTime)
{
	position += velocity * gameTime.elapsedTime;

	velocity *= friction;

	// Kill movement when it becomes too small to be
	// significant
	float speedSqr = velocity.lengthSquared();
	if (speedSqr != 0.0f)
	{
		if (Math::fAbsEquals(speedSqr, 0.0f, MIN_SPEED))
		{
			velocity.x = 0.0f;
			velocity.y = 0.0f;
		}
	}
}
