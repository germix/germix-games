////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestEntities
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/testing/TestEntities.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/followers/Honeygirl.h>

#include <mach/Machine.h>
#include <mach/Keyboard.h>

TestEntities::TestEntities()
: hero(null)
, scene(null)
, weapon(1)
{
}
TestEntities::~TestEntities()
{
	delete scene;
}
void TestEntities::init(Machine* mach)
{
	res.load("aisland/resources.xres");
	scene = new Scene(info);
	scene->addEntity(hero = new Hero(scene, 20, 184, info));
	hero->setWeapon(Hero::WEAPON_AX);
	firstCreate();
}
void TestEntities::close(Machine* mach)
{
}
void TestEntities::update(Machine* mach, double dt)
{
	if(dt > 0.8)
		dt = 0.8;

	if(Keyboard::isPressed(Key::TAB))
	{
		weapon ++;
		if(weapon == 3)
			weapon = 1;
		hero->setWeapon(weapon);
	}
	if(Keyboard::isPressed(Key::SPACE))
	{
		create();
	}
	if(Keyboard::isPressed(Key::LETTER_H))
	{
		scene->addEntity(new Honeygirl(scene, 0, 0));
	}
	if(Keyboard::isPressed(Key::LEFT_CTRL))
	{
		hero->setSkate();
	}
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		mach->shutdown();
	}
	else
	{
		scene->update(dt);
		if(scene->isCompleted())
		{
			mach->shutdown();
		}
	}
}
void TestEntities::render(Machine* mach, Graphics* gr)
{
	scene->render(gr);
}
