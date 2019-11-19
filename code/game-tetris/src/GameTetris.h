////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameTetris
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GameTetris_h___
#define ___GameTetris_h___
#include <mach/Game.h>
#include <gamelib/ScreenManager.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224

class GameTetris : public Game
{
	ScreenManager smgr;
public:
	GameTetris();
	~GameTetris();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif