////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellShotEffect | Efecto de disparo del Masknell
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/masknell/MasknellShotEffect.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

MasknellShotEffect::MasknellShotEffect(Scene* scene, double x, double y) : Entity(scene, x, y)
, frame(0)
, clock(0.04)
, sprite(null)
{
	sprite = res.findSpriteSheet("MasknellShotEffect")->getSprite();
}
MasknellShotEffect::~MasknellShotEffect()
{
}
void MasknellShotEffect::update(double dt)
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
void MasknellShotEffect::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}

