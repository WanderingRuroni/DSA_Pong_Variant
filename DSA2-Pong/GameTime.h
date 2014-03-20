#ifndef GAMETIME_H
#define GAMETIME_H


#include <GL/freeglut.h>


/**
 * Structure that provides game time information.
 */
struct GameTime
{
	/**
	 * The change in time since the last frame (in seconds).
	 */
	GLfloat elapsedTime;

	/**
	 * The elapsed time since the game started, 
	 * not counting time spent paused (in seconds).
	 */
	GLfloat totalGameTime;
}; // GameTime


#endif // GAMETIME_H
