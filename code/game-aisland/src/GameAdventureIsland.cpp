////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameAdventureIsland
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/GameAdventureIsland.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <mach/Machine.h>

#include <src/HeroInfo.h>
#include <src/screens/WinnerScreen.h>
#include <src/screens/ControlsScreen.h>
#include <src/screens/GameOverScreen.h>
#include <src/screens/RoundBonusScreen.h>
#include <src/screens/InitGameScreen.h>
#include <src/screens/InitRoundScreen.h>
#include <src/screens/PlaySceneScreen.h>
#include <src/screens/AdventureScreen.h>

GameAdventureIsland::GameAdventureIsland()
{
}
GameAdventureIsland::~GameAdventureIsland()
{
}
void GameAdventureIsland::init(Machine* mach)
{
	res.load("aisland/resources.xres");
	static HeroInfo i;
	i.pot = true;
	smgr.init(mach, new InitGameScreen());
//	smgr.init(mach, new InitRoundScreen(1,1,&i));
//	smgr.init(mach, new RoundBonusScreen(&i));
//	smgr.init(mach, new WinnerScreen());
//	smgr.init(mach, new ControlsScreen());
//	smgr.init(mach, new GameOverScreen(1,1,12345));
//	smgr.init(mach, new PlaySceneScreen(1,1));

//	smgr.init(mach, new AdventureScreen());
}
void GameAdventureIsland::close(Machine* mach)
{
}
void GameAdventureIsland::update(Machine* mach, double dt)
{
	if(dt > 0.1)
		dt = 0.1;
	if(!smgr.update(mach, dt))
	{
		mach->shutdown();
	}
}
void GameAdventureIsland::render(Machine* mach, Graphics* gr)
{
	smgr.render(mach, gr);
}

