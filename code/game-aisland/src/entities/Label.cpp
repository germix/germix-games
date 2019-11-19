////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Label
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Label.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>

#include <mach/Mixer.h>
#include <mach/Graphics.h>

Label::Label(Scene* s, double x, double y, char ___type) : Entity(s, x, y)
, type(___type)
, texture(null)
{
	switch(type)
	{
		case 'S': texture = res.findTexture("Label.S"); break;
		case '2': texture = res.findTexture("Label.2"); break;
		case '3': texture = res.findTexture("Label.3"); break;
		case '4': texture = res.findTexture("Label.4"); break;
		case 'G': texture = res.findTexture("Label.G"); break;
	}
}
Label::~Label()
{
}
void Label::update(double dt)
{
	Hero* hero;
	if(type != 0 && (null != (hero = scene->getHero())) && (pos.x-100 < hero->getPosition().x))
	{
		if(type == 'S')
		{
		}
		else if(type == 'G')
		{
			hero->win();
			Mixer::playMusic(res.findMusic("RoundCompleted"));
		}
		else
		{
			scene->setRespawnPosition(Vector2f(pos.x - 60, pos.y));
		}
		type = 0;
	}
}
void Label::render(Graphics* gr)
{
	gr->drawTexture(texture, int(pos.x - 8), int(pos.y - 16));
}
