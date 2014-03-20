#ifndef PLAYERPADDLE_H
#define PLAYERPADDLE_H


#include "BasePaddle.h"


class PlayerPaddle : public BasePaddle
{

public:
	// contructor
	PlayerPaddle(Point2 p, GLuint w, GLuint h);
	// destructor
	~PlayerPaddle();

public:
	// function to move the player's paddle
	void movePaddle(const Vector2& moveDir);

}; // PlayerPaddle


#endif // PLAYERPADDLE_H
