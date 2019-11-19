////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugBradleyScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugBradleyScreen_h___
#define ___DebugBradleyScreen_h___
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/bradley/Bradley.h>

#include <mach/Keyboard.h>

class DebugBradleyScreen : public DebugPlayingScreen
{
public:
	DebugBradleyScreen() {}
	~DebugBradleyScreen() {}
public:
	void show(Machine* mach)
	{
		DebugPlayingScreen::show(mach);
		scene->addEntity(new Bradley(scene, 260, 0));
	}
	void update(Machine* mach, double dt)
	{
		DebugPlayingScreen::update(mach, dt);
		if(Keyboard::isPressed(Key::SPACE))
		{
			scene->addEntity(new Bradley(scene, scene->getHero()->getPosition().x + 150, 0));
		}
	}
};

#endif

