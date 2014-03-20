#include "GameTimer.h"

namespace
{
	const float MILLISECONDS_TO_SECONDS = 1.0f / 1000;
}

GameTimer::GameTimer()
{
	reset();
}

GameTimer::~GameTimer()
{
}

const GameTime& GameTimer::getGameTime()
{
	_gameTime.elapsedTime = getElapsedTime();
	_gameTime.totalGameTime = getTotalGameTime();
	return _gameTime;
}

GLfloat GameTimer::getElapsedTime() const
{
	return _deltaTime * MILLISECONDS_TO_SECONDS;
}

GLfloat GameTimer::getTotalGameTime() const 
{
	float gameTime = 0.0f;

	if (_isStopped)
	{
		gameTime = (_stopTime - _baseTime) * MILLISECONDS_TO_SECONDS;
	}
	else
	{
		gameTime = (_currTime - _pausedTime - _baseTime) * MILLISECONDS_TO_SECONDS;
	}

	return gameTime;
}

GLvoid GameTimer::reset()
{
	_currTime = glutGet(GLUT_ELAPSED_TIME);
	_lastTime = _currTime;
	_deltaTime = 0;

	_isStopped = false;
	_baseTime = _currTime;
	_stopTime = 0;
	_pausedTime = 0;
}

GLvoid GameTimer::start()
{
	if (_isStopped)
	{
		_currTime = glutGet(GLUT_ELAPSED_TIME);
			
		// Accumulate paused time
		_pausedTime += (_currTime - _stopTime);

		_lastTime = _currTime;
		_stopTime = 0;

		_isStopped = false;
	}
}

GLvoid GameTimer::stop()
{
	if (!_isStopped)
	{
		_currTime = glutGet(GLUT_ELAPSED_TIME);	
		_stopTime = _currTime;

		_isStopped = true;
	}
}

GLvoid GameTimer::tick()
{
	if (_isStopped)
	{
		// If the timer is stopped, dt = 0
		_deltaTime = 0;
	}
	else
	{
		// Update time
		_currTime = glutGet(GLUT_ELAPSED_TIME);
		_deltaTime = _currTime - _lastTime;
		_lastTime = _currTime;
	}
}
