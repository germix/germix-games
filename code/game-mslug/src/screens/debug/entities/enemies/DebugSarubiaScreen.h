////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugSarubiaScreen
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugSarubiaScreen_h___
#define ___DebugSarubiaScreen_h___
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/sarubia/Sarubia.h>

#include <mach/Keyboard.h>

class DebugSarubiaScreen : public DebugPlayingScreen
{
public:
	DebugSarubiaScreen() {}
	~DebugSarubiaScreen() {}
public:
	void show(Machine* mach)
	{
		DebugPlayingScreen::show(mach);
		scene->addEntity(new Sarubia(scene, 240, 192));
	}
	void update(Machine* mach, double dt)
	{
		DebugPlayingScreen::update(mach, dt);
		if(Keyboard::isPressed(Key::SPACE))
		{
			scene->addEntity(new Sarubia(scene, scene->getHero()->getPosition().x + 150, 0));
		}
	}
};

#endif
