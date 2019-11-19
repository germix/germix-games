////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugIronNokanaScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugIronNokanaScreen_h___
#define ___DebugIronNokanaScreen_h___
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/nokana/IronNokana.h>

#include <mach/Keyboard.h>

class DebugIronNokanaScreen : public DebugPlayingScreen
{
public:
	DebugIronNokanaScreen() {}
	~DebugIronNokanaScreen() {}
public:
	void show(Machine* mach)
	{
		DebugPlayingScreen::show(mach);
		scene->addEntity(new IronNokana(scene, 240, 192));
		scene->setRightLimit(SCREEN_WIDTH+130);
	}
	void update(Machine* mach, double dt)
	{
		DebugPlayingScreen::update(mach, dt);
		if(Keyboard::isPressed(Key::SPACE))
		{
			scene->addEntity(new IronNokana(scene, scene->getHero()->getPosition().x + 150, 0));
		}
	}
};

#endif
