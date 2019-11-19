////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GamePacman
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/GamePacman.h>
#include <src/Config.h>
#include <src/screens/MenuScreen.h>
#include <src/resources/ResourceManager.h>

#include <mach/Machine.h>

#include <src/screens/AboutScreen.h>
#include <src/screens/PlayingScreen.h>
#include <src/screens/SelectMapScreen.h>
#include <src/screens/SelectThemeScreen.h>

GamePacman::GamePacman()
{
}
GamePacman::~GamePacman()
{
}
void GamePacman::init(Machine* mach)
{
	res.load("pacman/resources.xres");
	Config::load();
	
	smgr.init(mach, new MenuScreen());
//	smgr.init(mach, new AboutScreen());
//	smgr.init(mach, new PlayingScreen("testing-1.tmx"));
//	smgr.init(mach, new SelectMapScreen());
//	smgr.init(mach, new SelectThemeScreen());
}
void GamePacman::close(Machine* mach)
{
	Config::save();
}
void GamePacman::update(Machine* mach, double dt)
{
	if(dt > 0.8)
		dt = 0.8;
	if(!smgr.update(mach, dt))
	{
		mach->shutdown();
	}
}
void GamePacman::render(Machine* mach, Graphics* gr)
{
	smgr.render(mach, gr);
}


