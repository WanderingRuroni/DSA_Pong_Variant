#include "AIPaddle.h"

AIPaddle::AIPaddle(Point2 p, GLuint w, GLuint h)
	: BasePaddle(p, w, h)
{
	// no friction needed for the AI
	friction = 0.5f;
	speed = 20.0f / (800 * 2.1f);
}

AIPaddle::~AIPaddle()
{
}

void AIPaddle::update(const GameTime& gameTime, GLuint topBound, GLuint bottomBound, const Point2& ballPos)
{
	BasePaddle::update(gameTime, topBound, bottomBound);

	intelligence(ballPos);
}

void AIPaddle::intelligence(const Point2& ballPos)
{
	// Calculate reaction speed using the ball's x position
	// (when the ball is closer, the AI will react faster)
	float reactionSpeed = ballPos.x * speed;
	
	if(ballPos.x <= 400.0f)
	{
		reactionSpeed *= 0.8f;
	}
	else
		reactionSpeed *= 1.1f;

	// Move towards the ball
	velocity = Vector2(0.0f, (ballPos.y - position.y) * reactionSpeed);
}
