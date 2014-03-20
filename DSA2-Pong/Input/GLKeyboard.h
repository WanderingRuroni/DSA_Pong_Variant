#ifndef GL_KEYBOARD_H
#define GL_KEYBOARD_H


#include "Keyboard.h"


/**
 * Gets input from a keyboard using GLUT callbacks.
 *
 * @author Peter B. Tummillo
 */
class GLKeyboard : public Keyboard
{

public:
	// constructor
	GLKeyboard();
	// destructor
	~GLKeyboard();
	
public:
	
	void getState(KeyboardState& keyboardState);

	void onPause();

	void handleKeyDownMessage(BYTE keyCode);
	void handleKeyUpMessage(BYTE keyCode);

private:

	void formatKeyCode(BYTE& keyCode);

}; // GLKeyboard


#endif // GL_KEYBOARD_H
