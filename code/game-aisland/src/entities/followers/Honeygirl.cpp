////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Honeygirl
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/followers/Honeygirl.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>

#include <mach/Mixer.h>
#include <mach/Graphics.h>
#include <src/Scene.h>
#include <src/ResourceManager.h>

Honeygirl::Honeygirl(Scene* s, double x, double y) : HeroFollower(s, x, y)
, clock(11)
, texture(res.findTexture("Honeygirl"))
{
	hero->setHoneygirl(this);
	Mixer::playMusic(res.findMusic("Honeygirl"));
}
Honeygirl::~Honeygirl()
{
}
void Honeygirl::update(double dt)
{
	HeroFollower::update(dt);
	if(state == STATE_IDLE)
	{
		if(clock.update(dt))
		{
			leave();
		}
	}
	if(removable)
	{
		hero->releaseHoneygirl();
		Mixer::playMusic(scene->getSceneMusic());
	}
}
void Honeygirl::render(Graphics* gr)
{
	gr->drawTexture(texture, int(pos.x - 14), int(pos.y - 16 + dy));
}
