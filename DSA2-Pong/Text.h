#ifndef TEXT_H
#define TEXT_H


#include <Math/Point2.h>

#include <Shared/Types.h>

#include <GL/freeglut.h>

#include "ClippingPlanes.h"


/**
 * Helper for drawing text.
 *
 * @author Peter B. Tummillo  
 */
namespace Text
{

	/**
	 * Draws a 2D string at the specified position using OpenGL's current color.
	 *
	 * @param position 2D Position
	 * @param font Font type.
	 * @param string Text to draw.
	 */
	inline GLvoid draw2DString(ClippingPlanes planes, Point2 position, GLvoid* font, string text)
	{
		// Set a 2D projection with the origin at the top-left of the window
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(planes.left, planes.right, planes.bottom, planes.top);
		glMatrixMode(GL_MODELVIEW);
	
		glPushMatrix();
		glLoadIdentity();

		// Set the raster position of the string
		glRasterPos2f(position.x, position.y);

		// Put the string on the screen, character by chracter
		glutBitmapString(font, reinterpret_cast<const BYTE*>(text.c_str()));

		glPopMatrix();

		// Restore the previous projection
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

}; // Text


#endif // TEXT_H
