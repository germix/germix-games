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
#include <gamelib/TimeClock.h>

class Music;
class Texture;

class GameOverScreen : public Screen
{
	enum STATE
	{
		STATE_FADING,
		STATE_NOTHING,
	};
	STATE				state;
	TimeClock			clock;
	bool				removable;
	Music*				music;
	bool				playingMusic;
	Texture*			background;
	
	int					fadingValue;
	TimeClock			fadingClock;
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
