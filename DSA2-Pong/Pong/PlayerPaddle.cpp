#include "PlayerPaddle.h"

PlayerPaddle::PlayerPaddle(Point2 p, GLuint w, GLuint h)
	: BasePaddle(p, w, h)
{
	friction = 0.5f;
	speed = 500.0f;
}

PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::movePaddle(const Vector2& moveDir)
{
	velocity = moveDir * speed;
}
