////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Game1943
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Game1943.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/BonusManager.h>
#include <src/screens/InitScreen.h>
#if 1
#include <src/screens/PlayingScreen.h>
#include <src/screens/WinnerScreen.h>
#include <src/screens/GameOverScreen.h>
#endif

#include <mach/Color.h>
#include <mach/Machine.h>
#include <mach/Graphics.h>

Game1943::Game1943()
{
}
Game1943::~Game1943()
{
}
void Game1943::init(Machine* mach)
{
	res.load("1943/resources.xres");
	BonusManager::init();
	smgr.init(mach, new InitScreen());
//	smgr.init(mach, new WinnerScreen());
//	smgr.init(mach, new GameOverScreen());
//	smgr.init(mach, new PlayingScreen());
}
void Game1943::close(Machine* mach)
{
	BonusManager::clear();
}
void Game1943::update(Machine* mach, double dt)
{
	if(dt > 0.3)
		dt = 0.3;

	if(!smgr.update(mach, dt))
	{
		mach->shutdown();
	}
}
void Game1943::render(Machine* mach, Graphics* gr)
{
	gr->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color());
	gr->clip(SCENE_X, SCENE_Y, SCENE_WIDTH, SCENE_HEIGHT);
	smgr.render(mach, gr);
}

