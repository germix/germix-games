////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Game1943
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Game1943_h___
#define ___Game1943_h___
#include <mach/Game.h>
#include <gamelib/ScreenManager.h>

class Game1943 : public Game
{
	ScreenManager smgr;
public:
	Game1943();
	~Game1943();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif
