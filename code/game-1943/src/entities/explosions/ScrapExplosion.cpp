////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScrapExplosion
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/explosions/ScrapExplosion.h>
#include <src/Utils.h>
#include <src/ResourceManager.h>
#include <src/sprites/Sprite.h>
#include <src/sprites/SpriteSheet.h>

ScrapExplosion::ScrapExplosion(Scene* s, double x, double y, char type, double ___angle) : Explosion(s, x, y)
, clock(0.2)
, angle(___angle)
, sprite(null)
, spriteIndex(0)
{
	char sn[10] = "scrap.x";
	sn[6] = type;
	sprite = res.findSpriteSheet("explosions")->getSprite(sn);
}
ScrapExplosion::~ScrapExplosion()
{
}
void ScrapExplosion::update(double dt)
{
	pos = Utils::getMoved(pos, angle, 50*dt);
	if(clock.update(dt))
	{
		if(++spriteIndex >= sprite->count)
		{
			removable = true;
		}
	}
}
void ScrapExplosion::render(Graphics* gr)
{
	sprite->render(gr, position().x, position().y, spriteIndex);
}
