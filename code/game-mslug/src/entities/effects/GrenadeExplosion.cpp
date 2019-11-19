////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GrenadeExplosion | Explosión de granada
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/GrenadeExplosion.h>
#include <src/ResourceManager.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

GrenadeExplosion::GrenadeExplosion(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("GrenadeExplosion")->getSprite();
	Mixer::playChannel(res.findSound("GrenadeExplosion"));
}
GrenadeExplosion::~GrenadeExplosion()
{
}
void GrenadeExplosion::update(double dt)
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
void GrenadeExplosion::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
