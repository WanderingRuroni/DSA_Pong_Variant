#ifndef GAMETIMER_H
#define GAMETIMER_H


#include "GameTime.h"


/**
 * High-performance timer for game use.
 *
 * @author Peter B. Tummillo
 */
class GameTimer
{

public:

	GameTimer();

	~GameTimer();

public:

	const GameTime& getGameTime();

private:

	GLfloat getElapsedTime() const;

	GLfloat getTotalGameTime() const;

public:

	/**
	 * Resets the timer.
	 */
	GLvoid reset();
		
	/**
	 * Starts the timer.
	 */
	GLvoid start();
		
	/**
	 * Stops the timer.
	 */
	GLvoid stop();

	/**
	 * Updates the time.
	 */
	GLvoid tick();

private:

	GameTime _gameTime;

	// Time Tracking (in milliseconds)
	GLuint _currTime;
	GLuint _lastTime;
	GLuint _deltaTime;

	// Recording paused time
	GLboolean _isStopped;
	GLuint _baseTime;
	GLuint _stopTime;
	GLuint _pausedTime;

}; // GameTimer


#endif // GAMETIMER_H
