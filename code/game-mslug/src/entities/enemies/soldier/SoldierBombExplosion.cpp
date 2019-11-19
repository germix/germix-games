////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SoldierBombExplosion | Efecto de explosión de la bomba del soldado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/soldier/SoldierBombExplosion.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

SoldierBombExplosion::SoldierBombExplosion(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("SoldierBombExplosion")->getSprite();
}
SoldierBombExplosion::~SoldierBombExplosion()
{
}
void SoldierBombExplosion::update(double dt)
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
void SoldierBombExplosion::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
