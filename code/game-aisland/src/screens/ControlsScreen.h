////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ControlsScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ControlsScreen_h___
#define ___ControlsScreen_h___
#include <gamelib/Screen.h>

class Font;

class ControlsScreen : public Screen
{
	bool		removable;
	Font*		font1;
	Font*		font2;
public:
	ControlsScreen();
	virtual ~ControlsScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
