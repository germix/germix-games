////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Explosion
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Explosion.h>
#include <src/base/Sprite.h>

Explosion::Explosion(Map* m, Scene* s, int x, int y, Sprite* spr, double time) : Entity(m, s, x-spr->getFrameWidth()/2, y-spr->getFrameHeight()/2)
, sprite(spr)
, spriteIndex(0)
, spriteClock(time)
{
}
Explosion::~Explosion()
{
}
void Explosion::update(double dt)
{
	if(spriteClock.update(dt))
	{
		if(++spriteIndex == sprite->getFrameCount())
			removable = true;
	}
}
void Explosion::render(Graphics* gr)
{
	sprite->render(gr, x, y, spriteIndex);
}

