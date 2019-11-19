////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PistolBullet | Bala de la pistola
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/PistolBullet.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/effects/BulletHit1.h>
#include <src/entities/effects/BulletHit2.h>
#include <src/___/HurtableRect.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

PistolBullet::PistolBullet(Scene* scene, double px, double py, double vx, double vy) : HeroBullet(scene, px, py)
, vel(vx, vy)
{
	sprite = res.findSpriteSheet("Bullet.P")->getSprite();
}
PistolBullet::~PistolBullet()
{
}
void PistolBullet::update(double dt)
{
	CollisionInfo ci =  scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);
	
	if(ci.flags != 0)
	{
		//
		// Eliminar si colision� con el escenario
		//
		removable = true;
		scene->addEntity(new BulletHit2(scene, pos.x, pos.y));
	}
	else if(scene->getCameraRect().excluded(bounds()))
	{
		//
		// Eliminar si est� fuera de la c�mara
		//
		removable = true;
	}
}
void PistolBullet::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, 0, 0);
	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef PistolBullet::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef PistolBullet::bounds(double px, double py) const
{
	return Rectanglef(px-4,py-4,8,8);
}
void PistolBullet::hurt(HurtableRect* hr)
{
	removable = true;
	hr->hurt(2);
	scene->addEntity(new BulletHit1(scene, pos.x, pos.y));
}
