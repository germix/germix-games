////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusEffect | Efecto visual cuando se obtiene un bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/BonusEffect.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

BonusEffect::BonusEffect(Scene* scene, double x, double y)
: Entity(scene, x, y)
, frame(0)
, clock(0.05)
, sprite(null)
{
	sprite = res.findSpriteSheet("BonusEffect")->getSprite();
}
BonusEffect::~BonusEffect()
{
}
void BonusEffect::update(double dt)
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
void BonusEffect::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
