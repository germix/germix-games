////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Keyboard
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Keyboard.h>
#include "mach.h"
#include <sdl/SDL_Scancode.h>

bool Keyboard::isDown(int k)
{
	return (mach.keyStatus[k].flags & KEY_FLAG_DOWN) != 0;
}
bool Keyboard::isPressed(int k)
{
	return (mach.keyStatus[k].flags & KEY_FLAG_PRESSED) != 0;
}
bool Keyboard::isReleased(int k)
{
	return (mach.keyStatus[k].flags & KEY_FLAG_RELEASED) != 0;
}
bool Keyboard::isRepeated(int k)
{
	return (mach.keyStatus[k].flags & KEY_FLAG_REPEATED) != 0;
}
