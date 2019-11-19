////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BulletHit2 | Explosión de bala que se genera cuando se golpea contra un elemento del entorno
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/BulletHit2.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

BulletHit2::BulletHit2(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("BulletHit2")->getSprite();
}
BulletHit2::~BulletHit2()
{
}
void BulletHit2::update(double dt)
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
void BulletHit2::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
