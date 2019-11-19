////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BradleyShootingFire
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/bradley/BradleyShootingFire.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

BradleyShootingFire::BradleyShootingFire(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.04)
, sprite(null)
{
	sprite = res.findSpriteSheet("Bradley.ShootingFire2")->getSprite();
}
BradleyShootingFire::~BradleyShootingFire()
{
}
void BradleyShootingFire::update(double dt)
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
void BradleyShootingFire::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
