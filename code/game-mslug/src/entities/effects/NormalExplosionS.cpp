////////////////////////////////////////////////////////////////////////////////////////////////////
//
// NormalExplosionS | Explosión normal de tamaño pequeño (Small)
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/NormalExplosionS.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

NormalExplosionS::NormalExplosionS(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("NormalExplosionS")->getSprite();
}
NormalExplosionS::~NormalExplosionS()
{
}
void NormalExplosionS::update(double dt)
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
void NormalExplosionS::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
