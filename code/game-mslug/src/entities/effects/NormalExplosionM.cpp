////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NormalExplosionM | Explosión normal de tamaño medio (Medium)
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/NormalExplosionM.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

NormalExplosionM::NormalExplosionM(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("NormalExplosionM")->getSprite();
}
NormalExplosionM::~NormalExplosionM()
{
}
void NormalExplosionM::update(double dt)
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
void NormalExplosionM::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
