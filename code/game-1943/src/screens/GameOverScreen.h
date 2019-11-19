////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameOverScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GameOverScreen_h___
#define ___GameOverScreen_h___
#include <gamelib/Screen.h>
#include <src/AlphaFlicker.h>

class Font;

class GameOverScreen : public Screen
{
	bool			removable;
	Screen*			nextScreen;

	Font*			font1;
	Font*			font2;
	
	AlphaFlicker	alphaFlicker;
public:
	GameOverScreen();
	~GameOverScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
