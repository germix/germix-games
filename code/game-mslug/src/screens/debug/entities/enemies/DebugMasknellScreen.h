////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugMasknellScreen
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugMasknellScreen_h___
#define ___DebugMasknellScreen_h___
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/masknell/MasknellFleet.h>

#include <mach/Keyboard.h>

class DebugMasknellScreen : public DebugPlayingScreen
{
public:
	DebugMasknellScreen() {}
	~DebugMasknellScreen() {}
public:
	void show(Machine* mach)
	{
		DebugPlayingScreen::show(mach);
		scene->addEntity(new MasknellFleet(scene, SCREEN_WIDTH+30, 30));
	}
	void update(Machine* mach, double dt)
	{
		DebugPlayingScreen::update(mach, dt);
		if(Keyboard::isPressed(Key::SPACE))
		{
			scene->addEntity(new MasknellFleet(scene, scene->getHero()->getPosition().x+SCREEN_WIDTH+30, 30));
		}
	}
};

#endif

