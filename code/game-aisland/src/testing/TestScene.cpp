////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestScene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/testing/TestScene.h>
#include <src/Scene.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>

#include <mach/Machine.h>
#include <mach/Keyboard.h>

TestScene::TestScene(int ___area, int ___round)
: scene(null)
, area(___area)
, round(___round)
, weapon(0)
{
}
TestScene::~TestScene()
{
	delete scene;
}
void TestScene::init(Machine* mach)
{
	res.load("aisland/resources.xres");
	scene = new Scene(info, area, round);
}
void TestScene::close(Machine* mach)
{
}
void TestScene::update(Machine* mach, double dt)
{
	if(Keyboard::isPressed(Key::ESCAPE))
	{
		mach->shutdown();
	}
	else
	{
		if(Keyboard::isPressed(Key::TAB))
		{
			weapon ++;
			if(weapon == 3)
				weapon = 1;
			scene->getHero()->setWeapon(weapon);
		}
		scene->update(dt);
		if(scene->isFinished())
		{
			if(scene->isCompleted())
				mach->shutdown();
			else
				scene->restart();
		}
	}
}
void TestScene::render(Machine* mach, Graphics* gr)
{
	scene->render(gr);
}
