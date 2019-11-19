////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Mouse
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Mouse_h___
#define ___Mouse_h___

enum MouseButton
{
	MouseButton_Left,
	MouseButton_Right,
	MouseButton_Middle,
};

class Mouse
{
public:
	static int getX();
	static int getY();
	static bool isButtonDown(MouseButton button);
	static bool isButtonPressed(MouseButton button);
	static bool isButtonReleased(MouseButton button);
};

#endif
