////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BulletHit1 | Explosión de bala que se genera cuando se golpea contra una entidad
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/BulletHit1.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

BulletHit1::BulletHit1(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("BulletHit1")->getSprite();
}
BulletHit1::~BulletHit1()
{
}
void BulletHit1::update(double dt)
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
void BulletHit1::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
