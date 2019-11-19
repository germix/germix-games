////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameBattleCity
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/GameBattleCity.h>
#include <src/Config.h>
#include <src/res/ResourceManager.h>

#include <mach/Machine.h>

#include <src/screens/InitScreen.h>
#include <src/screens/AboutScreen.h>
#include <src/screens/AllOverScreen.h>
#include <src/screens/GameOverScreen.h>
#include <src/screens/HiScoreScreen.h>
#include <src/screens/StatisticsScreen.h>
#include <src/screens/SelectMapScreen.h>
#include <src/screens/SelectMapTypeScreen.h>
#include <src/screens/ConstructionScreen.h>

#include <src/base/Player.h>
#include <src/screens/PlayingScreen.h>
#include <src/stages/SkirmishStagesProvider.h>
#include <src/stages/CampaignStagesProvider.h>

GameBattleCity::GameBattleCity()
{
}
GameBattleCity::~GameBattleCity()
{
}
void GameBattleCity::init(Machine* mach)
{
	res.load("bcity/resources.xres");
	Config::load();

	smgr.init(mach, new InitScreen());

/*
//	smgr.init(mach, new InitScreen());
//	smgr.init(mach, new AboutScreen());
//	smgr.init(mach, new AllOverScreen());
//	smgr.init(mach, new GameOverScreen());
//	smgr.init(mach, new HiScoreScreen(123456789));
	
	Player* player1 = new Player();
	Player* player2 = null;
	int victims1[] = {4,2,10,2};
	int victims2[] = {1,4,2,7};

//	smgr.init(mach, new StatisticsScreen("X", player1, victims1, true, player2, victims2, true));
//	smgr.init(mach, new SelectMapScreen(true, player1, player2));
//	smgr.init(mach, new SelectMapTypeScreen(player1, player2));
//	smgr.init(mach, new PlayingScreen(new CampaignStagesProvider(), player1, player2));
//	smgr.init(mach, new PlayingScreen(new SkirmishStagesProvider("bcity/maps/bcity-01.tmx"), player1, player2));
//	smgr.init(mach, new ConstructionScreen());
*/
}
void GameBattleCity::close(Machine* mach)
{
	Config::save();
}
void GameBattleCity::update(Machine* mach, double dt)
{
	if(dt > 1)
		dt = 1;
	if(!smgr.update(mach, dt))
	{
		mach->shutdown();
	}
}
void GameBattleCity::render(Machine* mach, Graphics* gr)
{
	smgr.render(mach, gr);
}
