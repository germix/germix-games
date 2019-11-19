////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NormalExplosion
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/explosions/NormalExplosion.h>
#include <src/ResourceManager.h>
#include <src/sprites/Sprite.h>
#include <src/sprites/SpriteSheet.h>

#include <mach/Mixer.h>

NormalExplosion::NormalExplosion(Scene* s, double x, double y, Entity* ___ref, const char* sound, const char* ___sprite, double time) : Explosion(s, x, y)
, ref(___ref)
, clock(time)
, sprite(res.findSpriteSheet("explosions")->getSprite(___sprite))
, spriteIndex(0)
{
	Mixer::playChannel(res.findSound(sound));
	if(!sprite)
	{
		printf("");
	}
}
NormalExplosion::~NormalExplosion()
{
}
void NormalExplosion::update(double dt)
{
	if(clock.update(dt))
	{
		if(++spriteIndex >= sprite->count)
		{
			removable = true;
		}
	}
}
void NormalExplosion::render(Graphics* gr)
{
	Vector2f p = pos;
	if(ref)
	{
		Rectanglef rc = ref->rect();
		p = Vector2f(rc.getX() + pos.x, rc.getY() + pos.y);
	}
	sprite->render(gr, p.x, p.y, spriteIndex);
}
