////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WinnerScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___WinnerScreen_h___
#define ___WinnerScreen_h___
#include <gamelib/Screen.h>
#include <src/AlphaFlicker.h>

class Font;
class Texture;

class WinnerScreen : public Screen
{
	bool			removable;
	Screen*			nextScreen;

	Font*			font1;
	Font*			font2;
	Texture*		texture;
	
	AlphaFlicker	alphaFlicker;
public:
	WinnerScreen();
	~WinnerScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};


#endif
