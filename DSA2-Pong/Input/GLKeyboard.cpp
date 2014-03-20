#include "GLKeyboard.h"

GLKeyboard::GLKeyboard()
{
}

GLKeyboard::~GLKeyboard()
{
}

void GLKeyboard::getState(KeyboardState& keyboardState)
{
	// Pass current keyboard state
	memcpy(&keyboardState, &_state, sizeof(BYTE) * NUM_KEYS);
}

void GLKeyboard::onPause()
{
	// Strip high-order bit from all keys (forces Key Up)
	for (UINT i = 0; i < NUM_KEYS; ++i)
	{
		_state.keys[i] &= ~(128);
	}
}

void GLKeyboard::handleKeyDownMessage(BYTE keyCode)
{
	formatKeyCode(keyCode);

	// Set high-order bit
	_state.keys[keyCode] |= 128;

	// Toggle last bit
	_state.keys[keyCode] ^= 1;
}

void GLKeyboard::handleKeyUpMessage(BYTE keyCode)
{
	formatKeyCode(keyCode);

	// Clear high-order bit
	_state.keys[keyCode] &= ~(128);
}

void GLKeyboard::formatKeyCode(BYTE& keyCode)
{
	// Convert lowercase keys to uppercase
	if (keyCode >= 97 && keyCode <= 122)
	{
		keyCode -= 32;
	}
}
