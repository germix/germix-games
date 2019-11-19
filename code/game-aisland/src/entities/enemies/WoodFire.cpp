////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WoodFire
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/WoodFire.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

WoodFire::WoodFire(Scene* s, double x, double y) : Enemy(s, x, y)
, sheet(res.findSpriteSheet("WoodFire"))
, sprite(sheet->getSprite("Idle"))
, spriteIndex(0)
, spriteClock(0.1)
{
}
WoodFire::~WoodFire()
{
}
void WoodFire::update(double dt)
{
	if(spriteClock.update(dt))
	{
		if(++spriteIndex >= sprite->count())
		{
			spriteIndex = 0;
		}
	}
}
void WoodFire::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, 0);
}
void WoodFire::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
}
Rectanglef WoodFire::getCollisionRectangle() const
{
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 6, pos.y - 20, 12, 20);
}
