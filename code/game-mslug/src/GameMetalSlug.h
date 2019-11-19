////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameMetalSlug
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GameMetalSlug_h___
#define ___GameMetalSlug_h___
#include <mach/Game.h>
#include <gamelib/ScreenManager.h>

class GameMetalSlug : public Game
{
	ScreenManager smgr;
public:
	GameMetalSlug();
	~GameMetalSlug();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif
