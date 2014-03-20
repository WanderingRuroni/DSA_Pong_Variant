#include "Obstacle.h"
#include <Physics/Circle.h>


Obstacle::Obstacle(Point2 p, GLuint ns, GLfloat r)
	: GameObject(p, Color::random()), numSides(ns), radius(r)
{
	name = "Obstacle";

	bounds = new Circle(this, radius);
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(const GameTime& gameTime, GLfloat upperBound, GLfloat lowerBound, GLfloat s)
{
	GameObject::update(gameTime);
	// reverses movement if it reaches its height bounds
	if (position.y <= upperBound)
	{
		position.y = upperBound;

		velocity = Vector2(0.0f, 1.0f) * s;
	}
	else if (position.y >= lowerBound)
	{
		position.y = lowerBound;

		velocity = Vector2(0.0f, -1.0f) * s;
	}
}

void Obstacle::makeVerts()
{
	// creates vertices based on an angle moved by the number of sides the obstacle ahs
	for(GLuint side = 0; side < numSides; ++side)
	{
		GLfloat angle = 2 * Math::PI * side / numSides;

		Point2* vertex = new Point2(radius * cos(angle), radius * sin(angle));
		vertices.push_back(vertex);
	}
}
