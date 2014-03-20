#ifndef BASEPADDLE_H
#define BASEPADDLE_H


#include "GameObject.h"


class BasePaddle : public GameObject
{

public:
	// constructor
	BasePaddle(Point2 p, GLuint width, GLuint height);
	// destructor
	virtual ~BasePaddle() = 0;

public:
	// update function to keep the paddle within bounds of the screen
	void update(const GameTime& gameTime, GLuint topBound, GLuint bottomBound);

protected:
	// create the vertices of the paddle object
	void makeVerts();

private:
	// variables of the paddle
	GLuint width;
	GLuint height;

}; // BasePaddle


inline BasePaddle::~BasePaddle() {}


#endif // BASEPADDLE_H
