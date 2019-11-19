////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GamePacman
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GamePacman_h___
#define ___GamePacman_h___
#include <mach/Game.h>
#include <gamelib/ScreenManager.h>

class GamePacman : public Game
{
	ScreenManager smgr;
public:
	GamePacman();
	~GamePacman();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif
