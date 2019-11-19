////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Eggplant
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/followers/Eggplant.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>

#include <mach/Mixer.h>
#include <mach/Graphics.h>
#include <src/Scene.h>
#include <src/ResourceManager.h>

Eggplant::Eggplant(Scene* s, double x, double y) : HeroFollower(s, x, y)
, clock(4)
, texture(res.findTexture("Eggplant"))
{
	Mixer::playMusic(res.findMusic("Eggplant"));
}
Eggplant::~Eggplant()
{
}
void Eggplant::update(double dt)
{
	HeroFollower::update(dt);
	if(state == STATE_IDLE)
	{
		if(clock.update(dt))
		{
			if(hero->decreaseHealth() == 2)
			{
				leave();
			}
		}
	}
	if(removable)
	{
		Mixer::playMusic(scene->getSceneMusic());
	}
}
void Eggplant::render(Graphics* gr)
{
	gr->drawTexture(texture, (int)(pos.x - 16), (int)(pos.y - 16 + dy));
}
