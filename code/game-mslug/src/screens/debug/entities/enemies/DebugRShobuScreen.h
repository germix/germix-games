////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugRShobuScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugRShobuScreen_h___
#define ___DebugRShobuScreen_h___
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/rshobu/RShobu.h>

#include <mach/Keyboard.h>

class DebugRShobuScreen : public DebugPlayingScreen
{
public:
	DebugRShobuScreen() {}
	~DebugRShobuScreen() {}
public:
	void show(Machine* mach)
	{
		DebugPlayingScreen::show(mach);
		scene->addEntity(new RShobu(scene, 260, 0));
	}
	void update(Machine* mach, double dt)
	{
		DebugPlayingScreen::update(mach, dt);
		if(Keyboard::isPressed(Key::SPACE))
		{
			scene->addEntity(new RShobu(scene, scene->getHero()->getPosition().x + 170, 0));
		}
	}
};

#endif

