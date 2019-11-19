////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugSoldierScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugSoldierScreen_h___
#define ___DebugSoldierScreen_h___
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/soldier/Soldier.h>

#include <mach/Keyboard.h>

class DebugSoldierScreen : public DebugPlayingScreen
{
public:
	DebugSoldierScreen() {}
	~DebugSoldierScreen() {}
public:
	void show(Machine* mach)
	{
		DebugPlayingScreen::show(mach);
		scene->addEntity(new Soldier(scene, 240, 192));
	}
	void update(Machine* mach, double dt)
	{
		DebugPlayingScreen::update(mach, dt);
		if(Keyboard::isPressed(Key::SPACE))
		{
			scene->addEntity(new Soldier(scene, scene->getHero()->getPosition().x + 150, 0));
		}
	}
};

#endif
