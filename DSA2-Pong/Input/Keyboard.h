#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <Shared/Types.h>


#define NUM_KEYS 256
 

enum Keys
{
	KEY_ESC = 27,
	KEY_SPACE = 32,
	KEY_A = 65,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
};

/**
 * Encapsulates the state of a keyboard.
 */
struct KeyboardState
{

public:

	KeyboardState()
	{
		// Initialize keyboard buffer
		memset( &keys, 0, sizeof(BYTE) * NUM_KEYS );
	}

public:

	bool isKeyDown(BYTE keyCode) 
	{
		// True if high-order bit is set
		return (keys[keyCode] & 128) != 0;
	}

	bool isKeyUp(BYTE keyCode)   
	{ 
		// True if high-order bit is not set
		return (keys[keyCode] & 128) == 0; 
	}

	bool isKeyOn(BYTE keyCode)  
	{ 
		// True if low-order bit is set
		return (keys[keyCode] & 1) != 0; 
	}

	bool isKeyOff(BYTE keyCode) 
	{
		// True if low-order bit is not set
		return (keys[keyCode] & 1) == 0; 
	}

public:

	BYTE keys[NUM_KEYS];

}; // KeyboardState

/**
 * Interface for a keyboard.
 *
 * @author Peter B. Tummillo
 */
class Keyboard
{

public:
	
	Keyboard() {}

	~Keyboard() {}
	
public:
	
	virtual void getState(KeyboardState& keyboardState) = 0;

protected:

	KeyboardState _state;

}; // Keyboard


#endif // KEYBOARD_H
