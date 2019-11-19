////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AllOverScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AllOverScreen_h___
#define ___AllOverScreen_h___
#include <gamelib/Screen.h>

#include <gamelib/TimeClock.h>

class Font;

class AllOverScreen : public Screen
{
	enum STATE
	{
		STATE_IDLE,
		STATE_FADEOUT,
	};
	STATE		state;
	bool		removable;
	Font*		font;
	TimeClock	clock;
	int			fadeout;
public:
	AllOverScreen();
	~AllOverScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
