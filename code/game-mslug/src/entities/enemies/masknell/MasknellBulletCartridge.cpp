////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellBulletCartridge | Cartucho de bala del Masknell
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/masknell/MasknellBulletCartridge.h>
#include <src/Config.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

MasknellBulletCartridge::MasknellBulletCartridge(Scene* scene, double x, double y, int dir) : Entity(scene, x, y)
, vel(dir * 30, 0)
, sprite(null)
, spriteFrame(0)
, spriteHints(dir == -1 ? Sprite::FLIP_X : 0)
, spriteClock(0.06)
{
	sprite = res.findSpriteSheet("MasknellBulletCartridge")->getSprite();
}
MasknellBulletCartridge::~MasknellBulletCartridge()
{
}
void MasknellBulletCartridge::update(double dt)
{
	pos.x += vel.x*dt;
	pos.y += vel.y*dt + ((GRAVITY_CONSTANT*GRAVITY_DOWN)*dt*dt)/2;
	
	vel.y += (GRAVITY_CONSTANT*GRAVITY_DOWN)*dt;

	if(spriteClock.update(dt))
	{
		if(++spriteFrame >= sprite->count())
		{
			spriteFrame = 0;
			removable = true;
		}
	}
}
void MasknellBulletCartridge::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, spriteHints);
}


