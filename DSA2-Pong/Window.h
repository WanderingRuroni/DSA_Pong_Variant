#ifndef WINDOW_H
#define WINDOW_H


#include <GL/freeglut.h>

// easily accessible window struct
struct Window
{
	GLuint width;
	GLuint height;
	GLuint centerX;
	GLuint centerY;
};


#endif // WINDOW_H
