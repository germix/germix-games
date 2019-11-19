////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SoldierDeadEffect | Effecto de la muerte del soldado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/soldier/SoldierDeadEffect.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

SoldierDeadEffect::SoldierDeadEffect(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.04)
, sprite(null)
{
	sprite = res.findSpriteSheet("SoldierDeadEffect")->getSprite();
}
SoldierDeadEffect::~SoldierDeadEffect()
{
}
void SoldierDeadEffect::update(double dt)
{
	if(clock.update(dt))
	{
		if(++frame >= sprite->count())
		{
			frame = 0;
			removable = true;
		}
	}
}
void SoldierDeadEffect::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
