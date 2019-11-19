////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugMosqueScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___DebugMosqueScreen_h___
#define ___DebugMosqueScreen_h___
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/mosque/Mosque.h>

#include <mach/Keyboard.h>

class DebugMosqueScreen : public DebugPlayingScreen
{
public:
	DebugMosqueScreen() {}
	~DebugMosqueScreen() {}
public:
	void show(Machine* mach)
	{
		DebugPlayingScreen::show(mach);
		scene->addEntity(new Mosque(scene, 260, SCREEN_HEIGHT-DEBUG_GROUND_HEIGHT));
	}
	void update(Machine* mach, double dt)
	{
		DebugPlayingScreen::update(mach, dt);
	}
};

#endif

