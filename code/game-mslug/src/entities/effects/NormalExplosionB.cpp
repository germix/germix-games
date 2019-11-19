////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NormalExplosionB | Explosión normal de tamaño grande (Big)
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/NormalExplosionB.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

NormalExplosionB::NormalExplosionB(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("NormalExplosionB")->getSprite();
}
NormalExplosionB::~NormalExplosionB()
{
}
void NormalExplosionB::update(double dt)
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
void NormalExplosionB::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
