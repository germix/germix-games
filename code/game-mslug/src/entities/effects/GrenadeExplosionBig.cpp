////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GrenadeExplosionBig | Explosión de granada (grande)
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/GrenadeExplosionBig.h>
#include <src/ResourceManager.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

GrenadeExplosionBig::GrenadeExplosionBig(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("GrenadeExplosionBig")->getSprite();
	Mixer::playChannel(res.findSound("GrenadeExplosionBig"));
}
GrenadeExplosionBig::~GrenadeExplosionBig()
{
}
void GrenadeExplosionBig::update(double dt)
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
void GrenadeExplosionBig::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
