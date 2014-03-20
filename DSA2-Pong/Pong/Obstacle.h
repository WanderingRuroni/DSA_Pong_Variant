#ifndef OBSTACLE_H
#define OBSTACLE_H


#include "GameObject.h"


class Obstacle : public GameObject
{

public:
	// constructor
	Obstacle(Point2 p, GLuint ns, GLfloat r);
	// destructor
	~Obstacle();

public:
	// update function used in moving the obstacle when a particular score is reached during play
	void update(const GameTime& gameTime, GLfloat upperBound, GLfloat lowerBound, GLfloat s);

protected:
	// create vertices for the obstacle object
	void makeVerts();

private:

	GLuint numSides;
	GLfloat radius;

}; // Obstacle


#endif // OBSTACLE_H
