////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameBattleCity
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GameBattleCity_h___
#define ___GameBattleCity_h___
#include <mach/Game.h>
#include <gamelib/ScreenManager.h>

class GameBattleCity : public Game
{
	ScreenManager smgr;
public:
	GameBattleCity();
	virtual ~GameBattleCity();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif
