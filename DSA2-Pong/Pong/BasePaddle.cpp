#include "BasePaddle.h"

#include <Physics/AABB.h>

BasePaddle::BasePaddle(Point2 p, GLuint w, GLuint h)
	: GameObject(p, Colors::WHITE), width(w), height(h)
{
	name = "Paddle";

	bounds = new AABB(this, Vector2(width * 0.5f, height * 0.5f));
}

void BasePaddle::makeVerts()
{
	// create Vertices using extents of its AABB BoundingShape
	float extentX = width * 0.5f;
	float extentY = height * 0.5f;

	Point2* upLeft      = new Point2(-extentX, -extentY);
	Point2* upRight     = new Point2( extentX, -extentY);
	Point2* bottomRight = new Point2( extentX,  extentY);
	Point2* bottomLeft  = new Point2(-extentX,  extentY);

	vertices.push_back(upLeft);
	vertices.push_back(upRight);
	vertices.push_back(bottomRight);
	vertices.push_back(bottomLeft);
}

void BasePaddle::update(const GameTime& gameTime, GLuint topBound, GLuint bottomBound)
{
	GameObject::update(gameTime);

	// clamps the paddle to the screen's boundaries if it is going to mvoe out of it
	float halfHeight = height * 0.5f;
	if(position.y - halfHeight < topBound)
	{
		position.y = topBound + halfHeight;
	}
	else if(position.y + halfHeight > bottomBound)
	{
		position.y = bottomBound - halfHeight;
	}
}
