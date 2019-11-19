////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Mouse
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Mouse.h>
#include "mach.h"

int Mouse::getX()
{
	return mach.mouseX/mach.scale;
}
int Mouse::getY()
{
	return mach.mouseY/mach.scale;
}
bool Mouse::isButtonDown(MouseButton button)
{
	return mach.mouseButtons[button].down;
}
bool Mouse::isButtonPressed(MouseButton button)
{
	return mach.mouseButtons[button].pressed;
}
bool Mouse::isButtonReleased(MouseButton button)
{
	return mach.mouseButtons[button].released;
}
