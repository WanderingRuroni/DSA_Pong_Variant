#ifndef BALL_H
#define BALL_H


#include "GameObject.h"


class Ball : public GameObject
{

public:
	// constructor
	Ball(Point2 p, float r);
	// destructor
	~Ball();

public:
	// getter function for the ball's radius
	float getRadius();
	
public:
	// resets the ball to its inital position
	void reset(const Point2& resetPos);
	// shoots the ball in a random direction to either the AI or the player
	void launch(const Vector2& launchDir);
	// update function to keep the ball within the boundaries of the screen
	void update(const GameTime& gameTime, GLuint topBound, GLuint bottomBound);

protected:
	// create the ball object's vertices
	void makeVerts();
	// determines whether the ball collided with and applies proper reflection and speed
	void onCollision(Circle* circle, const Collision& collision);

private:

	GLfloat maxSpeed;

	GLfloat radius;

	GLboolean isLaunched;

}; // Ball


#endif // BALL_H
