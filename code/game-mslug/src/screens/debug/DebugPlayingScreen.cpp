////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebugPlayingScreen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/screens/debug/DebugPlayingScreen.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/scene/DebugHud.h>
#include <src/scene/DebugMap.h>
#include <src/entities/hero/Hero.h>

#include <src/entities/enemies/soldier/Soldier.h>

#include <mach/Keyboard.h>

#define MAX_WEAPONS 4

DebugPlayingScreen::DebugPlayingScreen()
: removable(false)
, scene(null)
, currentWeapon(0)
{
}
DebugPlayingScreen::~DebugPlayingScreen()
{
	if(scene)
		delete scene;
}
Screen* DebugPlayingScreen::getNext()
{
	return null;
}
bool    DebugPlayingScreen::isRemovable()
{
	return removable;
}
void    DebugPlayingScreen::show(Machine* mach)
{
	scene = new Scene(new DebugMap(1500, SCREEN_HEIGHT), false);
	hud = new DebugHud();
	scene->addEntity(hero = new Hero(scene, 80, 0));
}
void    DebugPlayingScreen::hide(Machine* mach)
{
}
void    DebugPlayingScreen::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		removable = true;
	}
	if(Keyboard::isPressed(Key::TAB))
	{
		if(++currentWeapon >= MAX_WEAPONS)
		{
			currentWeapon = 0;
		}
		hero->setWeapon(currentWeapon);
	}
	if(Keyboard::isPressed(Key::LETTER_B))
	{
		hero->addBombs(10);
	}
	scene->update(dt);
	hud->update(scene, dt);
}
void    DebugPlayingScreen::render(Machine* mach, Graphics* gr)
{
	scene->render(gr);
	hud->render(scene, gr);
}


