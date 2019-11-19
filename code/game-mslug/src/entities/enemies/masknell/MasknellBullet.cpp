////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellBullet | Bala del Masknell
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/masknell/MasknellBullet.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/BulletHit2.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

MasknellBullet::MasknellBullet(Scene* scene, double x, double y) : EnemyProjectile(scene, x, y)
, vel(0, 60)
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, sprite(null)
, spriteFrame(0)
, spriteClock(0.06)
{
	sprite = res.findSpriteSheet("MasknellBullet")->getSprite();
}
MasknellBullet::~MasknellBullet()
{
}
void MasknellBullet::update(double dt)
{
	if(spriteClock.update(dt))
	{
		spriteFrame = (++spriteFrame) & 1;
	}
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);

	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		removable = true;
		scene->addEntity(new BulletHit2(scene, pos.x, pos.y));
	}
}
void MasknellBullet::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, 0);

	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef MasknellBullet::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef MasknellBullet::bounds(double px, double py) const
{
	return sprite->rectangle(pos.x, pos.y, spriteFrame, 0);
}
void MasknellBullet::collide(Entity* other)
{
	if(dynamic_cast<Hero*>(other))
	{
		removable = true;
		((Hero*)other)->hurt();
	}
}
Rectanglef MasknellBullet::collisionRect() const
{
	return bounds();
}
