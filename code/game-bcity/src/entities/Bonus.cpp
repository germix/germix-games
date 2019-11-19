////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Bonus.h>
#include <src/Config.h>
#include <src/Scene.h>
#include <src/base/Sprite.h>
#include <src/entities/ScoreEffect.h>
#include <src/entities/tanks/HeroTank.h>

#include <mach/Mixer.h>

Bonus::Bonus(Map* m, Scene* s, int x, int y, int t, Sound* snd) : Entity(m, s, x, y)
, type(t)
, sound(snd)
, visible(false)
, blinkClock(0.2)
, removeClock(20)
{
}
Bonus::~Bonus()
{
}
void Bonus::update(double dt)
{
	if(blinkClock.update(dt))
	{
		visible = !visible;
	}
	if(removeClock.update(dt))
	{
		removable = true;
	}
}
void Bonus::render(Graphics* gr)
{
	if(visible)
		Config::bonus->render(gr, x, y, type);
}
void Bonus::collides(Entity* other)
{
	HeroTank* hero;
	
	if(null != (hero = dynamic_cast<HeroTank*>(other)))
	{
		//
		// Activar bonus
		//
		activated(hero);
		Mixer::playChannel(sound);
		
		//
		// Marcar como removible
		//
		removable = true;
		
		//
		// Agregar puntaje al héroe
		//
		hero->addScore(500);
		
		//
		// Generar efecto del puntaje
		//
		scene->addEntity(new ScoreEffect(map, scene, x, y, 500));
	}
}
