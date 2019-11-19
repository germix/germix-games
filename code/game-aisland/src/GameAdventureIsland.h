////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameAdventureIsland
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GameAdventureIsland_h___
#define ___GameAdventureIsland_h___
#include <mach/Game.h>
#include <gamelib/ScreenManager.h>

class GameAdventureIsland : public Game
{
	ScreenManager smgr;
public:
	GameAdventureIsland();
	virtual ~GameAdventureIsland();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif
