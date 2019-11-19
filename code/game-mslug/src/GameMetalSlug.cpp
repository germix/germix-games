////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameMetalSlug
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/GameMetalSlug.h>
#include <src/ResourceManager.h>

#include <mach/Mixer.h>
#include <mach/Machine.h>

#include <src/screens/InitScreen.h>
#include <src/screens/MenuScreen.h>
#include <src/screens/RankingScreen.h>
#include <src/screens/GameOverScreen.h>
#include <src/screens/HeroSelectionScreen.h>
#include <src/screens/PlayingMissionScreen.h>

#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/screens/debug/DebugMissionCompletedScreen.h>

#include <src/screens/debug/entities/enemies/DebugSoldierScreen.h>
#include <src/screens/debug/entities/enemies/DebugRShobuScreen.h>
#include <src/screens/debug/entities/enemies/DebugMosqueScreen.h>
#include <src/screens/debug/entities/enemies/DebugBradleyScreen.h>
#include <src/screens/debug/entities/enemies/DebugSarubiaScreen.h>
#include <src/screens/debug/entities/enemies/DebugMasknellScreen.h>
#include <src/screens/debug/entities/enemies/DebugIronNokanaScreen.h>

#include <src/screens/debug/entities/others/DebugBonusScreen.h>
#include <src/screens/debug/entities/others/DebugHiddenBonusScreen.h>

#include <src/screens/PistolScreen.h>
#include <src/screens/ControlsScreen.h>
#include <src/screens/ArtScreen.h>
#include <src/screens/EnterNameScreen.h>
#include <mach/Random.h>

GameMetalSlug::GameMetalSlug()
{
}
GameMetalSlug::~GameMetalSlug()
{
}
void GameMetalSlug::init(Machine* mach)
{
	res.load("mslug/resources.xres");
	res.load("mslug/resources-font.xres");

	smgr.init(mach, new InitScreen());
//	smgr.init(mach, new MenuScreen());						mach->setTitle("Metal Slug | MenuScreen");
//	smgr.init(mach, new RankingScreen());					mach->setTitle("Metal Slug | RankingScreen");
//	smgr.init(mach, new GameOverScreen());					mach->setTitle("Metal Slug | GameOverScreen");
//	smgr.init(mach, new HeroSelectionScreen());				mach->setTitle("Metal Slug | HeroSelectionScreen");
//	smgr.init(mach, new PlayingMissionScreen());			mach->setTitle("Metal Slug | PlayingMissionScreen");
//	smgr.init(mach, new PistolScreen());					mach->setTitle("Metal Slug | PistolScreen");
//	smgr.init(mach, new ControlsScreen());					mach->setTitle("Metal Slug | ControlsScreen");
//	smgr.init(mach, new ArtScreen());						mach->setTitle("Metal Slug | ArtScreen");
//	smgr.init(mach, new EnterNameScreen(Random().nextInt(10, 10000), 30));			mach->setTitle("Metal Slug | EnterNameScreen");

//	smgr.init(mach, new DebugPlayingScreen());				mach->setTitle("Metal Slug | DebugPlayingScreen");
//	smgr.init(mach, new DebugMissionCompletedScreen());		mach->setTitle("Metal Slug | DebugMissionCompletedScreen");

//	smgr.init(mach, new DebugSoldierScreen());				mach->setTitle("Metal Slug | Debug | Soldier");
//	smgr.init(mach, new DebugRShobuScreen());				mach->setTitle("Metal Slug | Debug | R-Shobu");
//	smgr.init(mach, new DebugMosqueScreen());				mach->setTitle("Metal Slug | Debug | Mosque");
//	smgr.init(mach, new DebugBradleyScreen());				mach->setTitle("Metal Slug | Debug | Bradley");
//	smgr.init(mach, new DebugSarubiaScreen());				mach->setTitle("Metal Slug | Debug | Sarubia");
//	smgr.init(mach, new DebugMasknellScreen());				mach->setTitle("Metal Slug | Debug | Masknell");
//	smgr.init(mach, new DebugIronNokanaScreen());			mach->setTitle("Metal Slug | Debug | IronNokana");
//	smgr.init(mach, new DebugBonusScreen());				mach->setTitle("Metal Slug | Debug | Bonus");
//	smgr.init(mach, new DebugHiddenBonusScreen());			mach->setTitle("Metal Slug | Debug | HiddenBonus");
}
void GameMetalSlug::close(Machine* mach)
{
}
void GameMetalSlug::update(Machine* mach, double dt)
{
	if(dt > 0.5)
		dt = 0.5;
//	dt /= 8;
	if(!smgr.update(mach, dt))
	{
		mach->shutdown();
	}
}
void GameMetalSlug::render(Machine* mach, Graphics* gr)
{
	smgr.render(mach, gr);
}


