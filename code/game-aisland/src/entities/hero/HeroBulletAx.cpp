////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBulletAx
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/HeroBulletAx.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>

#include <gamelib-sprites/SpriteSheet.h>

HeroBulletAx::HeroBulletAx(Scene* s, double x, double y, double vx, double vy) : HeroBullet(s, x, y, vx, vy, res.findSpriteSheet("HeroBulletAx")->getSprite("Idle"))
{
}
HeroBulletAx::~HeroBulletAx()
{
}
void HeroBulletAx::stop()
{
	if(!stopped)
	{
		stopped = true;
		if(velocity.x > 0)
			velocity = Vector2f(-40, 0);
		else
			velocity = Vector2f(+40, 0);
	}
}
Rectanglef HeroBulletAx::getCollisionRectangle() const
{
	if(stopped)
		return Rectanglef();
	return bounds();
}
