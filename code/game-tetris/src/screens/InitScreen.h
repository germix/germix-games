////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InitScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___InitScreen_h___
#define ___InitScreen_h___
#include <gamelib/Screen.h>
#include <gamelib/TimeClock.h>

class Font;
class Texture;
class Music;

class InitScreen : public Screen
{
	Font*			font;
	Texture*		texture;
	bool			removable;
	Texture**		fireworks;
	int				fireworksIndex;
	int				fireworksFrame;
	int				fireworksState;
	TimeClock		fireworksClock;

	Music*			music;

	Screen*			nextScreen;
public:
	InitScreen();
	~InitScreen();
public:
	virtual Screen* getNext();
	virtual bool    isRemovable();
	virtual void    show(Machine* mach);
	virtual void    hide(Machine* mach);
	virtual void    update(Machine* mach, double dt);
	virtual void    render(Machine* mach, Graphics* gr);
};

#endif
