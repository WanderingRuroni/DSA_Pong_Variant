#ifndef AIPADDLE_H
#define AIPADDLE_H


#include "BasePaddle.h"


class AIPaddle : public BasePaddle
{

public:
	// constructor
	AIPaddle(Point2 p, GLuint w, GLuint h);
	// destructor
	~AIPaddle();

public:
	// update function to keep the ball inside the bounds of the screen and follow the ball
	void update(const GameTime& gameTime, GLuint topBound, GLuint bottomBound, const Point2& ballPos);

private:
	// AI code to determine its behavior
	void intelligence(const Point2& ballPos);

}; // AIPaddle


#endif // AIPADDLE_H
